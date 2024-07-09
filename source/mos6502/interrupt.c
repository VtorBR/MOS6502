#include "mos6502/interrupt.h"

#include "mos6502/cpu.h"
#include "mos6502/cpuio.h"
#include "mos6502/u16.h"

void Reset(struct CPU* cpu)
{
	cpu->accumulator = 0xAA;
	cpu->xIndex = 0x00;
	cpu->yIndex = 0x00;
	cpu->stackPointer = 0xFD;
	cpu->status.flags = 0b0010110;

	cpu->internal.address = 0xFFFC;
	*LO(&cpu->programCounter) = Read(cpu);
	++cpu->internal.address;
	*HI(&cpu->programCounter) = Read(cpu);

	cpu->internal.cycles = 8;
}
