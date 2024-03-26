#include "cr_registers.h"

uint64_t READ_cr0() {
    uint64_t ret;
    __asm__ __volatile__("mov %%cr0, %0" : "=r"(ret));
    return ret;
}

uint64_t READ_cr2() {
    uint64_t ret;
    __asm__ __volatile__("mov %%cr2, %0" : "=r"(ret));
    return ret;
}

uint64_t READ_cr3() {
    uint64_t ret;
    __asm__ __volatile__("mov %%cr3, %0" : "=r"(ret));
    return ret;
}

uint64_t READ_cr4() {
    uint64_t ret;
    __asm__ __volatile__("mov %%cr4, %0" : "=r"(ret));
    return ret;
}

uint64_t READ_cr8() {
    uint64_t ret;
    __asm__ __volatile__("mov %%cr8, %0" : "=r"(ret));
    return ret;
}

void WRITE_cr0(uint64_t value) {
    __asm__ __volatile__("mov %0, %%cr0" :: "r"(value));
}

void WRITE_cr3(uint64_t value) {
    __asm__ __volatile__("mov %0, %%cr3" :: "r"(value));
}

void WRITE_cr4(uint64_t value) {
    __asm__ __volatile__("mov %0, %%cr4" :: "r"(value));
}

void WRITE_cr8(uint64_t value) {
    __asm__ __volatile__("mov %0, %%cr8" :: "r"(value));
}