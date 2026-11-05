/*
 * Copyright (c) 2015, Google Inc. All rights reserved
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <err.h>
#include <kernel/thread.h>
#include <kernel/vm.h>
#include <lib/mmutest/mmutest.h>
#include <lib/unittest/unittest.h>
#include <lk/init.h>
#include <pow2.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
 * These below declarations are made to avoid issues with CFI
 * while copying heap allocated method, this is to reduce the
 * probability of it breaking in future toolchain versions
 */
extern uint8_t mmutest_arch_nop[];
extern uint8_t mmutest_arch_nop_end[];

static int mmutest_run_in_thread(const char* thread_name,
                                 int (*func)(void* arg),
                                 void* arg) {
    int ret;
    int thread_ret;
    struct thread* thread;
    uint8_t* canary;
    vmm_aspace_t* aspace = vmm_get_kernel_aspace();

    thread = thread_create("mmu_test_execute", func, arg, DEFAULT_PRIORITY,
                           DEFAULT_STACK_SIZE);
    if (!thread) {
        return ERR_NO_MEMORY;
    }

    canary = (uint8_t*)thread->stack - PAGE_SIZE * 2;

    ret = vmm_alloc(aspace, "canary", PAGE_SIZE, (void**)&canary, 0,
                    VMM_FLAG_VALLOC_SPECIFIC, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret) {
        canary = NULL;
    } else {
        memset(canary, 0x55, PAGE_SIZE);
    }

    thread_set_flag_exit_on_panic(thread, true);
    ret = thread_resume(thread);
    if (ret) {
        return ret;
    }

    ret = thread_join(thread, &thread_ret, INFINITE_TIME);
    if (ret) {
        return ret;
    }

    if (canary) {
        size_t i;
        for (i = 0; i < PAGE_SIZE; i++) {
            if (canary[i] != 0x55)
                break;
        }
        EXPECT_EQ(i, PAGE_SIZE, "memory below stack corrupted\n");

        vmm_free_region(aspace, (vaddr_t)canary);
    }

    return thread_ret;
}

static int mmutest_alloc(void** ptrp, uint arch_mmu_flags) {
    int ret;
    uint arch_mmu_flags_query = ~0U;
    vmm_aspace_t* aspace = vmm_get_kernel_aspace();

    ret = vmm_alloc_contiguous(aspace, "mmutest", PAGE_SIZE, ptrp, 0, 0,
                               arch_mmu_flags);

    EXPECT_EQ(NO_ERROR, ret, "vmm_alloc_contiguous failed\n");
    if (ret) {
        return ret;
    }

    arch_mmu_query(&aspace->arch_aspace, (vaddr_t)*ptrp, NULL,
                   &arch_mmu_flags_query);
    EXPECT_EQ(arch_mmu_flags_query, arch_mmu_flags,
              "arch_mmu_query, 0x%x, does not match requested flags, 0x%x\n",
              arch_mmu_flags_query, arch_mmu_flags);
    return 0;
}

static int mmutest_vmm_store_uint32(uint arch_mmu_flags, bool user) {
    int ret;
    void* ptr;

    ret = mmutest_alloc(&ptr, arch_mmu_flags);
    if (ret) {
        return ret;
    }

    ret = mmutest_arch_store_uint32(ptr, user);

    vmm_free_region(vmm_get_kernel_aspace(), (vaddr_t)ptr);
    return ret;
}

static int mmutest_vmm_store_uint32_kernel(uint arch_mmu_flags) {
    return mmutest_vmm_store_uint32(arch_mmu_flags, false);
}

static int mmutest_vmm_store_uint32_user(uint arch_mmu_flags) {
    return mmutest_vmm_store_uint32(arch_mmu_flags, true);
}

/*
 * disabling the cfi-icall as a workaround to avoid cfi check
 * failure errors while calling heap allocated functions
 */
static int mmu_test_execute_thread_func(void* arg)
        __attribute__((no_sanitize("cfi-icall"))) {
    void (*func)(void) = arg;
    func();
    return 0;
}

/*
 * Executes 'mmutest_arch_nop' code from a memory mapped with the passed flags.
 * To simplify test writing, this first creates a writable allocation and vmm
 * mapping before making a second mapping with the requested arch_mmu_flags and
 * executing the test thread.  This avoids violating W^X semantics which are
 * enforced on some architectures.
 */
static int mmu_test_execute(uint arch_mmu_flags) {
    const size_t len = mmutest_arch_nop_end - mmutest_arch_nop;
    const size_t alloc_len = round_up(len, PAGE_SIZE);
    vmm_aspace_t* aspace = vmm_get_kernel_aspace();
    struct obj_ref vmm_obj_ref = OBJ_REF_INITIAL_VALUE(vmm_obj_ref);
    struct vmm_obj* vmm_obj = NULL;
    void *ptr = NULL, *execute_ptr = NULL;
    uint arch_mmu_flags_query;
    int ret;

    /* Allocate pages to hold the test code and create writable mapping */
    ret = pmm_alloc(&vmm_obj, &vmm_obj_ref, alloc_len / PAGE_SIZE,
                    PMM_ALLOC_FLAG_CONTIGUOUS, 0);
    ASSERT_EQ(NO_ERROR, ret, "pmm_alloc failed\n");

    ret = vmm_alloc_obj(aspace, "mmutest_w", vmm_obj, 0, alloc_len, &ptr, 0, 0,
                        ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret, "vmm_alloc_obj failed\n");

    /* Populate the memory */
    memcpy(ptr, mmutest_arch_nop, len);
    arch_sync_cache_range((addr_t)ptr, len);

    /* Now create a new mapping with the desired test arch_mmu_flags */
    ret = vmm_alloc_obj(aspace, "mmutest_flags", vmm_obj, 0, alloc_len,
                        &execute_ptr, 0, 0, arch_mmu_flags);
    ASSERT_EQ(NO_ERROR, ret, "vmm_alloc_obj failed\n");

    /* Ensure the new mapping reflects the initialised memory */
    EXPECT_EQ(0, memcmp(ptr, execute_ptr, alloc_len),
              "mapping contents mismatch\n");

    /* Double check the flags are as expected on the new memory */
    arch_mmu_query(&aspace->arch_aspace, (vaddr_t)execute_ptr, NULL,
                   &arch_mmu_flags_query);
    ASSERT_EQ(arch_mmu_flags_query, arch_mmu_flags,
              "arch_mmu_query, 0x%x, does not match requested flags, 0x%x\n",
              arch_mmu_flags_query, arch_mmu_flags);

    /* Execute the test */
    ret = mmutest_run_in_thread("mmu_test_execute",
                                mmu_test_execute_thread_func, execute_ptr);

test_abort:
    if (execute_ptr) {
        int tmp_ret = vmm_free_region(aspace, (vaddr_t)execute_ptr);
        EXPECT_EQ(NO_ERROR, tmp_ret, "vmm_free_region failed\n");
    }

    if (ptr) {
        int tmp_ret = vmm_free_region(aspace, (vaddr_t)ptr);
        EXPECT_EQ(NO_ERROR, tmp_ret, "vmm_free_region failed\n");
    }

    if (vmm_obj) {
        vmm_obj_del_ref(vmm_obj, &vmm_obj_ref);
    }

    return ret;
}

/* Skip kernel permission tests on ARM as it uses 1MB mappings */
#if ARCH_ARM
#define DISABLED_ON_ARM_NAME(name) DISABLED_##name
#else
#define DISABLED_ON_ARM_NAME(name) name
#endif

typedef struct {
    vmm_aspace_t* aspace;
    size_t allocation_size;
} mmutestvmm_t;

TEST_F_SETUP(mmutestvmm) {
    int ret;
    const void* const* params = GetParam();
    const size_t* allocation_size_p = params[0];
    const bool* is_kernel_aspace = params[1];

    _state->allocation_size = *allocation_size_p;
    if (*is_kernel_aspace) {
        _state->aspace = vmm_get_kernel_aspace();
    } else {
        ret = vmm_create_aspace(&_state->aspace, "mmutestvmm", 0);
        ASSERT_EQ(NO_ERROR, ret);
    }

    ASSERT_GE(_state->allocation_size, PAGE_SIZE);
    ASSERT_LT(_state->allocation_size, _state->aspace->size);
test_abort:;
}

static size_t mmutestvmm_allocation_sizes[] = {
        PAGE_SIZE,
        2 * 1024 * 1024, /* large enough to use section/block mapping on arm */
};

TEST_F_TEARDOWN(mmutestvmm) {
    if (!(_state->aspace->flags & VMM_ASPACE_FLAG_KERNEL)) {
        vmm_free_aspace(_state->aspace);
    }
}

/* Smoke test for vmm_alloc */
TEST_P(mmutestvmm, vmm_alloc) {
    int ret;
    void* ptr = NULL;
    ret = vmm_alloc(_state->aspace, "mmutest", _state->allocation_size, &ptr, 0,
                    0, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    EXPECT_EQ(NO_ERROR, ret);
    EXPECT_NE(NULL, ptr);
    ret = vmm_free_region(_state->aspace, (vaddr_t)ptr);
    EXPECT_EQ(NO_ERROR, ret, "vmm_free_region failed\n");
}

/* Smoke test for vmm_alloc_contiguous */
TEST_P(mmutestvmm, vmm_alloc_contiguous) {
    int ret;
    void* ptr = NULL;
    ret = vmm_alloc_contiguous(_state->aspace, "mmutest",
                               _state->allocation_size, &ptr,
                               log2_uint(_state->allocation_size), 0,
                               ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    EXPECT_EQ(NO_ERROR, ret);
    EXPECT_NE(NULL, ptr);
    ret = vmm_free_region(_state->aspace, (vaddr_t)ptr);
    EXPECT_EQ(NO_ERROR, ret, "vmm_free_region failed\n");
}

INSTANTIATE_TEST_SUITE_P(
        allocationsize,
        mmutestvmm,
        testing_Combine(testing_ValuesIn(mmutestvmm_allocation_sizes),
                        /* user(false) and kernel(true) aspaces */
                        testing_Bool()));

static int mmutest_panic_thread_func(void* _unused) {
    panic("mmutest-panic");
}

TEST(mmutest, panic) {
    /* Check thread_set_flag_exit_on_panic feature needed by other tests */
    int ret = mmutest_run_in_thread("mmutest-panic", mmutest_panic_thread_func,
                                    NULL);
    EXPECT_EQ(ERR_FAULT, ret);
}

static int mmutest_panic_thread_lock_thread_func(void* _unused) {
    THREAD_LOCK(state);
    panic("mmutest-panic-thread-lock");
}

TEST(mmutest, panic_thread_lock) {
    /*
     * Test panic with thread locked. Both _panic and platform_halt locks the
     * thread_lock, so _panic needs to release it if it was already held by the
     * current CPU.
     */
    int ret =
            mmutest_run_in_thread("mmutest-panic-thread-lock",
                                  mmutest_panic_thread_lock_thread_func, NULL);
    EXPECT_EQ(ERR_FAULT, ret);
}

TEST(mmutest, alloc_last_kernel_page) {
    int ret;
    void* ptr1;
    void* ptr2;
    void* ptr3;
    vmm_aspace_t* aspace = vmm_get_kernel_aspace();
    struct vmm_obj_slice slice;
    vmm_obj_slice_init(&slice);

    /*
     * Perform allocations at a specific address and at a vmm chosen address
     * with and without the last page allocated. There are different code paths
     * in the vmm allocator where the virtual address can overflow for the
     * region that is being allocated and for regions already allocated.
     */

    /* Allocate last kernel aspace page. */
    ptr1 = (void*)(aspace->base + (aspace->size - PAGE_SIZE));
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr1, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD |
                            VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    /* TODO: allow this to fail as page could already be in use */
    ASSERT_EQ(NO_ERROR, ret, "vmm_alloc failed last page\n");

    /* While the last page is allocated, get an object corresponding to it */
    ret = vmm_get_obj(aspace, (vaddr_t)ptr1, PAGE_SIZE, &slice);
    EXPECT_EQ(NO_ERROR, ret, "vmm_get_obj failed to get last page object");
    /* Check the slice we got back */
    EXPECT_NE(NULL, slice.obj);
    EXPECT_EQ(PAGE_SIZE, slice.size);
    EXPECT_EQ(NO_ERROR, slice.offset);
    vmm_obj_slice_release(&slice);

    /* Allocate page anywhere, while the last page is allocated. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0, 0,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret, "vmm_alloc failed anywhere page\n");

    /* Try to allocate last kernel aspace page again, should fail */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr1, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    EXPECT_EQ(ERR_NO_MEMORY, ret, "vmm_alloc last page\n");

    /* Allocate 2nd last kernel aspace page, while last page is allocated. */
    ptr3 = (void*)(aspace->base + (aspace->size - 2 * PAGE_SIZE));
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr3, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    /* TODO: allow this to fail as page could already be in use */
    ASSERT_EQ(NO_ERROR, ret, "vmm_alloc failed 2nd last page\n");

    /* Free allocated pages */
    ret = vmm_free_region(aspace, (vaddr_t)ptr1);
    EXPECT_EQ(NO_ERROR, ret, "vmm_free_region failed\n");
    ret = vmm_free_region(aspace, (vaddr_t)ptr2);
    EXPECT_EQ(NO_ERROR, ret, "vmm_free_region failed\n");
    ret = vmm_free_region(aspace, (vaddr_t)ptr3);
    EXPECT_EQ(NO_ERROR, ret, "vmm_free_region failed\n");

    /* Try to allocate last page without VMM_FLAG_NO_END_GUARD flag */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr1, 0,
                    VMM_FLAG_VALLOC_SPECIFIC, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_OUT_OF_RANGE, ret, "vmm_alloc succeeded unexpectedly\n");

    /* Allocate and free last page */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr1, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    /* TODO: allow this to fail as page could be in use */
    ASSERT_EQ(NO_ERROR, ret, "vmm_alloc failed last page\n");
    ret = vmm_free_region(aspace, (vaddr_t)ptr1);
    EXPECT_EQ(NO_ERROR, ret, "vmm_free_region failed\n");

    /* Allocate and free page anywhere, while last page is free */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0, 0,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret, "vmm_alloc failed anywhere page\n");
    ret = vmm_free_region(aspace, (vaddr_t)ptr2);
    EXPECT_EQ(NO_ERROR, ret, "vmm_free_region failed\n");

test_abort:;
}

typedef struct {
    vmm_aspace_t* aspace;
} mmutestaspace_t;

TEST_F_SETUP(mmutestaspace) {
    int ret;
    const bool* is_kernel_aspace = GetParam();

    if (*is_kernel_aspace) {
        _state->aspace = vmm_get_kernel_aspace();
    } else {
        ret = vmm_create_aspace(&_state->aspace, "mmutestaspace", 0);
        ASSERT_EQ(NO_ERROR, ret);
    }

test_abort:;
}

TEST_F_TEARDOWN(mmutestaspace) {
    if (!(_state->aspace->flags & VMM_ASPACE_FLAG_KERNEL)) {
        vmm_free_aspace(_state->aspace);
    }
}

TEST_P(mmutestaspace, guard_page) {
    int ret;
    bool retb;
    vmm_aspace_t* aspace = _state->aspace;
    size_t size = PAGE_SIZE * 6;
    vaddr_t base;
    void* ptr1 = NULL;
    void* ptr2 = NULL;
    void* ptr3 = NULL;
    void* ptr4 = NULL;
    void* ptr5 = NULL;
    struct vmm_obj_slice slice;
    vmm_obj_slice_init(&slice);

    /* Allocate a page at a random spot with guard pages. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr1, 0, 0,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);

    /*
     * We may get an allocation right at the beginning of the address space
     * by chance or because ASLR is disabled. In that case, we make another
     * allocation to ensure that ptr1 - PAGE_SIZE >= aspace->base holds.
     */
    if (aspace->base > (vaddr_t)ptr1 - PAGE_SIZE) {
        ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr3, 0, 0,
                        ARCH_MMU_FLAG_PERM_NO_EXECUTE);
        ASSERT_EQ(NO_ERROR, ret);
        ASSERT_GE((vaddr_t)ptr3 - PAGE_SIZE, aspace->base);
        vmm_free_region(aspace, (vaddr_t)ptr1);
        ptr1 = ptr3;
        ptr3 = NULL;
    }

    /* Check that there are no existing adjacent allocations. */
    ret = vmm_get_obj(aspace, (vaddr_t)ptr1 - PAGE_SIZE, PAGE_SIZE, &slice);
    EXPECT_EQ(ERR_NOT_FOUND, ret);
    vmm_obj_slice_release(&slice);

    ret = vmm_get_obj(aspace, (vaddr_t)ptr1 + PAGE_SIZE, PAGE_SIZE, &slice);
    EXPECT_EQ(ERR_NOT_FOUND, ret);
    vmm_obj_slice_release(&slice);

    /* Check that guard pages cannot be allocated. */
    ptr2 = (void*)((vaddr_t)ptr1 - PAGE_SIZE);
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD |
                            VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    ptr2 = (void*)((vaddr_t)ptr1 + PAGE_SIZE);
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD |
                            VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    ptr2 = NULL;
    vmm_free_region(aspace, (vaddr_t)ptr1);
    ptr1 = NULL;

    /* Check that we cannot allocate at a random spot without guard page */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr1, 0,
                    VMM_FLAG_NO_START_GUARD | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_INVALID_ARGS, ret);

    /* Find a range to to more specific tests in. */
    retb = vmm_find_spot(aspace, size, &base);
    ASSERT_EQ(true, retb, "failed to find region for test\n");

    /* Allocate first test page. */
    ptr1 = (void*)base;
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr1, 0,
                    VMM_FLAG_VALLOC_SPECIFIC, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret) {
        /*
         * This allocation can fail if another thread allocated the page after
         * vmm_find_spot returned as that call does not reserve the memory.
         * Set ptr1 to NULL so we don't free memory belonging to someone else.
         */
        ptr1 = NULL;
    }
    ASSERT_EQ(NO_ERROR, ret);

    /* Test adjacent page. Should all fail as ptr1 has guard on both sides. */
    ptr2 = (void*)(base + PAGE_SIZE);

    /* No flags. Should fail as both regions have a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0,
                    VMM_FLAG_VALLOC_SPECIFIC, 0);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No start guard. Should fail as first region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No end guard. Should fail as both regions have a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No guard pages. Should fail as first region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD |
                            VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* Allocate page after guard page with no end guard */
    ptr2 = (void*)(base + PAGE_SIZE * 2);
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr2, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret) {
        ptr2 = NULL;
    }
    ASSERT_EQ(NO_ERROR, ret);

    /* Test page directly after ptr2 */
    ptr3 = (void*)(base + PAGE_SIZE * 3);

    /* No flags. Should fail as second region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr3, 0,
                    VMM_FLAG_VALLOC_SPECIFIC, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No end guard. Should fail as second region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr3, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No guard pages. Should succeed as neither region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr3, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD |
                            VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret) {
        ptr3 = NULL;
    }
    ASSERT_EQ(NO_ERROR, ret);

    /* Test page directly after ptr3 */
    ptr4 = (void*)(base + PAGE_SIZE * 4);

    /* No flags. Should fail as second region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr4, 0,
                    VMM_FLAG_VALLOC_SPECIFIC, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No end guard. Should fail as second region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr4, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No start guard. Should succeed as neither region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr4, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret) {
        ptr4 = NULL;
    }
    ASSERT_EQ(NO_ERROR, ret);

    /*
     * Test page directly after ptr4. Should all fail as ptr4 has end guard.
     * Similar the test after ptr1, but checks that disabling start guard does
     * not affect end guard.
     */
    ptr5 = (void*)(base + PAGE_SIZE * 5);

    /* No flags. Should fail as both regions have a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr5, 0,
                    VMM_FLAG_VALLOC_SPECIFIC, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No start guard. Should fail as first region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr5, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No end guard. Should fail as both regions have a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr5, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* No guard pages. Should fail as first region has a guard page. */
    ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr5, 0,
                    VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD |
                            VMM_FLAG_NO_END_GUARD,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /*
     * Clear ptr5 so we don't try to free it. Not strictly needed as the guard
     * page around ptr4 will prevent anyone else from allocating memory at this
     * location, and ptr5 is freed first below, but useful if vmm tracing is
     * enabled as failing vmm_free_region calls should all be for vaddr 0.
     */
    ptr5 = NULL;

test_abort:
    vmm_free_region(aspace, (vaddr_t)ptr5);
    vmm_free_region(aspace, (vaddr_t)ptr4);
    vmm_free_region(aspace, (vaddr_t)ptr3);
    vmm_free_region(aspace, (vaddr_t)ptr2);
    vmm_free_region(aspace, (vaddr_t)ptr1);
}

TEST_P(mmutestaspace, find_slice_no_guard) {
    int ret;
    bool retb;
    vmm_aspace_t* aspace = _state->aspace;
    void* ptr[8];
    size_t num_regions = countof(ptr);
    size_t size = PAGE_SIZE * num_regions;
    vaddr_t base;
    uint vmm_flags = VMM_FLAG_VALLOC_SPECIFIC | VMM_FLAG_NO_START_GUARD |
                     VMM_FLAG_NO_END_GUARD;
    struct vmm_obj_slice slice;
    vmm_obj_slice_init(&slice);

    for (size_t i = 0; i < num_regions; i++) {
        ptr[i] = NULL;
    }

    retb = vmm_find_spot(aspace, size, &base);
    ASSERT_EQ(true, retb, "failed to find region for test\n");

    for (int i = num_regions - 1; i >= 0; --i) {
        ptr[i] = (void*)(base + PAGE_SIZE * i);
        ret = vmm_alloc(aspace, "mmutest", PAGE_SIZE, &ptr[i], 0, vmm_flags,
                        ARCH_MMU_FLAG_PERM_NO_EXECUTE);
        if (ret) {
            ptr[i] = NULL;
        }

        if (ptr[i]) {
            /* Test that we can find slice corresponding to allocated page. */
            ret = vmm_get_obj(aspace, (vaddr_t)ptr[i], PAGE_SIZE, &slice);
            ASSERT_EQ(NO_ERROR, ret);
            vmm_obj_slice_release(&slice);
        }
    }

test_abort:
    for (size_t i = 0; i < num_regions; i++) {
        vmm_free_region(aspace, (vaddr_t)ptr[i]);
    }
}

INSTANTIATE_TEST_SUITE_P(aspacetype,
                         mmutestaspace,
                         /* user(false) and kernel(true) aspaces */
                         testing_Bool());

TEST(mmutest, check_stack_guard_page_bad_ptr)
__attribute__((no_sanitize("bounds"))) {
    char data[4];
    void* ptr1 = data;
    void* ptr2 = data - DEFAULT_STACK_SIZE;
    EXPECT_EQ(NO_ERROR, mmutest_arch_store_uint32(ptr1, false));
    EXPECT_EQ(ERR_GENERIC, mmutest_arch_store_uint32(ptr2, false));
}

static int mmutest_stack_overflow_thread_func(void* arg) {
    char data[DEFAULT_STACK_SIZE] __attribute((uninitialized));
    void* ptr = data;
    mmutest_arch_store_uint32(ptr, false);
    return 0;
}

TEST(mmutest, check_stack_guard_page_stack_overflow) {
    EXPECT_EQ(ERR_FAULT,
              mmutest_run_in_thread("stack-overflow",
                                    mmutest_stack_overflow_thread_func, NULL));
}

static int mmutest_recursive_stack_overflow_thread_func(void* arg) {
    char b;
    if ((vaddr_t)arg == 1) {
        return 0;
    }
    return mmutest_recursive_stack_overflow_thread_func(&b) + 1;
}

TEST(mmutest, check_stack_guard_page_recursive_stack_overflow) {
    EXPECT_EQ(ERR_FAULT,
              mmutest_run_in_thread(
                      "stack-overflow",
                      mmutest_recursive_stack_overflow_thread_func, 0));
}

TEST(mmutest, DISABLED_ON_ARM_NAME(rodata_pnx)) {
    EXPECT_EQ(ERR_FAULT, mmutest_arch_rodata_pnx());
}

TEST(mmutest, DISABLED_ON_ARM_NAME(data_pnx)) {
    EXPECT_EQ(ERR_FAULT, mmutest_arch_data_pnx());
}

TEST(mmutest, DISABLED_ON_ARM_NAME(rodata_ro)) {
    EXPECT_EQ(ERR_FAULT, mmutest_arch_rodata_ro());
}

TEST(mmutest, pan) {
    if (!mmutest_arch_pan_supported()) {
        trusty_unittest_printf("[   INFO   ] PAN is not supported\n");
        GTEST_SKIP();
    }
    EXPECT_EQ(true, mmutest_arch_pan_enabled());
test_abort:;
}

TEST(mmutest, store_kernel) {
    int expected_user_rw_access;
    int expected_user_ro_access;

    if (mmutest_arch_pan_enabled()) {
        expected_user_rw_access = ERR_GENERIC;
        expected_user_ro_access = ERR_GENERIC;
    } else {
        expected_user_rw_access = 0;
        expected_user_ro_access = ERR_FAULT;
    }

    EXPECT_EQ(NO_ERROR,
              mmutest_vmm_store_uint32_kernel(ARCH_MMU_FLAG_CACHED |
                                              ARCH_MMU_FLAG_PERM_NO_EXECUTE));
    EXPECT_EQ(expected_user_rw_access,
              mmutest_vmm_store_uint32_kernel(ARCH_MMU_FLAG_CACHED |
                                              ARCH_MMU_FLAG_PERM_NO_EXECUTE |
                                              ARCH_MMU_FLAG_PERM_USER));
    EXPECT_EQ(NO_ERROR,
              mmutest_vmm_store_uint32_kernel(ARCH_MMU_FLAG_CACHED |
                                              ARCH_MMU_FLAG_PERM_NO_EXECUTE));
    EXPECT_EQ(expected_user_rw_access,
              mmutest_vmm_store_uint32_kernel(ARCH_MMU_FLAG_CACHED |
                                              ARCH_MMU_FLAG_PERM_NO_EXECUTE |
                                              ARCH_MMU_FLAG_PERM_USER));
    EXPECT_EQ(ERR_FAULT, mmutest_vmm_store_uint32_kernel(
                                 ARCH_MMU_FLAG_CACHED | ARCH_MMU_FLAG_PERM_RO));
    EXPECT_EQ(expected_user_ro_access,
              mmutest_vmm_store_uint32_kernel(ARCH_MMU_FLAG_CACHED |
                                              ARCH_MMU_FLAG_PERM_RO |
                                              ARCH_MMU_FLAG_PERM_USER));
}

TEST(mmutest, store_user) {
    EXPECT_EQ(ERR_GENERIC,
              mmutest_vmm_store_uint32_user(ARCH_MMU_FLAG_CACHED |
                                            ARCH_MMU_FLAG_PERM_NO_EXECUTE));
    EXPECT_EQ(NO_ERROR,
              mmutest_vmm_store_uint32_user(ARCH_MMU_FLAG_CACHED |
                                            ARCH_MMU_FLAG_PERM_NO_EXECUTE |
                                            ARCH_MMU_FLAG_PERM_USER));
    EXPECT_EQ(ERR_GENERIC,
              mmutest_vmm_store_uint32_user(ARCH_MMU_FLAG_CACHED |
                                            ARCH_MMU_FLAG_PERM_NO_EXECUTE));
    EXPECT_EQ(NO_ERROR,
              mmutest_vmm_store_uint32_user(ARCH_MMU_FLAG_CACHED |
                                            ARCH_MMU_FLAG_PERM_NO_EXECUTE |
                                            ARCH_MMU_FLAG_PERM_USER));
    EXPECT_EQ(ERR_GENERIC,
              mmutest_vmm_store_uint32_user(ARCH_MMU_FLAG_CACHED |
                                            ARCH_MMU_FLAG_PERM_RO));
    EXPECT_EQ(ERR_FAULT, mmutest_vmm_store_uint32_user(
                                 ARCH_MMU_FLAG_CACHED | ARCH_MMU_FLAG_PERM_RO |
                                 ARCH_MMU_FLAG_PERM_USER));
}

/*
 * The current implementation of this test checks checks that the data is lost
 * when reading back from memory, but allows the store to reach the cache. This
 * is not the only allowed behavior and the emulator does not emulate this
 * behavior, so disable this test for now.
 */
TEST(mmutest, DISABLED_store_ns) {
    EXPECT_EQ(2, mmutest_vmm_store_uint32_kernel(ARCH_MMU_FLAG_CACHED |
                                                 ARCH_MMU_FLAG_NS));
    EXPECT_EQ(2, mmutest_vmm_store_uint32_kernel(ARCH_MMU_FLAG_CACHED |
                                                 ARCH_MMU_FLAG_NS |
                                                 ARCH_MMU_FLAG_PERM_USER));
    EXPECT_EQ(ERR_GENERIC, mmutest_vmm_store_uint32_user(ARCH_MMU_FLAG_CACHED |
                                                         ARCH_MMU_FLAG_NS));
    EXPECT_EQ(2, mmutest_vmm_store_uint32_user(ARCH_MMU_FLAG_CACHED |
                                               ARCH_MMU_FLAG_NS |
                                               ARCH_MMU_FLAG_PERM_USER));
}

TEST(mmutest, run_x) {
    EXPECT_EQ(NO_ERROR, mmu_test_execute(ARCH_MMU_FLAG_PERM_RO));
}

#if ARCH_ARM64
#include <arch/arm64/sregs.h>

TEST(mmutest, run_wx) {
    vmm_aspace_t* aspace = vmm_get_kernel_aspace();
    struct obj_ref vmm_obj_ref = OBJ_REF_INITIAL_VALUE(vmm_obj_ref);
    struct vmm_obj* vmm_obj = NULL;
    void* ptr = NULL;
    int ret;

    /* Allocate a single page */
    ret = pmm_alloc(&vmm_obj, &vmm_obj_ref, 1, PMM_ALLOC_FLAG_CONTIGUOUS, 0);
    ASSERT_EQ(NO_ERROR, ret, "pmm_alloc failed\n");

    /* Try to map as w+x and check it fails */
    ret = vmm_alloc_obj(aspace, "mmutest_wx", vmm_obj, 0, PAGE_SIZE, &ptr, 0, 0,
                        0);
    EXPECT_EQ(ERR_INVALID_ARGS, ret);

    /*
     * ARM64 should have WXN enabled.
     * This means that any writable page is NX irrespective of the PTE entry.
     */
    EXPECT_EQ(SCTLR_EL1_WXN, ARM64_READ_SYSREG(SCTLR_EL1) & SCTLR_EL1_WXN);

test_abort:
    if (vmm_obj) {
        vmm_obj_del_ref(vmm_obj, &vmm_obj_ref);
    }
}
#else
TEST(mmutest, run_wx) {
    EXPECT_EQ(NO_ERROR, mmu_test_execute(0));
}
#endif

TEST(mmutest, run_nx) {
    EXPECT_EQ(ERR_FAULT, mmu_test_execute(ARCH_MMU_FLAG_PERM_NO_EXECUTE));
}

/*
 * Tests that allocations with conflicting NS bits are not allowed
 * near each other
 */
TEST(mmutest, ns_conflict) {
    int ret;
    void* ptr_ns = NULL;
    void* ptr_s = NULL;
    uint arch_mmu_flags_query, ns_flag;
    vmm_aspace_t* aspace = vmm_get_kernel_aspace();

    /*
     * Allocate a NS page with a 16K alignment to ensure that there
     * is enough room after it in the 1MB section for both the guard page
     * and the S page below.
     */
    ret = vmm_alloc(aspace, "ns_conflict_ns", PAGE_SIZE, &ptr_ns,
                    PAGE_SIZE_SHIFT + 2, 0,
                    ARCH_MMU_FLAG_NS | ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret == ERR_NOT_SUPPORTED) {
        GTEST_SKIP();
    }
    EXPECT_EQ(NO_ERROR, ret);

    ret = arch_mmu_query(&aspace->arch_aspace, (vaddr_t)ptr_ns, NULL,
                         &arch_mmu_flags_query);
    EXPECT_EQ(NO_ERROR, ret);

    ns_flag = arch_mmu_flags_query & ARCH_MMU_FLAG_NS;
    EXPECT_EQ(ARCH_MMU_FLAG_NS, ns_flag);

    /*
     * Allocate an S page just after the previous one (plus the guard page).
     * This should fail on arm32 because the kernel shouldn't let us mix the
     * two kinds.
     */
    ptr_s = (uint8_t*)ptr_ns + 2 * PAGE_SIZE;
    ret = vmm_alloc(aspace, "ns_conflict_s", PAGE_SIZE, &ptr_s, PAGE_SIZE_SHIFT,
                    VMM_FLAG_VALLOC_SPECIFIC, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    if (ret) {
        ptr_s = NULL;
    } else {
        ret = arch_mmu_query(&aspace->arch_aspace, (vaddr_t)ptr_s, NULL,
                             &arch_mmu_flags_query);
        if (!ret) {
            ns_flag = arch_mmu_flags_query & ARCH_MMU_FLAG_NS;
            EXPECT_EQ(NO_ERROR, ns_flag);
        }
    }

test_abort:
    if (ptr_ns) {
        vmm_free_region(aspace, (vaddr_t)ptr_ns);
    }
    if (ptr_s) {
        vmm_free_region(aspace, (vaddr_t)ptr_s);
    }
}

/* Test suite for vmm_obj_slice and vmm_get_obj */

typedef struct {
    vmm_aspace_t* aspace;
    vaddr_t spot_a_2_page;
    vaddr_t spot_b_1_page;
    struct vmm_obj_slice slice;
} mmutest_slice_t;

TEST_F_SETUP(mmutest_slice) {
    _state->aspace = vmm_get_kernel_aspace();
    _state->spot_a_2_page = 0;
    _state->spot_b_1_page = 0;
    vmm_obj_slice_init(&_state->slice);
    ASSERT_EQ(vmm_alloc(_state->aspace, "mmutest_slice", 2 * PAGE_SIZE,
                        (void**)&_state->spot_a_2_page, 0, 0,
                        ARCH_MMU_FLAG_PERM_NO_EXECUTE),
              NO_ERROR);
    ASSERT_EQ(vmm_alloc(_state->aspace, "mmutest_slice", PAGE_SIZE,
                        (void**)&_state->spot_b_1_page, 0, 0,
                        ARCH_MMU_FLAG_PERM_NO_EXECUTE),
              NO_ERROR);
test_abort:;
}

TEST_F_TEARDOWN(mmutest_slice) {
    vmm_obj_slice_release(&_state->slice);
    if (_state->spot_a_2_page) {
        vmm_free_region(_state->aspace, (vaddr_t)_state->spot_a_2_page);
    }

    if (_state->spot_b_1_page) {
        vmm_free_region(_state->aspace, (vaddr_t)_state->spot_b_1_page);
    }
}

/*
 * Simplest use of interface - get the slice for a mapped region,
 * of the whole size
 */
TEST_F(mmutest_slice, simple) {
    ASSERT_EQ(vmm_get_obj(_state->aspace, _state->spot_b_1_page, PAGE_SIZE,
                          &_state->slice),
              NO_ERROR);
    EXPECT_EQ(_state->slice.offset, 0);
    EXPECT_EQ(_state->slice.size, PAGE_SIZE);
test_abort:;
}

/* Validate that we will reject an attempt to span two slices */
TEST_F(mmutest_slice, two_objs) {
    vaddr_t base;
    size_t size;
    vaddr_t spot_a = _state->spot_a_2_page;
    vaddr_t spot_b = _state->spot_b_1_page;

    base = MIN(spot_a, spot_b);
    size = MAX(spot_a, spot_b) - base + PAGE_SIZE;

    /* We should not be able to create a slice spanning both objects */
    EXPECT_EQ(vmm_get_obj(_state->aspace, base, size, &_state->slice),
              ERR_OUT_OF_RANGE);

test_abort:;
}

/* Check we can acquire a subslice of a mapped object */
TEST_F(mmutest_slice, subobj) {
    ASSERT_EQ(vmm_get_obj(_state->aspace, _state->spot_a_2_page + PAGE_SIZE,
                          PAGE_SIZE, &_state->slice),
              NO_ERROR);

    EXPECT_EQ(_state->slice.offset, PAGE_SIZE);
    EXPECT_EQ(_state->slice.size, PAGE_SIZE);

test_abort:;
}

/* Check for rejection of the requested range overflows */
TEST_F(mmutest_slice, overflow) {
    EXPECT_EQ(vmm_get_obj(_state->aspace, _state->spot_a_2_page, SIZE_MAX,
                          &_state->slice),
              ERR_INVALID_ARGS);
}

/* Test suite for PMM */

#define RESERVE_PAGES 500

typedef struct {
    vmm_aspace_t* aspace;
} mmutest_pmm_t;

TEST_F_SETUP(mmutest_pmm) {
    _state->aspace = NULL;
    status_t ret = vmm_create_aspace_with_quota(&_state->aspace, "mmutestpmm",
                                                PAGE_SIZE * 2, 0);
    ASSERT_EQ(NO_ERROR, ret);
test_abort:;
}

TEST_F_TEARDOWN(mmutest_pmm) {
    if (_state->aspace) {
        ASSERT_EQ(NO_ERROR, vmm_free_aspace(_state->aspace));
    }
test_abort:;
}

static uint probe_max_aspace_quota_pages(void) {
    struct vmm_aspace* probe_aspace = NULL;
    uint alloc_pages = 4096;
    uint alloc_step = 4096;
    status_t ret;

    do {
        ret = vmm_create_aspace_with_quota(&probe_aspace, "probe_aspace",
                                           PAGE_SIZE * alloc_pages, 0);

        if (probe_aspace) {
            vmm_free_aspace(probe_aspace);
            probe_aspace = NULL;
        }

        if (ret == NO_ERROR) {
            alloc_pages += alloc_step;
        } else if (alloc_step) {
            alloc_pages -= alloc_step;
            alloc_step = alloc_step / 2;
        } else {
            alloc_pages--;
        }

    } while (alloc_step > 0 || ret != NO_ERROR);

    return alloc_pages;
}

/*
 * Reserve physical pages and allocate from reserved memory.
 */
TEST_F(mmutest_pmm, reserve) {
    void* ptr = NULL;
    void* ptr_unused = NULL;
    status_t ret;
    struct vmm_aspace* temp_aspace = NULL;
    uint max_pages, temp_aspace_pages;

    /* Allocate virtual space without quota or pmm, which should pass */
    ret = vmm_alloc(_state->aspace, "test_reserve",
                    PAGE_SIZE * (RESERVE_PAGES + 2), &ptr, 0,
                    VMM_FLAG_NO_PHYSICAL, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);

    /* Allocate all quota pages at previous virtual address */
    ret = vmm_alloc(_state->aspace, "test_from_reserved", PAGE_SIZE * 2, &ptr,
                    0, VMM_FLAG_QUOTA | VMM_FLAG_VALLOC_SPECIFIC,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);

    /* Check the maximum quota that can be allocated to an aspace */
    max_pages = probe_max_aspace_quota_pages();
    ASSERT_GT(max_pages, RESERVE_PAGES);

    /* Reserve most pages for temp_aspace, leaving RESERVE_PAGES / 2 free */
    temp_aspace_pages = max_pages - (RESERVE_PAGES / 2);
    ret = vmm_create_aspace_with_quota(&temp_aspace, "temp_aspace",
                                       PAGE_SIZE * temp_aspace_pages, 0);
    ASSERT_EQ(NO_ERROR, ret);

    /* Almost all pages are reserved for temp_aspace quota; this should fail */
    ret = vmm_alloc(_state->aspace, "test_failure", PAGE_SIZE * RESERVE_PAGES,
                    &ptr_unused, 0, 0, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);

    /* Allocate from the temp_aspace quota reservation; should succeed */
    ptr += PAGE_SIZE * 2;
    ret = vmm_alloc(temp_aspace, "test_from_reserved_success",
                    PAGE_SIZE * MIN(temp_aspace_pages, RESERVE_PAGES), &ptr, 0,
                    VMM_FLAG_QUOTA | VMM_FLAG_VALLOC_SPECIFIC,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
test_abort:
    if (temp_aspace)
        vmm_free_aspace(temp_aspace);
}

TEST_F(mmutest_pmm, reserve_contiguous) {
    void* ptr = NULL;
    status_t ret;
    ret = vmm_alloc(_state->aspace, "test_reserve", PAGE_SIZE * 2, &ptr, 0,
                    VMM_FLAG_NO_PHYSICAL, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
    ret = vmm_alloc_contiguous(_state->aspace, "test_from_reserved_continuous",
                               PAGE_SIZE * 2, &ptr, 0,
                               VMM_FLAG_QUOTA | VMM_FLAG_VALLOC_SPECIFIC,
                               ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
test_abort:;
}

TEST_F(mmutest_pmm, reserve_too_small) {
    void* ptr = NULL;
    status_t ret;
    ret = vmm_alloc(_state->aspace, "test_reserve", PAGE_SIZE * 2, &ptr, 0,
                    VMM_FLAG_NO_PHYSICAL, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
    ret = vmm_alloc(_state->aspace, "test_from_reserved_too_small",
                    PAGE_SIZE * 3, &ptr, 0,
                    VMM_FLAG_QUOTA | VMM_FLAG_VALLOC_SPECIFIC,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);
test_abort:;
}

TEST_F(mmutest_pmm, reserve_outside_region) {
    void* ptr = NULL;
    status_t ret;
    ret = vmm_alloc(_state->aspace, "test_reserve", PAGE_SIZE * 2, &ptr, 0,
                    VMM_FLAG_NO_PHYSICAL, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
    ptr += PAGE_SIZE;
    ret = vmm_alloc(_state->aspace, "test_from_reserved_outside_region",
                    PAGE_SIZE * 2, &ptr, 0,
                    VMM_FLAG_QUOTA | VMM_FLAG_VALLOC_SPECIFIC,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_INVALID_ARGS, ret);
test_abort:;
}

/* Test suite for PMM */

typedef struct {
    vmm_aspace_t* aspace;
} mmutest_res_group_t;

TEST_F_SETUP(mmutest_res_group) {
    _state->aspace = NULL;
    status_t ret = vmm_create_aspace_with_quota(&_state->aspace, "mmutestrg",
                                                PAGE_SIZE, 0);
    ASSERT_EQ(NO_ERROR, ret);
test_abort:;
}

TEST_F_TEARDOWN(mmutest_res_group) {
    if (_state->aspace) {
        ASSERT_EQ(NO_ERROR, vmm_free_aspace(_state->aspace));
    }
test_abort:;
}

TEST_F(mmutest_res_group, reserve_group_too_big) {
    void* ptr;
    status_t ret = vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE + 1, &ptr,
                             0, VMM_FLAG_QUOTA, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);
test_abort:;
}

TEST_F(mmutest_res_group, reserve_group_release_ref) {
    /* Destroying an aspace releases refs on its vmm_objs. */
    status_t slice_init = ERR_INVALID_ARGS;
    void* ptr;
    struct vmm_obj_slice slice;
    vmm_obj_slice_init(&slice);
    status_t alloc_ret =
            vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE, &ptr, 0,
                      VMM_FLAG_QUOTA, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, alloc_ret);
    slice_init = vmm_get_obj(_state->aspace, (vaddr_t)ptr, PAGE_SIZE, &slice);
    ASSERT_EQ(NO_ERROR, slice_init);
    ASSERT_EQ(NO_ERROR, vmm_free_aspace(_state->aspace));
    _state->aspace = NULL;
    ASSERT_EQ(true, obj_has_only_ref(&slice.obj->obj, &slice.obj_ref));
    vmm_obj_slice_release(&slice);
test_abort:;
}

TEST_F(mmutest_res_group, no_physical_inner_obj) {
    void* ptr;
    struct vmm_obj_slice slice;
    vmm_obj_slice_init(&slice);
    status_t ret = vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE * 2, &ptr,
                             0, VMM_FLAG_QUOTA | VMM_FLAG_NO_PHYSICAL,
                             ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ret = vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE, &ptr, 0,
                    VMM_FLAG_QUOTA | VMM_FLAG_VALLOC_SPECIFIC,
                    ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    /* vmm_get_obj should look inside NO_PHYSICAL regions and return nested
     * vmm_objs from inside. */
    ret = vmm_get_obj(_state->aspace, (vaddr_t)ptr, PAGE_SIZE, &slice);
    ASSERT_EQ(NO_ERROR, ret);
    ASSERT_EQ(PAGE_SIZE, slice.size);
    ASSERT_EQ(NO_ERROR, vmm_free_region(_state->aspace, (vaddr_t)ptr));
    ASSERT_EQ(true, obj_has_only_ref(&slice.obj->obj, &slice.obj_ref));
    vmm_obj_slice_release(&slice);
test_abort:;
}

TEST_F(mmutest_res_group, reserve_group_no_physical) {
    /* NO_PHYSICAL allocations don't count towards memory usage. */
    void* ptr;
    status_t ret =
            vmm_alloc(_state->aspace, "test_reserved_alloc", PAGE_SIZE * 10,
                      &ptr, 0, VMM_FLAG_QUOTA | VMM_FLAG_NO_PHYSICAL,
                      ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
    ret = vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE, &ptr, 0,
                    VMM_FLAG_QUOTA, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
    ret = vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE, &ptr, 0,
                    VMM_FLAG_QUOTA, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);
test_abort:;
}

TEST_F(mmutest_res_group, reserve_group_disable_quota) {
    /* Allocations without VMM_FLAG_QUOTA set don't count towards memory usage.
     */
    void* ptr;
    status_t ret =
            vmm_alloc(_state->aspace, "test_reserved_alloc", PAGE_SIZE * 10,
                      &ptr, 0, 0, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
    ret = vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE, &ptr, 0,
                    VMM_FLAG_QUOTA, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(NO_ERROR, ret);
    ret = vmm_alloc(_state->aspace, "test_alloc", PAGE_SIZE, &ptr, 0,
                    VMM_FLAG_QUOTA, ARCH_MMU_FLAG_PERM_NO_EXECUTE);
    ASSERT_EQ(ERR_NO_MEMORY, ret);
test_abort:;
}

PORT_TEST(mmutest, "com.android.kernel.mmutest");
