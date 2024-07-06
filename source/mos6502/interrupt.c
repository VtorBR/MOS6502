#include "mos6502/interrupt.h"

#include "mos6502/cpu.h"
#include "mos6502/cpuio.h"

void Reset(struct CPU* cpu)
{
	cpu->internal.address = 0xFFFC;

	cpu->programCounter = ReadAddress(cpu);
	cpu->accumulator = 0;
	cpu->xIndex = 0;
	cpu->yIndex = 0;
	cpu->stackPointer = 0xFF;
	*(uint8_t*)&cpu->status = 0b00100000;

	cpu->internal.address = 0x0000;
	cpu->internal.cycles = 8;
}
