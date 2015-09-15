#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/system.h>

void panic(char* message, registers_t* regs)
{
	// TODO: IRQ_OFF

	DebugPrint("----------- PANIC -----------\n");
	DebugPrint(message);

	if (regs) 
	{
		DebugPrint("Registers at interrupt:\n");
		DebugPrint("eax=0x%x\n", regs->eax);
		DebugPrint("ebx=0x%x\n", regs->ebx);
		DebugPrint("ecx=0x%x\n", regs->ecx);
		DebugPrint("edx=0x%x\n", regs->edx);
		DebugPrint("esp=0x%x\n", regs->esp);
		DebugPrint("ebp=0x%x\n", regs->ebp);
		DebugPrint("Error code: 0x%x\n", regs->err_code);
		DebugPrint("EFLAGS:     0x%x\n", regs->eflags);
		DebugPrint("User ESP:   0x%x\n", regs->useresp);
		DebugPrint("eip=0x%x\n", regs->eip);
	}

	asm volatile ("hlt");
}