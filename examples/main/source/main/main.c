#include "main/memory.h"

#include <mos6502/bus.h>
#include <mos6502/cpu.h>
#include <mos6502/interrupt.h>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void Print(struct CPU const* cpu);

int main(int argc, char** argv)
{
	struct Memory* memory = malloc(sizeof(struct Memory));
	assert(memory);

	memory->mapped.resetVector = 0x0200;
	memory->mapped.irqVector = 0x020F;

	for (uint16_t i = memory->mapped.resetVector; i < memory->mapped.irqVector; ++i)
	{
		memory->raw[i] = 0x00; // BRK
	}
	memory->raw[memory->mapped.irqVector] = 0x40; // RTI

	struct Bus bus =
	{
		.Read = ReadMemory,
		.Write = WriteMemory,
		.memory = memory
	};

	struct CPU cpu =
	{
		.bus = &bus
	};

	Reset(&cpu);

	unsigned int cycle = 0;
	while (cpu.internal.opcode == 0x00 || cpu.internal.opcode == 0x40)
	{
		printf("\nCycle: %u\n", cycle++);
		Print(&cpu);

		Clock(&cpu);

		Print(&cpu);
	}

	free(memory);

	return cycle;
}

void Print(struct CPU const* cpu)
{
	printf("\tIR: 0x%02X PC: 0x%04X S:0x%02X P:0x%02X\n", cpu->internal.opcode, cpu->programCounter, cpu->stackPointer, cpu->status.flags);
}
