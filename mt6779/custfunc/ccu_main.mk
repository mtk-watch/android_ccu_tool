custfunc_src_path  ?= $(TOP)/vendor/mediatek/proprietary/custom/$(MTK_PLATFORM_DIR)/hal
custfunc_common_header_path  ?= $(TOP)/vendor/mediatek/proprietary/custom/common/hal/inc
my_ccu_src_path :=


MTK_CCU_TOOLCHAIN_VERSION := arc
my_ccu_binary_mk := $(CCU_TOOL_CUSTFUNC_DIR)/ccu_$(strip $(MTK_CCU_TOOLCHAIN_VERSION))_binary.mk

# max ELF code size in byte for split
MAX_SIZE_PM ?= 4096
MAX_SIZE_DM ?= 2048
MAX_SIZE_ALL ?= 16384

$(if $(BUILD_SYSTEM),$(eval include $(CLEAR_VARS)))\
$(eval include $(CCU_TOOL_CUSTFUNC_DIR)/ccu_extract.mk)\
$(if $(BUILD_SYSTEM),$(eval include $(my_ccu_binary_mk)))\

