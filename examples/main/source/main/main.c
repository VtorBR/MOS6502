#include "main/memory.h"

#include <mos6502/bus.h>
#include <mos6502/cpu.h>
#include <mos6502/debug.h>
#include <mos6502/interrupt.h>

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool IsTrapped(struct CPU*);

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

	while (!IsTrapped(&cpu))
	{
		const struct CPU old = cpu;

		Clock(&cpu);
		++cycle;

		continue;

		const char colors[] = { '\xB0', '\xB2', '\xB1' };
		if (old.internal.cycles == 0)
		{
			++instructionCount;
			char buffer[13];
			Disassemble(memory->raw + old.programCounter, buffer);
			printf("% 5u% 2c\t%04X : %-12s",
				cycle - 1,
				colors[instructionCount % 2],
				old.programCounter,
				buffer);
		}
		else if (cpu.internal.cycles == 0)
		{
			printf("% 3c",
				colors[instructionCount % 2]);

			const char* formats[] =
			{
				[false] = "\t%c: 0x%02X",
				[true] = "\t%c:     ",
			};

			printf(formats[old.stackPointer == cpu.stackPointer],
				'S',
				cpu.stackPointer);

			printf(formats[old.status.flags == cpu.status.flags],
				'P',
				cpu.status.flags);

			printf(formats[old.accumulator == cpu.accumulator],
				'A',
				cpu.accumulator);

			printf(formats[old.xIndex == cpu.xIndex],
				'X',
				cpu.xIndex);

			printf(formats[old.yIndex == cpu.yIndex],
				'Y',
				cpu.yIndex);

			if (old.status.flags != cpu.status.flags)
			{
				printf("\t%-2c%c%c%c%c%c%c%c%c",
					colors[instructionCount % 2],
					cpu.status.negative ? 'N' : 'n',
					cpu.status.overflow ? 'V' : 'v',
					cpu.status.unused ? 'U' : 'u',
					cpu.status.brkCommand ? 'B' : 'b',
					cpu.status.decimalMode ? 'D' : 'd',
					cpu.status.irqDisable ? 'I' : 'i',
					cpu.status.zero ? 'Z' : 'z',
					cpu.status.carry ? 'C' : 'c');
			}
			else
			{
				printf("\t%-2c        ",
					colors[instructionCount % 2]);
			}

			if (old.stackPointer != cpu.stackPointer)
			{
				printf("\tstack:");
				for (uint8_t index = cpu.stackPointer; index < 0xFF; ++index)
				{
					printf(" %02X", memory->mapped.stack[index + 1]);
				}
			}

			putchar('\n');
		}
	}

	printf("Trapped at 0x%04X\n", cpu.programCounter);

	free(memory);

	return cycle;
}

bool IsTrapped(struct CPU* cpu)
{
	static unsigned int count = 0;
	uint8_t const* instruction = ((struct Memory const*)cpu->bus->memory)->raw + cpu->programCounter;
	uint16_t const* address = (uint16_t*)(instruction + 1);
	const uint8_t JMP = 0x4C;

	if (cpu->internal.cycles == 0)
	{
		if (*instruction == JMP && *address == cpu->programCounter)
		{
			++count;
		}
		else if ((instruction[0] & 0x10) == 0x10 && (instruction[0] & 0x0F) == 0x00 && instruction[1] == 0xFE)
		{
			++count;
		}
		else
		{
			count = 0;
		}
	}

	return count > 5;
}
