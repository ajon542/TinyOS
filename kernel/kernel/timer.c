#include <kernel/system.h>

#define PIT_A 0x40
#define PIT_B 0x41
#define PIT_C 0x42
#define PIT_CONTROL 0x43

#define PIT_MASK 0xFF
#define PIT_SCALE 1193180
#define PIT_SET 0x36

#define TIMER_IRQ 0

uint32_t tick = 0;
static int timer_callback(registers_t* regs)
{
	tick++;
	DebugPrint("tick: %d\n", tick);
	irq_ack(TIMER_IRQ);
	return 1;
}

void init_timer(uint32_t frequency)
{
	// Firstly, register our timer callback.
	irq_install_handler(TIMER_IRQ, timer_callback);

	// The value we send to the PIT is the value to divide it's input clock
	// (1193180 Hz) by, to get our required frequency. Important to note is
	// that the divisor must be small enough to fit into 16-bits.
	uint32_t divisor = PIT_SCALE / frequency;

	// Send the command byte.
	outportb(PIT_CONTROL, PIT_SET);

	// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	uint8_t l = (uint8_t)(divisor & PIT_MASK);
	uint8_t h = (uint8_t)((divisor >> 8) & PIT_MASK);

	// Send the frequency divisor.
	outportb(PIT_A, l);
	outportb(PIT_A, h);
}