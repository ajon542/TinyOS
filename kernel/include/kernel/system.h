#ifndef _SYSTEM_H
#define _SYSTEM_H

typedef struct registers
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;

} registers_t;

// Implemented in idt.c
typedef void(*idt_gate_t)(void);
void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags);

// Implemented in panic.c
void panic(char* message, registers_t* regs);

// Implemented in irq.c
void int_disable();
void int_enable();
void int_resume();

// Implemented in system.c
unsigned short inports(unsigned short port);
void outports(unsigned short port, unsigned short data);
unsigned int inportl(unsigned short port);
void outportl(unsigned short port, unsigned int data);
unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);
void outportsm(unsigned short port, unsigned char* data, unsigned long size);
void inportsm(unsigned short port, unsigned char* data, unsigned long size);

#endif // _SYSTEM_H