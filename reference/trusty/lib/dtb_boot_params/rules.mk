ifeq ($(SUBARCH),x86-64)

LOCAL_DIR := $(GET_LOCAL_DIR)
MODULE := $(LOCAL_DIR)
MODULE_CRATE_NAME := dtb_boot_params
MODULE_SRCS += \
	$(LOCAL_DIR)/src/lib.rs \

MODULE_LIBRARY_DEPS += \
	$(call FIND_CRATE,log) \
	$(call FIND_CRATE,zerocopy) \
	$(call FIND_CRATE,thiserror) \

MODULE_RUST_USE_CLIPPY := true

include make/library.mk

endif
