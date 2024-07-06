#include "main/memory.h"

#include <mos6502/bus.h>
#include <mos6502/cpu.h>

#include <stdint.h>
#include <stdlib.h>

void Reset(struct CPU*);

int main(int argc, char** argv)
{
	struct Memory memory =
	{
		.ram = malloc(64 * 1024),
		.readCount = 0,
		.writeCount = 0,
	};

	struct Bus bus =
	{
		.Read = ReadMemory,
		.Write = WriteMemory,
		.memory = &memory
	};

	struct CPU cpu =
	{
		.bus = &bus
	};

	Reset(&cpu);

	cpu.bus->Write(cpu.bus->memory, cpu.internal.address, cpu.accumulator);

	free(memory.ram);

	return 0;
}

void Reset(struct CPU* cpu)
{
	const uint16_t address = 0xFFFC;

	const uint16_t lo = cpu->bus->Read(cpu->bus->memory, address + 0);
	const uint16_t hi = cpu->bus->Read(cpu->bus->memory, address + 1);

	cpu->programCounter = (hi << 8) | lo;

	cpu->accumulator = 0;
	cpu->xIndex = 0;
	cpu->yIndex = 0;
	cpu->stackPointer = 0xFD;
	*(uint8_t*)&cpu->status = 0b00100000;

	cpu->internal.address = 0x0000;

	cpu->internal.cycles = 8;
}
