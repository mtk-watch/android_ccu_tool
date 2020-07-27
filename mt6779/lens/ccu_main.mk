ifneq ($(wildcard $(LINUX_KERNEL_VERSION)),)
my_ccu_kernel_path ?= $(LINUX_KERNEL_VERSION)
else
my_ccu_kernel_path ?= kernel
endif

#Priority: project > platform > common
lens_driver_main_dir := $(my_ccu_kernel_path)/drivers/misc/mediatek/lens/main/common
lens_driver_main2_dir := $(my_ccu_kernel_path)/drivers/misc/mediatek/lens/main2/common
lens_driver_main3_dir := $(my_ccu_kernel_path)/drivers/misc/mediatek/lens/main3/common
lens_driver_sub_dir := $(my_ccu_kernel_path)/drivers/misc/mediatek/lens/sub/common
lens_driver_sub2_dir := $(my_ccu_kernel_path)/drivers/misc/mediatek/lens/sub2/common
my_ccu_src_path :=

MTK_CCU_TOOLCHAIN_VERSION := arc
#MTK_CCU_TOOLCHAIN_VERSION := ccmd32
my_ccu_binary_mk := $(CCU_TOOL_LENS_DIR)/ccu_$(strip $(MTK_CCU_TOOLCHAIN_VERSION))_binary.mk


ifneq ($(wildcard $(my_ccu_kernel_path)/drivers/misc/mediatek/lens/),)

$(foreach m,LOCAL_PATH my_ccu_kernel_path,$(if $(wildcard $($(m))),,$(error $(m)=$($(m)) does not exist)))

UpperCase = $(subst a,A,$(subst b,B,$(subst c,C,$(subst d,D,$(subst e,E,$(subst f,F,$(subst g,G,$(subst h,H,$(subst i,I,$(subst j,J,$(subst k,K,$(subst l,L,$(subst m,M,$(subst n,N,$(subst o,O,$(subst p,P,$(subst q,Q,$(subst r,R,$(subst s,S,$(subst t,T,$(subst u,U,$(subst v,V,$(subst w,W,$(subst x,X,$(subst y,Y,$(subst z,Z,$(1)))))))))))))))))))))))))))

# max ELF code size in byte for split
MAX_SIZE_PM ?= 4096
MAX_SIZE_DM ?= 2048
MAX_SIZE_ALL ?= 16384

main_lens := $(sort $(patsubst %/ ,% ,$(dir $(wildcard $(lens_driver_main_dir)/*/))))
$(foreach c, $(main_lens), \
	$(eval my_ccu_lens := $(strip $(notdir $(patsubst %/,%,$(c))))) \
	$(eval MY_CCU_DRVNAME_$(call UpperCase,$(my_ccu_lens))=libccu_$(my_ccu_lens)_main) \
)

$(eval my_lens_path := $(lens_driver_main_dir))
$(foreach c,$(main_lens),\
	$(eval my_ccu_lens := $(notdir $(patsubst %/,%,$(c))))\
	$(if $(BUILD_SYSTEM),$(eval include $(CLEAR_VARS)))\
	$(eval include $(CCU_TOOL_LENS_DIR)/ccu_extract.mk)\
	$(if $(BUILD_SYSTEM),$(eval include $(my_ccu_binary_mk)))\
)

main2_lens := $(sort $(patsubst %/ ,% ,$(dir $(wildcard $(lens_driver_main2_dir)/*/))))
$(foreach c, $(main2_lens), \
    $(eval my_ccu_lens := $(strip $(notdir $(patsubst %/,%,$(c))))) \
    $(eval MY_CCU_DRVNAME_$(call UpperCase,$(my_ccu_lens))=libccu_$(my_ccu_lens)_main2) \
)
$(eval my_lens_path := $(lens_driver_main2_dir))
$(foreach c,$(main2_lens),\
    $(eval my_ccu_lens := $(notdir $(patsubst %/,%,$(c))))\
    $(if $(BUILD_SYSTEM),$(eval include $(CLEAR_VARS)))\
    $(eval include $(CCU_TOOL_LENS_DIR)/ccu_extract.mk)\
    $(if $(BUILD_SYSTEM),$(eval include $(my_ccu_binary_mk)))\
)

sub_lens := $(sort $(patsubst %/ ,% ,$(dir $(wildcard $(lens_driver_sub_dir)/*/))))
$(foreach c, $(sub_lens), \
    $(eval my_ccu_lens := $(strip $(notdir $(patsubst %/,%,$(c))))) \
    $(eval MY_CCU_DRVNAME_$(call UpperCase,$(my_ccu_lens))=libccu_$(my_ccu_lens)_sub) \
)
$(eval my_lens_path := $(lens_driver_sub_dir))
$(foreach c,$(sub_lens),\
    $(eval my_ccu_lens := $(notdir $(patsubst %/,%,$(c))))\
    $(if $(BUILD_SYSTEM),$(eval include $(CLEAR_VARS)))\
    $(eval include $(CCU_TOOL_LENS_DIR)/ccu_extract.mk)\
    $(if $(BUILD_SYSTEM),$(eval include $(my_ccu_binary_mk)))\
)

main3_lens := $(sort $(patsubst %/ ,% ,$(dir $(wildcard $(lens_driver_main3_dir)/*/))))
$(foreach c, $(main3_lens), \
    $(eval my_ccu_lens := $(strip $(notdir $(patsubst %/,%,$(c))))) \
    $(eval MY_CCU_DRVNAME_$(call UpperCase,$(my_ccu_lens))=libccu_$(my_ccu_lens)_main3) \
)
$(eval my_lens_path := $(lens_driver_main3_dir))
$(foreach c,$(main3_lens),\
    $(eval my_ccu_lens := $(notdir $(patsubst %/,%,$(c))))\
    $(if $(BUILD_SYSTEM),$(eval include $(CLEAR_VARS)))\
    $(eval include $(CCU_TOOL_LENS_DIR)/ccu_extract.mk)\
    $(if $(BUILD_SYSTEM),$(eval include $(my_ccu_binary_mk)))\
)


sub2_lens := $(sort $(patsubst %/ ,% ,$(dir $(wildcard $(lens_driver_sub2_dir)/*/))))
$(foreach c, $(sub2_lens), \
    $(eval my_ccu_lens := $(strip $(notdir $(patsubst %/,%,$(c))))) \
    $(eval MY_CCU_DRVNAME_$(call UpperCase,$(my_ccu_lens))=libccu_$(my_ccu_lens)_sub2) \
)
$(eval my_lens_path := $(lens_driver_sub2_dir))
$(foreach c,$(sub2_lens),\
    $(eval my_ccu_lens := $(notdir $(patsubst %/,%,$(c))))\
    $(if $(BUILD_SYSTEM),$(eval include $(CLEAR_VARS)))\
    $(eval include $(CCU_TOOL_LENS_DIR)/ccu_extract.mk)\
    $(if $(BUILD_SYSTEM),$(eval include $(my_ccu_binary_mk)))\
)

else
$(info $(my_ccu_kernel_path)/drivers/misc/mediatek/lens is not exist)
endif
