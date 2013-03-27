# This is the Makefile for project
SHELL := /bin/bash

ARCH ?= arm
CROSS_COMPILE := arm-none-eabi-
CC := $(CROSS_COMPILE)gcc

# Check for the correct version of cross tool
cross_tool_arch := $(shell $(CC) -v 2>&1 | head -n 10 | grep -n '^Target:*[^ ].*' | grep -n '$(ARCH)')
cross_tool_version := $(shell $(CC) -v 2>&1 | tail -1 | grep -n '^gcc .*4\.5[\. "$$]')

ifeq ($(strip $(cross_tool_arch)),)
ifeq ($(strip $(cross_tool_version)),)
$(info **********************************)
$(info the cross_tool_version:$(shell $(CC) -v 2>&1 | tail -1))
$(info decompression the cross_tool:$(shell ls ))
$(info **********************************)
endif
endif



.PHONY: help
help:
	@echo "$(cross_tools_arch)"
	@echo "----------------------------------------"
