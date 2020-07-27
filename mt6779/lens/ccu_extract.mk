my_ccu_lens := $(strip $(my_ccu_lens))

ifeq ($(my_ccu_lens),)
  $(error my_ccu_lens is not defined)
endif

define is_ccu_supported
$(shell $(CCU_TOOL_LENS_DIR)/extractor $1>/dev/null && echo $1)
endef

ifneq ($(wildcard $(my_lens_path)/$(my_ccu_lens)),)
  my_ccu_src_path = $(my_lens_path)
endif

cfile := $(shell find $(my_lens_path)/$(my_ccu_lens) -name '*.c')
hfile := $(shell find $(my_lens_path)/$(my_ccu_lens) -name '*.h')
INPUT := $(words $(hfile)) $(sort $(hfile)) $(words $(cfile)) $(sort $(cfile))

$(info $(my_ccu_lens): is_ccu_supported = $(INPUT))

m := $(call UpperCase,$(my_ccu_lens))
# reset LOCAL_MODULE for each lens
LOCAL_MODULE := $(MY_CCU_DRVNAME_$(m))

LOCAL_MODULE_CLASS := GYP
intermediates := $(call intermediates-dir-for,$(LOCAL_MODULE_CLASS),$(LOCAL_MODULE),,,$(if $(TARGET_2ND_ARCH),$(TARGET_2ND_ARCH_VAR_PREFIX)))
ifeq ($(strip $(intermediates)),)
  intermediates := out/target/product/$(MTK_TARGET_PROJECT)/obj_arm/$(LOCAL_MODULE_CLASS)/$(LOCAL_MODULE)_intermediates
endif

GEN := $(intermediates)/$(MY_CCU_DRVNAME_$(m)).c

LOCAL_GENERATED_SOURCES += $(GEN)
my_ccu_generated_sources := $(my_ccu_generated_sources) $(GEN)

$(GEN): PRIVATE_INPUT := $(INPUT)
$(GEN):  $(hfile) $(cfile) $(CCU_TOOL_LENS_DIR)/extractor
	@echo Extract $@:
	$(hide) mkdir -p $(dir $@)
	$(hide) rm -f $@
	$(CCU_TOOL_LENS_DIR)/extractor $(PRIVATE_INPUT) $@
