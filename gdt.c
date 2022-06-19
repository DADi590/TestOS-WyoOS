#include "gdt.h"
#include "CFuncs/stdio.h"
#include <stdint-gcc.h>
#include <stdbool.h>

struct SegmentDescriptor {
	uint16_t limit_lo;
	uint16_t base_lo;
	uint8_t base_hi;
	uint8_t access_byte;
	uint8_t flags_limit_hi;
	uint8_t base_vhi;
} __attribute__((packed));

struct GDT {
	struct SegmentDescriptor null_seg_descriptor;
	struct SegmentDescriptor kernel_code_seg;
	struct SegmentDescriptor kernel_data_seg;
	struct SegmentDescriptor task_state_seg;
} __attribute__((packed));

struct GDTEntry {
	uint32_t base;
	uint32_t limit;
	uint8_t access_byte;
	uint8_t flags;
} __attribute__((aligned(16)));

void encodeGdtEntry(struct SegmentDescriptor *target, struct GDTEntry source);
void encodeGdtEntryBase(struct SegmentDescriptor *target, uint32_t base);
void encodeGdtEntryLimit(struct SegmentDescriptor *target, uint32_t limit);
void encodeGdtEntryAccessByte(struct SegmentDescriptor *target, uint8_t access_byte);
void encodeGdtEntryFlags(struct SegmentDescriptor *target, uint8_t flags);


struct GDT gdt = {0};
bool gdt_ready = false;

void prepareGDT(void) {
	if (gdt_ready) {
		printS("GDT already prepared. Aborting...\n");

		return;
	}

	struct GDTEntry gdt_entry = {0};
	gdt_entry.base = 0;
	gdt_entry.limit = (64*1024*1024)/4096; // 64 MiB, but in 4 KiB chunks as required by the Granularity.
	gdt_entry.access_byte = 0x9A;
	gdt_entry.flags = 0xC;
	encodeGdtEntry(&gdt.kernel_code_seg, gdt_entry);
	gdt_entry.access_byte = 0x92;
	encodeGdtEntry(&gdt.kernel_data_seg, gdt_entry);

	// Must be 6 bytes, and I'm starting at position 0 of the 1st byte (easier with inline-asm...).
	uint32_t gdt_info[2];
	gdt_info[0] = sizeof(gdt) - 1;
	gdt_info[0] |= ((uint32_t) &gdt) << (uint8_t) (2*8);
	gdt_info[1] = ((uint32_t) &gdt) >> (uint8_t) (2*8);

	//printNu(sizeof(gdt)-1);
	//printC(' ');
	//printNu((uint32_t) &gdt);
	//printC(' ');
	//printNu(gdt_info[0]);
	//printC(' ');
	//printNu(gdt_info[1]);
	//printC(' ');

	__asm__ volatile (
			"lgdt    [%0]" : : "g" (gdt_info)
			);

	printS("GDT ready\n");

	gdt_ready = true;
}

void encodeGdtEntry(struct SegmentDescriptor *target, struct GDTEntry source) {

	encodeGdtEntryBase(target, source.base);
	encodeGdtEntryLimit(target, source.limit);
	encodeGdtEntryAccessByte(target, source.access_byte);
	encodeGdtEntryFlags(target, source.flags);
}

void encodeGdtEntryBase(struct SegmentDescriptor *target, uint32_t base) {
	// Encode the base
	((uint8_t *) target)[2] = base & (uint8_t) 0xFF;
	((uint8_t *) target)[3] = (base >> (uint8_t) (1*8)) & (uint8_t) 0xFF;
	((uint8_t *) target)[4] = (base >> (uint8_t) (2*8)) & (uint8_t) 0xFF;
	((uint8_t *) target)[7] = (base >> (uint8_t) (3*8)) & (uint8_t) 0xFF;
}

void encodeGdtEntryLimit(struct SegmentDescriptor *target, uint32_t limit) {
	// Check the limit to make sure that it can be encoded
	if (limit > 0xFFFFF) {
		printS("GDT cannot encode limits larger than 0xFFFFF\n");
	}

	// Encode the limit
	((uint8_t *) target)[0] = limit & (uint8_t) 0xFF;
	((uint8_t *) target)[1] = (limit >> (uint8_t) (1*8)) & (uint8_t) 0xFF;
	((uint8_t *) target)[6] |= (limit >> (uint8_t) (2*8));
}

void encodeGdtEntryAccessByte(struct SegmentDescriptor *target, uint8_t access_byte) {
	// Encode the access byte
	((uint8_t *) target)[5] = access_byte;
}

void encodeGdtEntryFlags(struct SegmentDescriptor *target, uint8_t flags) {
	// Encode the flags
	((uint8_t *) target)[6] |= (uint8_t) (flags << (uint8_t) 4);
}
