#ifndef _SYSTEM_H
#define _SYSTEM_H

// TODO: Probably belongs in isr.h
typedef struct registers
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;

} registers_t;

// TODO: Probably belongs in panic.h
void panic(char* message, registers_t* regs);

#endif // _SYSTEM_H