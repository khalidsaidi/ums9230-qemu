LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_CRATE_NAME := platform_generic_x86_64

MODULE_SRCS += \
	$(LOCAL_DIR)/src/lib.rs \

MODULE_LIBRARY_DEPS += \
	$(call FIND_CRATE,acpi) \
	$(call FIND_CRATE,log) \
	dev/virtio/vsock-rust \

include make/library.mk
