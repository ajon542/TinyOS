#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/system.h>

unsigned short inports(unsigned short port)
{
	unsigned short rv;
	asm volatile ("inw %1, %0" : "=a" (rv) : "dN" (port));
	return rv;
}

void outports(unsigned short port, unsigned short data)
{
	asm volatile ("outw %1, %0" : : "dN" (port), "a" (data));
}

unsigned int inportl(unsigned short port)
{
	unsigned int rv;
	asm volatile ("inl %%dx, %%eax" : "=a" (rv) : "dN" (port));
	return rv;
}

void outportl(unsigned short port, unsigned int data)
{
	asm volatile ("outl %%eax, %%dx" : : "dN" (port), "a" (data));
}

unsigned char inportb(unsigned short port)
{
	unsigned char rv;
	asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (port));
	return rv;
}

void outportb(unsigned short port, unsigned char data)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

void outportsm(unsigned short port, unsigned char* data, unsigned long size)
{
	asm volatile ("rep outsw" : "+S" (data), "+c" (size) : "d" (port));
}

void inportsm(unsigned short port, unsigned char* data, unsigned long size)
{
	asm volatile ("rep insw" : "+D" (data), "+c" (size) : "d" (port) : "memory");
}