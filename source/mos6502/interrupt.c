#include "mos6502/interrupt.h"

#include "mos6502/cpu.h"
#include "mos6502/cpuio.h"
#include "mos6502/instructionset.h"
#include "mos6502/u16.h"

#include <assert.h>

#define FETCH 0x00
#define DECODE 0xDE
#define EXECUTE 0xE0

void Clock(struct CPU* cpu)
{
	static_assert(EXECUTE - DECODE == 2, "2 is the minimum instruction cycle count.");

	switch (cpu->internal.cycles)
	{
	case FETCH:
		cpu->internal.address = cpu->programCounter;
		++cpu->programCounter;
		cpu->internal.opcode = Read(cpu);
		cpu->internal.cycles = DECODE;
		cpu->internal.cycles += instructionSet[cpu->internal.opcode].cycles;
		break;
	case DECODE: // Illegal opcode
		assert(instructionSet[cpu->internal.opcode].cycles);
	case EXECUTE:
		cpu->internal.cycles = FETCH;
		instructionSet[cpu->internal.opcode].Address(cpu);
		instructionSet[cpu->internal.opcode].Operate(cpu);
		break;
	default:
		--cpu->internal.cycles;
		break;
	}
}

void Reset(struct CPU* cpu)
{
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
