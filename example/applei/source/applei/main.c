#include "applei/applei.h"

#include <mos6502/cpu.h>
#include <mos6502/debug.h>
#include <mos6502/interrupt.h>

#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	FILE* log = fopen("6502.log", "w");
	assert(log);

	struct CPU cpu =
	{
		.bus = CreateAppleI(),
	};

	Reset(&cpu);

	while (cpu.internal.cycles != 0xDE) // Legal opcode
	{
		Clock(&cpu);
		
		if (cpu.internal.cycles == 0) // Instruction fetch
		{
			const uint8_t* program = GetAddress(cpu.bus, cpu.programCounter);
			char assembly[13];
			Disassemble(program, assembly);
			fprintf(log, "%04X\t%-12s\n", cpu.programCounter, assembly);
		}
	}

	DestroyAppleI(cpu.bus);

	fclose(log);

	return 0;
}
