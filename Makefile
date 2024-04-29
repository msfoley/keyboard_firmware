PROJ_NAME := keyboard_firmware

CROSS_COMPILE ?= arm-none-eabi
CC := $(CROSS_COMPILE)-gcc
LD := $(CROSS_COMPILE)-ld
OBJCOPY := $(CROSS_COMPILE)-objcopy

SRC_DIR := src
BLD_DIR := build

PROJ_SRCS := $(shell find $(SRC_DIR) -name "*.[cs]")
PROJ_OBJS := $(addprefix $(BLD_DIR)/,$(patsubst %.c,%.o,$(patsubst %.s,%.o,$(PROJ_SRCS))))

NXP_SDK ?= $(HOME)/projects/nxp_sdk
SDK_DEVICE := MIMXRT1062
SDK_DIR := $(NXP_SDK)
SDK_DEVICE_DIR := $(SDK_DIR)/devices/$(SDK_DEVICE)

SDK_SRCS := $(shell find $(SDK_DEVICE_DIR)/drivers -name "*.c") $(shell find $(SDK_DEVICE_DIR)/utilities -name "*.c")
SDK_OBJS := $(addprefix $(BLD_DIR)/,$(subst $(SDK_DEVICE_DIR),sdk,$(patsubst %.c,%.o,$(SDK_SRCS))))

OBJS := $(SDK_OBJS) $(PROJ_OBJS)

$(BLD_DIR)/src/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(BLD_DIR)/src/%.o: $(SRC_DIR)/%.s
	$(CC) $(CFLAGS) -o $@ $<

$(BLD_DIR)/sdk/%.o: $(SDK_DEVICE_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

%.elf:
	@mkdir -p $(@D)
	$(LD) -T $(LINKER_FILE) --entry $(ENTRY) $(LDFLAGS) -o $@ $^

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.dasm: %.elf
	$(OBJDUMP) -S $< > $@

$(BLD_DIR)/$(PROJ_NAME).elf: $(OBJS)

$(BLD_DIR)/$(PROJ_NAME).bin: $(BLD_DIR)/$(PROJ_NAME).elf

$(BLD_DIR)/$(PROJ_NAME).hex: $(BLD_DIR)/$(PROJ_NAME).elf

$(BLD_DIR)/$(PROJ_NAME).dasm: $(BLD_DIR)/$(PROJ_NAME).elf

all: $(BLD_DIR)/$(PROJ_NAME).bin $(BLD_DIR)/$(PROJ_NAME).hex $(BLD_DIR)/$(PROJ_NAME).dasm

print-%:
	@echo $* = $($*)
