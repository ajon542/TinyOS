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


void fault_handler(registers_t* regs)
{
	DebugPrint("fault_handler: %x\n", regs->int_no);
}