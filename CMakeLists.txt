cmake_minimum_required(VERSION 3.16.3)
project(TestOS C)

# Se se mudar aqui o standard, mudar também no Cppcheck.
set(CMAKE_C_FLAGS "-masm=intel -std=c11 -O3 -funroll-loops -Wall -Wextra -Werror=format=2 -Werror=pedantic -pedantic-errors -funroll-loops -Wno-main -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore")

add_executable(TestOS kernel.c gdt.c gdt.h CFuncs/stdio.c CFuncs/stdio.h port.c port.h)
