#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/system.h>

#define INDEX_FROM_BIT(b) (b / 0x20)

void kernel_early(uint32_t magic, multiboot_info_t* mbi)
{
	// Intialize basic terminal functionality.
	terminal_initialize();

	// Parse the multiboot information.
	parse_multiboot_info(magic, mbi);


	uint32_t memsize = (uint32_t)mbi->mem_lower + (uint32_t)mbi->mem_upper;
	//uint32_t nframes = memsize / 4;
	//uint32_t frames = INDEX_FROM_BIT(nframes * 8);

	DebugPrint("---------------------------------\n");
	DebugPrint("memsize: %d\n", memsize);
	/*DebugPrint("nframes: %d\n", nframes);
	DebugPrint(" frames: %d\n", frames);
	DebugPrint("memsize: %x\n", memsize);
	DebugPrint("nframes: %x\n", nframes);
	DebugPrint(" frames: %x\n", frames);
	DebugPrint("---------------------------------\n");*/

	//uintptr_t phys;
	//kernel_directory = (page_directory_t *)kvmalloc_p(sizeof(page_directory_t), &phys);
	//memset(kernel_directory, 0, sizeof(page_directory_t));


	DebugPrint("Installing GDT...\n");
	gdt_install();
	DebugPrint("Installing IDT...\n");
	idt_install();
	DebugPrint("Installing IRQ...\n");
	irq_install();
}

extern void* code;
extern void* data;
extern void* bss;
extern void* end;

char* string = "hello";

void kernel_main(void)
{
	DebugPrint("Hello, kernel World - Tiny OS!\n");

	//init_timer(50);
	DebugPrint("code: %x\n", code);
	DebugPrint("data: %x\n", data);
	DebugPrint(" bss: %x\n", bss);
	DebugPrint(" end: %x\n", end);

	while (1) {}
}
