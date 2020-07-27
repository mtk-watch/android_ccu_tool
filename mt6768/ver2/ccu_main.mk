ifneq ($(wildcard $(LINUX_KERNEL_VERSION)),)
my_ccu_kernel_path ?= $(LINUX_KERNEL_VERSION)
else
my_ccu_kernel_path ?= kernel
endif

#Priority: project > platform > common
COMMON_VERSION := $(strip $(shell cat $(my_ccu_kernel_path)/drivers/misc/mediatek/imgsensor/src/$(MTK_PLATFORM_DIR)/Makefile | grep ^COMMON_VERSION | sed -e s/^.*:=/''/g))
sensor_driver_src_project  ?= $(my_ccu_kernel_path)/drivers/misc/mediatek/imgsensor/src/$(MTK_PLATFORM_DIR)/camera_project/$(MTK_TARGET_PROJECT)
sensor_driver_src_platform ?= $(my_ccu_kernel_path)/drivers/misc/mediatek/imgsensor/src/$(MTK_PLATFORM_DIR)
sensor_driver_src_common   ?= $(my_ccu_kernel_path)/drivers/misc/mediatek/imgsensor/src/common/$(COMMON_VERSION)
my_ccu_src_path :=

my_ccu_inc_file ?= $(my_ccu_kernel_path)/drivers/misc/mediatek/imgsensor/inc/kd_imgsensor.h

$(foreach m,MTK_TARGET_PROJECT MTK_PLATFORM_DIR,$(if $($(m)),,$(error $(m) is not defined)))
$(foreach m,LOCAL_PATH my_ccu_kernel_path my_ccu_inc_file,$(if $(wildcard $($(m))),,$(error $(m)=$($(m)) does not exist)))

UpperCase = $(subst a,A,$(subst b,B,$(subst c,C,$(subst d,D,$(subst e,E,$(subst f,F,$(subst g,G,$(subst h,H,$(subst i,I,$(subst j,J,$(subst k,K,$(subst l,L,$(subst m,M,$(subst n,N,$(subst o,O,$(subst p,P,$(subst q,Q,$(subst r,R,$(subst s,S,$(subst t,T,$(subst u,U,$(subst v,V,$(subst w,W,$(subst x,X,$(subst y,Y,$(subst z,Z,$(1)))))))))))))))))))))))))))

# max ELF code size in byte for split
my_ccu_pm_max_code ?= 4096
my_ccu_dm_max_code ?= 1536

my_ccu_drvname_map := $(shell cat $(my_ccu_inc_file) | grep '^\s*\#define SENSOR_DRVNAME_' | sed -e 's/^\s*\#define SENSOR_DRVNAME_\(\w\+\)\s\+"\(\w\+\)"/\1=libccu_\2/g')
$(foreach m,$(my_ccu_drvname_map),\
	$(eval MY_CCU_DRVNAME_$(m))\
)

$(foreach c,$(CUSTOM_KERNEL_IMGSENSOR),\
	$(eval my_ccu_sensor := $(c))\
	$(if $(BUILD_SYSTEM),$(eval include $(CLEAR_VARS)))\
	$(eval include $(MTK_PLATFORM_SW_VER_DIR)/ccu_extract.mk)\
	$(if $(BUILD_SYSTEM),$(eval include $(MTK_PLATFORM_SW_VER_DIR)/ccu_binary.mk))\
)
