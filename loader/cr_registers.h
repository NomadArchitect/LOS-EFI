
#ifndef CR_REGISTERS_H
#define CR_REGISTERS_H

uint64_t READ_cr0(void);
uint64_t READ_cr2(void);
uint64_t READ_cr3(void);
uint64_t READ_cr4(void);
uint64_t READ_cr8(void);

void WRITE_cr0(uint64_t value);
void WRITE_cr3(uint64_t value);
void WRITE_cr4(uint64_t value);
void WRITE_cr8(uint64_t value);

#endif  // CR_REGISTERS_H
