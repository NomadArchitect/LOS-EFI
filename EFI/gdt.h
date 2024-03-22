
#ifndef GDT_H
#define GDT_H

#include "typedefs.h"

struct GDTEntry
{
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_mid;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} __attribute__((__packed__));

struct GDTRegister
{
    uint16_t    limit;
    uint64_t    base;
} __attribute__((__packed__));

static struct {
    struct GDTEntry entry[5];
} __attribute__((__packed__)) gdt;

static struct GDTRegister GDTReg;

void gdt_init() {
    gdt.entry[0].limit_low = 0;
    gdt.entry[0].base_low = 0;
    gdt.entry[0].base_mid = 0;
    gdt.entry[0].access = 0;
    gdt.entry[0].granularity = 0;
    gdt.entry[0].base_high = 0;

    gdt.entry[1].limit_low = 0;
    gdt.entry[1].base_low = 0;
    gdt.entry[1].base_mid = 0;
    gdt.entry[1].access = 0b10011010;
    gdt.entry[1].granularity = 0b00100000;
    gdt.entry[1].base_high = 0;

    gdt.entry[2].limit_low = 0;
    gdt.entry[2].base_low = 0;
    gdt.entry[2].base_mid = 0;
    gdt.entry[2].access = 0b10010010;
    gdt.entry[2].granularity = 0;
    gdt.entry[2].base_high = 0;

    gdt.entry[3].limit_low = 0;
    gdt.entry[3].base_low = 0;
    gdt.entry[3].base_mid = 0;
    gdt.entry[3].access = 0b11111010;
    gdt.entry[3].granularity = 0b00100000;
    gdt.entry[3].base_high = 0;

    gdt.entry[4].limit_low = 0;
    gdt.entry[4].base_low = 0;
    gdt.entry[4].base_mid = 0;
    gdt.entry[4].access = 0b11110010;
    gdt.entry[4].granularity = 0;
    gdt.entry[4].base_high = 0;

    GDTReg.limit = (uint16_t) sizeof(gdt) - 1;
    GDTReg.base = (uint64_t) &gdt;

    __asm__ __volatile__("lgdt %0" :: "m"(GDTReg) : "memory");
	
	__asm__ __volatile__(
        "push %0\n\t"
        "push $1\n\t"
        "lretq\n\t"
        "1:\n\t"
        "mov %1, %%ds\n\t"
        "mov %1, %%es\n\t"
        "mov %1, %%fs\n\t"
        "mov %1, %%gs\n\t"
        "mov %1, %%ss\n\t"
        :: "rmi"(0x08), "rm"(0x10)
        : "memory"
    );
}

#endif  // GDT_H
