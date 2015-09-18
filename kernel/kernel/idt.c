#include <kernel/system.h>

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

extern void idt_load(uintptr_t);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

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

	idt_set_gate(0, (idt_gate_t)isr0, 0x08, 0x8E);
	idt_set_gate(1, (idt_gate_t)isr1, 0x08, 0x8E);
	idt_set_gate(2, (idt_gate_t)isr2, 0x08, 0x8E);
	idt_set_gate(3, (idt_gate_t)isr3, 0x08, 0x8E);
	idt_set_gate(4, (idt_gate_t)isr4, 0x08, 0x8E);
	idt_set_gate(5, (idt_gate_t)isr5, 0x08, 0x8E);
	idt_set_gate(6, (idt_gate_t)isr6, 0x08, 0x8E);
	idt_set_gate(7, (idt_gate_t)isr7, 0x08, 0x8E);
	idt_set_gate(8, (idt_gate_t)isr8, 0x08, 0x8E);
	idt_set_gate(9, (idt_gate_t)isr9, 0x08, 0x8E);
	idt_set_gate(10, (idt_gate_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (idt_gate_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (idt_gate_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (idt_gate_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (idt_gate_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (idt_gate_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (idt_gate_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (idt_gate_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (idt_gate_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (idt_gate_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (idt_gate_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (idt_gate_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (idt_gate_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (idt_gate_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (idt_gate_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (idt_gate_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (idt_gate_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (idt_gate_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (idt_gate_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (idt_gate_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (idt_gate_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (idt_gate_t)isr31, 0x08, 0x8E);

	idt_load((uintptr_t)idtp);
}
