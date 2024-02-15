# There is no C17 support on Cppcheck yet (27-09-2022), so must be C11 here too.
FLAGS_STD := -masm=intel -std=c17 -g3
# Don't remove the optimizations: https://wiki.osdev.org/C#Things_you_should_know_about_optimizations
FLAGS_OPTIM := #-funroll-loops -O3
# Unsigned char because I may (and do, currently) use a char in bitwise operations, so I'm making them all unsigned.
FLAGS_DIALECT := #-funsigned-char
# -Warith-conversion is not working so far (26-09-2022, updated GCC, WSL)
FLAGS_WARN_COMP_ERR := -Werror -Wpedantic -pedantic-errors -Wall -Wextra -Wformat=2 -Wformat-overflow=2 \
	-Wformat-signedness -Wnull-dereference -Winit-self -Wparentheses -Wshift-overflow=2 -Wswitch-default -Wswitch-enum \
	-Wunused-const-variable=1 -Walloc-zero -Wattribute-alias=2 -Wduplicated-branches -Wduplicated-cond -Wtrampolines \
	-Wfloat-equal -Wcast-qual -Wcast-align -Wwrite-strings -Wlogical-op -Waggressive-loop-optimizations \
	-Wredundant-decls -Winline -Wstack-protector
FLAGS_WARN_LINK_ERR := -Wl,--fatal-warnings,--warn-common
FLAGS_PROG_INSTRUM := -fstack-protector-all
FLAGS_OS := -m32 -ffreestanding -nostdlib

GCCPARAMS := $(FLAGS_STD) $(FLAGS_OPTIM) $(FLAGS_DIALECT) $(FLAGS_WARN_COMP_ERR) $(FLAGS_WARN_LINK_ERR) \
	$(FLAGS_PROG_INSTRUM) $(FLAGS_OS)
ASPARAMS := --32
WARN_LINK_ERR := --fatal-warnings --warn-common
LDPARAMS := -m elf_i386 $(WARN_LINK_ERR) -z noexecstack

objects = \
	CLibs/stdio.o \
	Utils/KernelUtils.o Utils/LowIo.o Utils/MemReadWrite.o \
	Gdt/Gdt.o \
	Interrupts/Idt.o Interrupts/InterruptHandlers.o Interrupts/InterruptStubs.o Interrupts/Pic.o \
		Interrupts/Keyboard/Keyboard.o \
	C_runtime.o Kernel.o Loader.o

%.o: %.c
	gcc $(GCCPARAMS) -o $@ -c $^

%.o: %.asm
	# Change of plans: now it's NASM - Intel syntax... No idea how to change it on GCC - masm=intel is only for code
	# generation, I think, not for assembling --> so NASM.
	nasm -g -f elf $<
	#gcc $(GCCPARAMS) -o $@ -c $^
	#as $(ASPARAMS) -o $@ $<

mykernel.bin: Linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

#install: mykernel.bin
#	sudo cp $< /boot/mykernel.bin

# NOTE: if the file doesn't have at least 9 MB, means it won't work.
# The 9 MB come from copying stuff from /usr/lib/grub/i386-pc/ to the iso/boot/grub/ folder. Make sure that folder
# exists. On WSL it didn't, so I went on a VM of Debian 12 and copied the files from there and it worked.
mykernel.iso: mykernel.bin
	rm -rf iso
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot

	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg

	grub-mkrescue --output=$@ iso

.PHONY: clean
clean:
	rm -f $(objects) mykernel.bin mykernel.iso
