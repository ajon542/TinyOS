#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct registers
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;

} registers_t;


// Implemented in gtc.c
void gdt_install();

// Implemented in idt.c
void idt_install();
typedef void(*idt_gate_t)(void);
void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags);

// Implemented in panic.c
void panic(char* message, registers_t* regs);

// Implemented in irq.c
void irq_install();
void int_disable();
void int_enable();
void int_resume();
void irq_ack(size_t irq_no);

typedef int(*irq_handler_chain_t) (registers_t *);
void irq_install_handler(size_t irq, irq_handler_chain_t handler);

// Implemented in system.c
uint16_t inports(uint16_t port);
void outports(uint16_t port, uint16_t data);
uint32_t inportl(uint16_t port);
void outportl(uint16_t port, uint32_t data);
uint8_t inportb(uint16_t port);
void outportb(uint16_t port, uint8_t data);
void outportsm(uint16_t port, uint8_t* data, uint32_t size);
void inportsm(uint16_t port, uint8_t* data, uint32_t size);

// Implemented in timer.c
void init_timer(uint32_t frequency);

#endif // _SYSTEM_H