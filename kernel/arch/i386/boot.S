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

// TODO: Example of a assembly function and it is called from kernel_main() in kernel.c
.section .text
.globl asm_mod_array
.type asm_mod_array, @function
asm_mod_array:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp),%eax          # get pointer to start of array passed from C
    movl 12(%ebp),%ecx         # get size of array
    xorl %edi, %edi            # zero out our array index
     
    start_loop:                # start loop
    cmpl %edi, %ecx            # check to see if we’ve hit the end
    je loop_exit
    movl (%eax,%edi,4), %edx   # store the element in %edx for calculations
    leal 5(,%edx,2), %edx      # multiply array element by 2 and add 5
    movl %edx, (%eax,%edi,4)   # overwrite old element with new value
    incl %edi                  # increment the index, moving through the array.
    jmp start_loop             # jump to loop beginning
     
    loop_exit:                 # function epilogue
    movl %ebp, %esp
    popl %ebp
    ret                        # pop the return address and jmp to it

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

    pushl %ebx
    pushl %eax
    
    call kernel_test
    
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
