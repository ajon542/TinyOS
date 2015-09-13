#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <kernel/tty.h>

// TODO: This needs to be fixed, just not sure where to put it.
#include <../arch/i386/include/multiboot.h>

// Check if the bit BIT in FLAGS is set.
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

extern void gdt_install(void);

void kernel_early(uint32_t magic, uint32_t addr)
{
	// Intialize basic terminal functionality.
	terminal_initialize();

	DebugPrint("Terminal initialized\n");

	multiboot_info_t* mbi;

	// Am I booted by a Multiboot-compliant boot loader?
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		DebugPrint("Invalid magic number: 0x%x\n", (unsigned)magic);
		return;
	}

	// Set MBI to the address of the Multiboot information structure.
	mbi = (multiboot_info_t *)addr;

	// Print out the flags.
	DebugPrint("flags = 0x%x\n", (unsigned)mbi->flags);

	// Are mem_* valid?
	if (CHECK_FLAG(mbi->flags, 0))
	{
		DebugPrint("mem_lower = %d KB, mem_upper = %d KB\n",
			(unsigned)mbi->mem_lower, (unsigned)mbi->mem_upper);
	}

	// Is boot_device valid?
	if (CHECK_FLAG(mbi->flags, 1))
	{
		DebugPrint("boot_device = 0x%x\n", (unsigned)mbi->boot_device);
	}

	// Is the command line passed?
	if (CHECK_FLAG(mbi->flags, 2))
	{
		DebugPrint("cmdline = %s\n", (char *)mbi->cmdline);
	}

	// Are mods_* valid?
	if (CHECK_FLAG(mbi->flags, 3))
	{
		multiboot_module_t *mod;
		int i;

		DebugPrint("mods_count = 0x%x, mods_addr = 0x%x\n", (int)mbi->mods_count, (int)mbi->mods_addr);

		for (i = 0, mod = (multiboot_module_t *)mbi->mods_addr; i < (int)mbi->mods_count; i++, mod++)
		{
			DebugPrint(" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
				(unsigned)mod->mod_start,
				(unsigned)mod->mod_end,
				(char *)mod->cmdline);
		}
	}

	// Bits 4 and 5 are mutually exclusive!
	if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5))
	{
		DebugPrint("Both bits 4 and 5 are set.\n");
		return;
	}

	// Is the symbol table of a.out valid?
	if (CHECK_FLAG(mbi->flags, 4))
	{
		multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);

		DebugPrint("multiboot_aout_symbol_table: tabsize = 0x%0x, strsize = 0x%x, addr = 0x%x\n",
			(unsigned)multiboot_aout_sym->tabsize,
			(unsigned)multiboot_aout_sym->strsize,
			(unsigned)multiboot_aout_sym->addr);
	}

	// Is the section header table of ELF valid?
	if (CHECK_FLAG(mbi->flags, 5))
	{
		multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);

		DebugPrint("multiboot_elf_sec: num = %u, size = 0x%x, addr = 0x%x, shndx = 0x%x\n",
			(unsigned)multiboot_elf_sec->num, (unsigned)multiboot_elf_sec->size,
			(unsigned)multiboot_elf_sec->addr, (unsigned)multiboot_elf_sec->shndx);
	}

	// Are mmap_* valid?
	if (CHECK_FLAG(mbi->flags, 6))
	{
		multiboot_memory_map_t *mmap;

		DebugPrint("mmap_addr = 0x%x, mmap_length = 0x%x\n",
			(unsigned)mbi->mmap_addr, (unsigned)mbi->mmap_length);

		for (mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
			(unsigned long)mmap < mbi->mmap_addr + mbi->mmap_length;
			mmap = (multiboot_memory_map_t *)((unsigned long)mmap + mmap->size + sizeof(mmap->size)))
			DebugPrint(" size = 0x%x, base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
			(unsigned)mmap->size,
			(unsigned)(mmap->addr >> 32),
			(unsigned)(mmap->addr & 0xffffffff),
			(unsigned)(mmap->len >> 32),
			(unsigned)(mmap->len & 0xffffffff),
			(unsigned)mmap->type);
	}

	DebugPrint("Installing GDT...\n");
	gdt_install();
}

// prototype for asm function
int* asm_mod_array(int *ptr, int size);
void set_gdt();

void kernel_main(void)
{
	DebugPrint("Hello, kernel World - Tiny OS!\n");
	int fren[5] = { 1, 2, 3, 4, 5 };
	int i = 0;
	asm_mod_array(fren, 5);
	DebugPrint("Called asm_mod_arr\n");
	for (i = 0; i < 5; ++i)
	{
		DebugPrint("%d\n", fren[i]);
	}
}
