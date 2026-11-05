#
# Copyright (c) 2015, Google, Inc. All rights reserved
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ifeq (false,$(call TOBOOL,$(KERNEL_32BIT)))
ARCH := arm64
else
ARCH := arm
endif
ARM_CPU := armv8-a
WITH_SMP := 1

ifeq (false,$(call TOBOOL,$(HAFNIUM)))
ifneq (2,$(GIC_VERSION))
ARM_MERGE_FIQ_IRQ := true
endif
endif

MEMBASE ?= 0
MEMSIZE ?= 1

GLOBAL_INCLUDES += \
	$(LOCAL_DIR)/include

ifeq (true,$(call TOBOOL,$(HAFNIUM)))
MODULE_DEFINES += HAFNIUM=1
MODULE_DEPS += dev/interrupt/hafnium
MODULE_INCLUDES += \
	external/hafnium/inc/vmapi \
	external/hafnium/src/arch/aarch64/inc
else
MODULE_DEFINES += GIC_VERSION=$(GIC_VERSION)
MODULE_DEPS += dev/interrupt/arm_gic
endif

GENERIC_ARM64_DEBUG ?= SMC_DEBUG_PUTC
GLOBAL_DEFINES += GENERIC_ARM64_DEBUG_$(GENERIC_ARM64_DEBUG)=1

MODULE_SRCS += \
	$(LOCAL_DIR)/debug.c \
	$(LOCAL_DIR)/dtb.c \
	$(LOCAL_DIR)/platform.c \
	$(LOCAL_DIR)/smc.c \

# smc.h uses a header here, but does not depend on anything else in lib/sm
MODULE_INCLUDES += \
	$(TRUSTY_TOP)/trusty/kernel/lib/sm/include \

MODULE_DEPS += \
	dev/timer/arm_generic \

# vsock-rust only supports aarch64 (and x86_64)
MODULE_DEPS += \
	dev/virtio/vsock-rust \

GLOBAL_DEFINES += \
	MEMBASE=$(MEMBASE) \
	MEMSIZE=$(MEMSIZE) \
	MMU_WITH_TRAMPOLINE=1

LINKER_SCRIPT += \
	$(BUILDDIR)/system-onesegment.ld

# SMC service support
MODULE_INCLUDES += \
	$(TRUSTY_TOP)/trusty/kernel/services/smc/include \
	$(TRUSTY_TOP)/trusty/kernel/include \
	$(TRUSTY_TOP)/trusty/user/base/lib/smc/include \

MODULE_SRCS += \
	$(LOCAL_DIR)/smc_service_access_policy.c \

MODULE_DEPS += \
	$(LKROOT)/lib/device_tree \
	trusty/kernel/lib/dtb_embedded \
	trusty/kernel/lib/dtb_service \
	trusty/kernel/lib/ktipc \

ifeq ($(GENERIC_ARM64_DEBUG),FFA)
MODULE_DEPS += trusty/kernel/lib/arm_ffa
endif

# MMIO Guard support
MMIO_GUARD_ENABLED ?= false
ifeq (true,$(call TOBOOL,$(MMIO_GUARD_ENABLED)))
MODULE_DEPS += \
	$(LKROOT)/lib/libhypervisor

MODULE_DEFINES += MMIO_GUARD_ENABLED=1
endif

include make/module.mk
