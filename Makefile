# This is the Makefile for project
SHELL := /bin/bash

ARCH ?= arm

root_dir := $(shell pwd)

uboot_toolchain := arm-2011.03-42-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
kernel_toolchain := arm-2010q1-189-arm-uclinuxeabi-i686-pc-linux-gnu.tar.bz2

toolchain_dir := cross_tools
UBOOT_TOOL_DIR := $(root_dir)/$(toolchain_dir)/arm-2011.03/bin
KERNEL_TOOL_DIR := $(root_dir)/$(toolchain_dir)/arm-2010q1-uclinux/bin

.PHONY: all prepare uboot kernel
all: prepare uboot kernel

prepare:

CROSS_NAME := arm-none-eabi
CROSS_COMPILE := $(UBOOT_TOOL_DIR)/$(CROSS_NAME)-
CC := $(CROSS_COMPILE)gcc
# Check for the correct version of cross tool for uboot
cross_tool_arch := $(shell $(CC) -v 2>&1 | head -n 10 | grep -n '^Target:*[^ ].*' | grep -n '$(CROSS_NAME)')

ifeq ($(strip $(cross_tool_arch)),)
$(info **********************************)
$(info decompression the cross_tool:)
$(shell mkdir -p $(toolchain_dir)) 
$(shell tar -jxf source/$(uboot_toolchain) -C $(toolchain_dir))  
$(info **********************************)
endif

KERNEL_CROSS_NAME := arm-uclinuxeabi
KERNEL_CROSS_COMPILE := $(KERNEL_TOOL_DIR)/$(KERNEL_CROSS_NAME)-
KERNEL_CC := $(KERNEL_CROSS_COMPILE)gcc
# Check for the correct version of cross tool for kernel
cross_tool_arch := $(shell $(KERNEL_CC) -v 2>&1 | head -n 10 | grep -n '^Target:*[^ ].*' | grep -n '$(KERNEL_CROSS_NAME)')

ifeq ($(strip $(cross_tool_arch)),)
$(info **********************************)
$(info decompression the cross_tool:$(shell mkdir -p $(toolchain_dir))) 
$(info $(shell tar -jxf source/$(kernel_toolchain) -C $(toolchain_dir)))
$(shell mv $(toolchain_dir)/arm-2010q1 $(toolchain_dir)/arm-2010q1-uclinux)
$(info **********************************)
endif

uboot:
	make -C $(root_dir)/uboot/u-boot-2011.06/ ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) distclean
	make -C $(root_dir)/uboot/u-boot-2011.06/ ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) ea1788_config
	make -C $(root_dir)/uboot/u-boot-2011.06/ ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) 

uboot_clean:
	make -C $(root_dir)/uboot/u-boot-2011.06/ ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) distclean

kernel:
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) distclean
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) ea-lpc1788_defconfig
	#make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(CROSS_COMPILE) ea-lpc1788_initramfs_defconfig
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) uImage

kernel_clean:
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) distclean
	
.PHONY += help
help:
	@echo "----------------------------------------"
