#include <kernel/system.h>

void fault_handler(registers_t* regs)
{
	panic("fault_Handler\n", regs);
}
