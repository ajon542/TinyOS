# Declare constants used for creating a multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

    # ‘EAX’
    # Must contain the magic value ‘0x2BADB002’;
    # the presence of this value indicates to the operating system that it was loaded 
    # by a Multiboot-compliant boot loader (e.g. as opposed to another type of boot 
    # loader that the operating system can also be loaded from). 
    # ‘EBX’
    # Must contain the 32-bit physical address of the Multiboot information structure
    # provided by the boot loader (see Boot information format).     
    
    # Save the register values.
    pushl %ebx
    pushl %eax
    
	# Initialize the core kernel before running the global constructors.   
	call kernel_early
    
    # Restore the register values.
    popl %eax
    popl %ebx
    
	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
.Lhang:
	hlt
	jmp .Lhang
.size _start, . - _start
