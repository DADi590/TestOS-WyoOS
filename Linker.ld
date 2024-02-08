/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(_start)

OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

/*
Notes:
- ALIGN and BLOCK both are for backwards compatibility with older linkers. I think ALIGN is the newer, and BLOCK the
older one. Keep them both.
- *(.thing) means all '.thing' section from all files
- The kernel is still being compiled as an ELF - don't change the structure of the file. Else it might become an invalid
  ELF or something (not sure, just thought on this).
*/

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS {
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 0x00100000;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(0x1000) : ALIGN(0x1000) { /* Align at 4 KiB*/
		*(.multiboot)
		*(.text*)
	}

	/* Read-only data. */
	.rodata BLOCK(0x1000) : ALIGN(0x1000) { /* Align at 4 KiB*/
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(0x1000) : ALIGN(0x1000) { /* Align at 4 KiB*/
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(0x1000) : ALIGN(0x1000) { /* Align at 4 KiB*/
		*(COMMON)
		*(.bss)
	}

	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}
