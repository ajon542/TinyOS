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

typedef int(*irq_handler_chain_t) (registers_t *);
typedef void(*idt_gate_t)(void);

// TODO: Probably belongs in panic.h
void panic(char* message, registers_t* regs);

void int_disable();
void int_enable();
void int_resume();

unsigned short inports(unsigned short port);
void outports(unsigned short port, unsigned short data);
unsigned int inportl(unsigned short port);
void outportl(unsigned short port, unsigned int data);
unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);
void outportsm(unsigned short port, unsigned char* data, unsigned long size);
void inportsm(unsigned short port, unsigned char* data, unsigned long size);

#endif // _SYSTEM_H