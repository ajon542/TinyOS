#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/system.h>

void fault_handler(registers_t* regs)
{
	panic("fault_Handler\n", regs);
}
