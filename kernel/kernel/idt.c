#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Interrupt Descriptor Table.
// http://wiki.osdev.org/Interrupt_Descriptor_Table

typedef struct
{
	uint16_t base_low;
	uint16_t sel;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct
{
	uint16_t limit;
	uintptr_t base;
} __attribute__((packed)) idt_pointer_t;

static struct
{
	idt_entry_t entries[256];
	idt_pointer_t pointer;
} idt __attribute__((used));

#define ENTRY(X) (idt.entries[(X)])

typedef void(*idt_gate_t)(void);

extern void idt_load(uintptr_t);

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags)
{
	ENTRY(num).base_low = ((uintptr_t)base & 0xFFFF);
	ENTRY(num).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	ENTRY(num).sel = sel;
	ENTRY(num).zero = 0;
	ENTRY(num).flags = flags | 0x60;
}

void idt_install(void)
{
	idt_pointer_t* idtp = &idt.pointer;
	idtp->limit = sizeof idt.entries - 1;
	idtp->base = (uintptr_t)&ENTRY(0);
	memset(&ENTRY(0), 0, sizeof idt.entries);

	idt_set_gate(0, (idt_gate_t)_isr0, 0x08, 0x8E);
	idt_set_gate(1, (idt_gate_t)_isr1, 0x08, 0x8E);
	idt_set_gate(2, (idt_gate_t)_isr2, 0x08, 0x8E);
	idt_set_gate(3, (idt_gate_t)_isr3, 0x08, 0x8E);
	idt_set_gate(4, (idt_gate_t)_isr4, 0x08, 0x8E);
	idt_set_gate(5, (idt_gate_t)_isr5, 0x08, 0x8E);
	idt_set_gate(6, (idt_gate_t)_isr6, 0x08, 0x8E);
	idt_set_gate(7, (idt_gate_t)_isr7, 0x08, 0x8E);
	idt_set_gate(8, (idt_gate_t)_isr8, 0x08, 0x8E);
	idt_set_gate(9, (idt_gate_t)_isr9, 0x08, 0x8E);
	idt_set_gate(10, (idt_gate_t)_isr10, 0x08, 0x8E);
	idt_set_gate(11, (idt_gate_t)_isr11, 0x08, 0x8E);
	idt_set_gate(12, (idt_gate_t)_isr12, 0x08, 0x8E);
	idt_set_gate(13, (idt_gate_t)_isr13, 0x08, 0x8E);
	idt_set_gate(14, (idt_gate_t)_isr14, 0x08, 0x8E);
	idt_set_gate(15, (idt_gate_t)_isr15, 0x08, 0x8E);
	idt_set_gate(16, (idt_gate_t)_isr16, 0x08, 0x8E);
	idt_set_gate(17, (idt_gate_t)_isr17, 0x08, 0x8E);
	idt_set_gate(18, (idt_gate_t)_isr18, 0x08, 0x8E);
	idt_set_gate(19, (idt_gate_t)_isr19, 0x08, 0x8E);
	idt_set_gate(20, (idt_gate_t)_isr20, 0x08, 0x8E);
	idt_set_gate(21, (idt_gate_t)_isr21, 0x08, 0x8E);
	idt_set_gate(22, (idt_gate_t)_isr22, 0x08, 0x8E);
	idt_set_gate(23, (idt_gate_t)_isr23, 0x08, 0x8E);
	idt_set_gate(24, (idt_gate_t)_isr24, 0x08, 0x8E);
	idt_set_gate(25, (idt_gate_t)_isr25, 0x08, 0x8E);
	idt_set_gate(26, (idt_gate_t)_isr26, 0x08, 0x8E);
	idt_set_gate(27, (idt_gate_t)_isr27, 0x08, 0x8E);
	idt_set_gate(28, (idt_gate_t)_isr28, 0x08, 0x8E);
	idt_set_gate(29, (idt_gate_t)_isr29, 0x08, 0x8E);
	idt_set_gate(30, (idt_gate_t)_isr30, 0x08, 0x8E);
	idt_set_gate(31, (idt_gate_t)_isr31, 0x08, 0x8E);

	idt_load((uintptr_t)idtp);
}
