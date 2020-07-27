define is_ccu_supported
$(shell $(CCU_TOOL_CUSTFUNC_DIR)/extractor $1>/dev/null && echo $1)
endef

INPUT := 1 $(custfunc_src_path)/inc/aaa/ae_custom_transform.h 1 $(custfunc_src_path)/camera_3a/ae_custom_transform.cpp 
$(info cust_func: is_ccu_supported = $(INPUT))


LOCAL_MODULE := libccu_custfunc

LOCAL_MODULE_CLASS := GYP
intermediates := $(call intermediates-dir-for,$(LOCAL_MODULE_CLASS),$(LOCAL_MODULE),,,$(if $(TARGET_2ND_ARCH),$(TARGET_2ND_ARCH_VAR_PREFIX)))
ifeq ($(strip $(intermediates)),)
  intermediates := out/target/product/$(MTK_TARGET_PROJECT)/obj_arm/$(LOCAL_MODULE_CLASS)/$(LOCAL_MODULE)_intermediates
endif

GEN := $(intermediates)/libccu_custfunc.c

LOCAL_GENERATED_SOURCES += $(GEN)
my_ccu_generated_sources := $(my_ccu_generated_sources) $(GEN)

$(GEN): PRIVATE_INPUT := $(INPUT)
$(GEN): $(cfile) $(CCU_TOOL_CUSTFUNC_DIR)/extractor
	$(info  Extract $@:)
	$(hide) mkdir -p $(dir $@)
	$(hide) rm -f $@
	$(CCU_TOOL_CUSTFUNC_DIR)/extractor $(PRIVATE_INPUT) $@