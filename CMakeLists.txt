cmake_minimum_required(VERSION 3.16.3)
project(TestOS C)

# This file is just for CLion to detect the compiler and compiler options to provide more code insight.
# Do not use CMake build configurations on CLion. Use Makefile configurations instead to be able to compile on Linux
# normally as well.

# If the standard is changed here, change too on Cppcheck. Note: on 2022-09-27, there is no C17 support.
set(CMAKE_C_FLAGS "-std=c17 -m32 -masm=intel -g3 \
	-funsigned-char \
	-ffreestanding -nostdlib \
	-funroll-loops -O3 \
	-fstack-protector-all \
	-Werror -Wpedantic -pedantic-errors -Wall -Wextra -Wformat=2 -Wformat-overflow=2 \
	-Wformat-signedness -Wnull-dereference -Winit-self -Wparentheses -Wshift-overflow=2 -Wswitch-default -Wswitch-enum \
	-Wunused-const-variable=1 -Walloc-zero -Wattribute-alias=2 -Wduplicated-branches -Wduplicated-cond -Wtrampolines \
	-Wfloat-equal -Wcast-qual -Wcast-align -Wwrite-strings -Wlogical-op -Waggressive-loop-optimizations \
	-Wredundant-decls -Winline -Wstack-protector \
")

add_executable(TestOS kernel.c gdt.c gdt.h CLibs/stdio.c CLibs/stdio.h idt.c idt.h interruptHandlers.c BinaryStructs.h c_runtime.c KernelUtils.c KernelUtils.h Utils/MemReadWrite.c Utils/MemReadWrite.h Utils/LowIo.c Utils/LowIo.h)
