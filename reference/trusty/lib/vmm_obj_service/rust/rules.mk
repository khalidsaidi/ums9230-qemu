LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_CRATE_NAME := vmm_obj_service_rust

MODULE_SRCS += \
	$(LOCAL_DIR)/src/lib.rs \

MODULE_LIBRARY_DEPS += \
	$(call FIND_CRATE,log) \
	$(call FIND_CRATE,zerocopy) \
	packages/modules/Virtualization/libs/libfdt \
	trusty/user/base/lib/trusty-std \

include make/library.mk
