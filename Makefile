# This is the Makefile for project
SHELL := /bin/bash

root_dir := $(shell pwd)

uboot_toolchain := arm-2011.03-42-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
kernel_toolchain := arm-2010q1-189-arm-uclinuxeabi-i686-pc-linux-gnu.tar.bz2

toolchain_dir := cross_tools
UBOOT_TOOL_DIR := $(root_dir)/$(toolchain_dir)/arm-2011.03/bin
KERNEL_TOOL_DIR := $(root_dir)/$(toolchain_dir)/arm-2010q1-uclinux/bin
ROOTFS_TOOL_DIR := $(root_dir)/$(toolchain_dir)/arm-2010q1-uclinux/bin

uboot_version := u-boot-2011.06
#uboot_version := u-boot-2010.03

filesystem_dir := filesystem
busybox_version := busybox-1.17.0
busybox_dir := $(root_dir)/$(filesystem_dir)/$(busybox_version)
rootfs_dir := $(root_dir)/$(filesystem_dir)/rootfs

$(shell export $(busybox_dir)) 

target_out := $(root_dir)/out
kernel_target := uImage
rootfs_target := 

.PHONY: all prepare uboot rootfs kernel 
all: prepare uboot rootfs kernel 

prepare:

UBOOT_CROSS_NAME := arm-none-eabi
UBOOT_CROSS_COMPILE := $(UBOOT_TOOL_DIR)/$(UBOOT_CROSS_NAME)-
UBOOT_CC := $(UBOOT_CROSS_COMPILE)gcc
# Check for the correct version of cross tool for uboot
cross_tool_arch := $(shell $(UBOOT_CC) -v 2>&1 | head -n 10 | grep -n '^Target:*[^ ].*' | grep -n '$(UBOOT_CROSS_NAME)')

ifeq ($(uboot_version),u-boot-2010.03) 
uboot_config := mic_lpc1788_s_config
uboot_target := u-boot-lpc.hex
else 
uboot_target := u-boot-lpc.hex
uboot_config := ea1788_config
endif 

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

ROOTFS_CROSS_NAME := arm-uclinuxeabi
ROOTFS_CROSS_COMPILE := $(ROOTFS_TOOL_DIR)/$(ROOTFS_CROSS_NAME)-
ROOTFS_CC := $(ROOTFS_CROSS_COMPILE)gcc
ROOTFS_CFLAGS := "-march=armv7-m -mthumb -Wl,-elf2flt=-s -Wl,-elf2flt=16384"
# Check for the correct version of cross tool for rootfs
rootfs_tool_arch := $(shell $(ROOTFS_CC) -v 2>&1 | head -n 10 | grep -n '^Target:*[^ ].*' | grep -n '$(ROOTFS_CROSS_NAME)')

# Increase the temporary output directory
$(shell mkdir -p $(target_out))

ifeq ($(strip $(cross_tool_arch)),)
$(info **********************************)
$(info decompression the cross_tool:$(shell mkdir -p $(toolchain_dir))) 
$(info $(shell tar -jxf source/$(kernel_toolchain) -C $(toolchain_dir)))
$(shell mv $(toolchain_dir)/arm-2010q1 $(toolchain_dir)/arm-2010q1-uclinux)
$(info **********************************)
endif

# Check whether the file system is compiled
filesystem_path := $(shell ls $(busybox_dir))
ifeq ($(strip $(filesystem_path)),)
$(info **********************************)
$(info $(shell tar -jxf source/${busybox_version}.tar.bz2 -C $(filesystem_dir)))
$(info **********************************)
endif

uboot:
	@echo $(uboot_version) $(uboot_config)
	make -C $(root_dir)/uboot/$(uboot_version)/ ARCH=arm CROSS_COMPILE=$(UBOOT_CROSS_COMPILE) $(uboot_config) distclean
	make -C $(root_dir)/uboot/$(uboot_version)/ ARCH=arm CROSS_COMPILE=$(UBOOT_CROSS_COMPILE) $(uboot_config)
	make -C $(root_dir)/uboot/$(uboot_version)/ ARCH=arm CROSS_COMPILE=$(UBOOT_CROSS_COMPILE) 
	cp -af $(root_dir)/uboot/$(uboot_version)/$(uboot_target) $(target_out)

uboot_clean:
	make -C $(root_dir)/uboot/$(uboot_version)/ ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) distclean
	rm -rf $(target_out)/$(uboot_target)

rootfs:
	make -C $(busybox_dir) ARCH=arm CROSS_COMPILE=$(ROOTFS_CROSS_COMPILE) CFLAGS=$(ROOTFS_CFLAGS) distclean
	cp $(busybox_dir)/uclinux_config $(busybox_dir)/.config
	#cp $(busybox_dir)/uclinux_config_bak $(busybox_dir)/.config
	make -C $(busybox_dir) ARCH=arm CROSS_COMPILE=$(ROOTFS_CROSS_COMPILE) CFLAGS=$(ROOTFS_CFLAGS) SKIP_STRIP=y
	make -C $(busybox_dir) ARCH=arm CROSS_COMPILE=$(ROOTFS_CROSS_COMPILE) CFLAGS=$(ROOTFS_CFLAGS) install

rootfs_clean:
	make -C $(busybox_dir) ARCH=arm CROSS_COMPILE=arm-uclinuxeabi- CFLAGS=$(ROOTFS_CFLAGS) distclean

kernel:
	cp -af $(filesystem_dir)/rootfs/initramfs-list-min $(root_dir)/kernel/linux-2.6.33/
	sed -i "s:busybox_dir:${busybox_dir}:" $(root_dir)/kernel/linux-2.6.33/initramfs-list-min
	sudo cp $(root_dir)/uboot/$(uboot_version)/tools/mkimage /bin/
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) distclean	
	#make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) ea-lpc1788_defconfig
	#make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) ea-lpc1788_initramfs_defconfig
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) mic-lpc1788_defconfig
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) uImage
	sudo rm -rf /bin/mkimage
	cp -af $(root_dir)/kernel/linux-2.6.33/arch/arm/boot/$(kernel_target) $(target_out)

kernel_clean:
	make -C $(root_dir)/kernel/linux-2.6.33/ CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) distclean	
	rm -rf $(target_out)/$(kernel_target)

.PHONY += clean
clean: uboot_clean kernel_clean rootfs_clean
	rm -rf $(target_out)
		
.PHONY += help
help:
	@echo -e "\033[31m----------------------------------------\033[0m" 
	@echo "    You can use the following command    "
	@echo "compile the uboot:"
	@echo -e "\033[31m    make uboot; make uboot_clean;\033[0m" 
	@echo "compile the kernel:"
	@echo -e "\033[31m    make kernel; make kernel_clean;\033[0m" 
	@echo "compile the rootfs:"
	@echo -e "\033[31m    make rootfs; make rootfs_clean;\033[0m" 
	@echo "clean the target:"
	@echo -e "\033[31m    make clean;\033[0m" 
	@echo -e "\033[31m----------------------------------------\033[0m" 
