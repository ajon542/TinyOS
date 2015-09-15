#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "../include/kernel/system.h"


void fault_handler(registers_t* regs)
{
	//DebugPrint("fault_handler: %x\n", regs->int_no);
	panic("fault_Handler\n", regs);
}