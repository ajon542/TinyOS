#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <kernel/tty.h>

void kernel_test(uint32_t eax, uint32_t ebx)
{
    printf("eax: %x\n", eax);
    printf("ebx: %x\n", ebx);
}

void kernel_early(void)
{
	terminal_initialize();
}

void kernel_main(void)
{
	printf("Hello, kernel World - Tiny OS!\n");
}
