#include "mos6502/interrupt.h"

#include "mos6502/cpu.h"
#include "mos6502/cpuio.h"
#include "mos6502/instructionset.h"
#include "mos6502/u16.h"

#include <assert.h>

#define FETCH 0x00
#define EXECUTE 0xE0

void Clock(struct CPU* cpu)
{
	switch (cpu->internal.cycles)
	{
	case FETCH:
		cpu->internal.address = cpu->programCounter;
		++cpu->programCounter;
		cpu->internal.opcode = Read(cpu);
		cpu->internal.cycles = EXECUTE;
		cpu->internal.cycles += instructionSet[cpu->internal.opcode].cycles;
		cpu->internal.cycles -= 2;
		break;
	default:
		assert(cpu->internal.cycles != EXECUTE - 2); // Illegal opcode
		--cpu->internal.cycles;
		break;
	case EXECUTE:
		cpu->internal.cycles = FETCH;

		instructionSet[cpu->internal.opcode].Address(cpu);
		instructionSet[cpu->internal.opcode].Operate(cpu);
		break;
	}
}

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

void IRQ(struct CPU* cpu)
{
	if (cpu->status.irqDisable)
	{
		return;
	}

	cpu->status.brkCommand = 0;

	Push(cpu, *HI(&cpu->programCounter));
	Push(cpu, *LO(&cpu->programCounter));
	Push(cpu, cpu->status.flags);

	cpu->status.irqDisable = 1;

	cpu->internal.address = 0xFFFE;
	*LO(&cpu->programCounter) = Read(cpu);
	++cpu->internal.address;
	*HI(&cpu->programCounter) = Read(cpu);

	cpu->internal.cycles = 7;
}

void NMI(struct CPU* cpu)
{
	Push(cpu, *HI(&cpu->programCounter));
	Push(cpu, *LO(&cpu->programCounter));

	cpu->status.brkCommand = 0;

	Push(cpu, cpu->status.flags);

	cpu->status.irqDisable = 1;

	cpu->internal.address = 0xFFFA;
	*LO(&cpu->programCounter) = Read(cpu);
	++cpu->internal.address;
	*HI(&cpu->programCounter) = Read(cpu);

	cpu->internal.cycles = 7;
}
