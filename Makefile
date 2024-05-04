PROJECT := keyboard_firmware

TARGET ?= MAX32650
TARGET_UC := $(shell echo $(TARGET) | tr '[:lower:]' '[:upper:]')
TARGET_LC := $(shell echo $(TARGET) | tr '[:upper:]' '[:lower:]')
export TARGET
export TARGET_UC
export TARGET_LC

#BOARD ?= keyboard
BOARD := EvKit_V1

ifeq ($(strip $(MAXIM_PATH)),)
$(error MAXIM_PATH not defined.)
endif

LIBS_DIR := $(abspath $(MAXIM_PATH)/Libraries)
CMSIS_ROOT := $(LIBS_DIR)/CMSIS
export CMSIS_ROOT

COMPILER := GCC
ifneq ($(strip $(DEBUG)),)
MXC_OPTIMIZE_CFLAGS += -Og -g
else
MXC_OPTIMIZE_CFLAGS += -O2
endif

MFLOAT_ABI ?= softfp
export MFLOAT_ABI

PROJ_CFLAGS += -Wall
PROJ_CFLAGS += -DMXC_ENABLE
#PROJ_CFLAGS += -DNO_EVAL_FEATURES
PROJ_CFLAGS += -fdiagnostics-color=always

CROSS_COMPILE ?= arm-none-eabi
CC := $(CROSS_COMPILE)-gcc
LD := $(CROSS_COMPILE)-ld
OBJCOPY := $(CROSS_COMPILE)-objcopy
OBJDUMP := $(CROSS_COMPILE)-objdump

VPATH += src
VPATH += src/target/$(TARGET_LC)
VPATH += $(CMSIS_ROOT)/Device/Maxim/$(TARGET_UC)/Source
VPATH := $(VPATH)
SRCS := $(wildcard $(addsuffix /*.c, $(VPATH)))

IPATH += .
IPATH += include

SRC_DIR ?= src
BLD_DIR ?= build

LINKERFILE := src/linker.ld
STARTUPFILE := src/startup.S

LIB_BOARD := 1
include $(LIBS_DIR)/libs.mk
include $(CMSIS_ROOT)/Device/Maxim/$(TARGET_UC)/Source/$(COMPILER)/$(TARGET_LC).mk

ifeq ($(strip $(MAKECMDGOALS)),)
MAKECMDGOALS := all
endif

.PHONY: all clean libclean distclean

all: $(BLD_DIR)/$(PROJECT).bin $(BLD_DIR)/$(PROJECT).dasm
	arm-none-eabi-size --format=berkeley $(BUILD_DIR)/$(PROJECT).elf

clean:
	$(RM) -r $(BLD_DIR)

libclean: 
	$(MAKE) -f $(PERIPH_DRIVER_DIR)/periphdriver.mk clean.periph

distclean: clean libclean

print-%:
	@echo $* = $($*)
