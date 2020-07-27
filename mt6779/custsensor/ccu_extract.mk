my_ccu_sensor := $(strip $(my_ccu_sensor))

ifeq ($(my_ccu_sensor),)
  $(error my_ccu_sensor is not defined)
endif

define is_ccu_supported
$(shell $(CCU_TOOL_CUSTSENSOR_DIR)/extractor $1>/dev/null && echo $1)
endef

my_ccu_src_path = $(sensor_driver_src_custsensor)


cfile := $(shell find $(my_ccu_src_path)/$(my_ccu_sensor) -name 'camera_AE_custom_transform.cpp')
INPUT := 0 1 $(cfile)
$(info $(my_ccu_sensor): is_ccu_supported = $(INPUT))


m := $(call UpperCase,$(my_ccu_sensor))
# reset LOCAL_MODULE for each sensor
LOCAL_MODULE := $(MY_CCU_DRVNAME_$(m))_custsensor

LOCAL_MODULE_CLASS := GYP
intermediates := $(call intermediates-dir-for,$(LOCAL_MODULE_CLASS),$(LOCAL_MODULE),,,$(if $(TARGET_2ND_ARCH),$(TARGET_2ND_ARCH_VAR_PREFIX)))
ifeq ($(strip $(intermediates)),)
  intermediates := out/target/product/$(MTK_TARGET_PROJECT)/obj_arm/$(LOCAL_MODULE_CLASS)/$(LOCAL_MODULE)_intermediates
endif

GEN := $(intermediates)/$(MY_CCU_DRVNAME_$(m)).c

LOCAL_GENERATED_SOURCES += $(GEN)
my_ccu_generated_sources := $(my_ccu_generated_sources) $(GEN)

$(GEN): PRIVATE_INPUT := $(INPUT)
$(GEN): $(cfile) $(CCU_TOOL_CUSTSENSOR_DIR)/extractor
	$(info  Extract $@:)
	$(hide) mkdir -p $(dir $@)
	$(hide) rm -f $@
	$(CCU_TOOL_CUSTSENSOR_DIR)/extractor $(PRIVATE_INPUT) $@