#include "main/memory.h"

#include <mos6502/bus.h>
#include <mos6502/cpu.h>
#include <mos6502/interrupt.h>

#include <stdint.h>
#include <stdlib.h>

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
