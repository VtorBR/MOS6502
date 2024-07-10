#include "main/memory.h"

#include <mos6502/bus.h>
#include <mos6502/cpu.h>
#include <mos6502/interrupt.h>
#include <mos6502/debug.h>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	struct Memory* memory = malloc(sizeof(struct Memory));
	assert(memory);

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

	FILE* source = NULL;
	if (argc > 1)
	{
		source = fopen(argv[1], "rb");
	}

	if (source)
	{
		const size_t readSize = fread(memory->raw, 1, 64 * 1024, source);

		cpu.programCounter = 0x0400;
		cpu.internal.cycles = 1;

		fclose(source);
		source = NULL;
	}
	else
	{
		memory->mapped.resetVector = 0x0200;
		memory->mapped.irqVector = 0x0204;

		memory->mapped.ram[0] = 0x00; // BRK
		memory->mapped.ram[1] = 0x4C; // JMP
		memory->mapped.ram[2] = 0x00; // Address lo
		memory->mapped.ram[3] = 0x02; // Address hi
		memory->mapped.ram[4] = 0x40; // RTI

		Reset(&cpu);
	}

	unsigned int cycle = 0;
	unsigned int instructionCount = 0;
	const char colors[] = { '\xB0', '\xB2', '\xB1' };
	while (cycle < 256)
	{
		if (cpu.internal.cycles == 1)
		{
			++instructionCount;
			char buffer[12];
			Disassemble(memory->raw + cpu.programCounter, buffer);
			printf("% 4u %c\t%04X : %-11s", cycle, colors[instructionCount % 2], cpu.programCounter, buffer);
		}

		const uint8_t oldCycles = cpu.internal.cycles;
		Clock(&cpu);

		if (oldCycles < cpu.internal.cycles)
		{
			printf("%-5c S: 0x%02X\tP: 0x%02X\tA: 0x%02X\tX: 0x%02X\tY: 0x%02X %c\n",
				colors[instructionCount % 2],
				cpu.stackPointer,
				cpu.status.flags,
				cpu.accumulator,
				cpu.xIndex,
				cpu.yIndex,
				colors[instructionCount % 2]);
		}

		++cycle;
	}

	free(memory);

	return cycle;
}
