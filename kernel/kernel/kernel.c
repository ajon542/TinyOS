#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/system.h>

void kernel_early(uint32_t magic, uint32_t addr)
{
	// Intialize basic terminal functionality.
	terminal_initialize();

	// Print the multiboot information.
	print_multiboot_info(magic, addr);

	DebugPrint("Installing GDT...\n");
	gdt_install();
	DebugPrint("Installing IDT...\n");
	idt_install();
	DebugPrint("Installing IRQ...\n");
	irq_install();
}

void kernel_main(void)
{
	DebugPrint("Hello, kernel World - Tiny OS!\n");

	//init_timer(50);

	while (1) {}
}
