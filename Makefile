FLAGS_STD := -masm=intel -std=c11 -g
FLAGS_OPTIM := -O3 -funroll-loops
FLAGS_WARN_ERR := -Wall -Wextra -Werror=pedantic -Werror=format=2 -pedantic-errors
FLAGS_OS := -m32 -nostdlib -fno-builtin -fno-leading-underscore

GCCPARAMS := $(FLAGS_STD) $(FLAGS_OPTIM) $(FLAGS_WARN_ERR) $(FLAGS_OS)
ASPARAMS := --32
LDPARAMS := -m elf_i386

objects = loader.o kernel.o gdt.o port.o CFuncs/stdio.o

%.o: %.c
	gcc $(GCCPARAMS) -o $@ -c $^

%.o: %.s
	gcc $(GCCPARAMS) -o $@ -c $^
	#as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

#install: mykernel.bin
#	sudo cp $< /boot/mykernel.bin

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
	rm $(objects) mykernel.bin mykernel.iso
