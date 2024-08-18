#include "applei/applei.h"
#include "applei/wozmon.h"

#include <mos6502/cpu.h>
#include <mos6502/debug.h>
#include <mos6502/interrupt.h>

#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	struct CPU cpu =
	{
		.bus = CreateAppleI(),
	};

	FILE* log = fopen("6502.log", "w");
	assert(log);

	Reset(&cpu);

	while (1)
	{
		Clock(&cpu);
		
		if (cpu.internal.cycles == 0)
		{
			char assembly[13];
			Disassemble(&wozmon[cpu.programCounter % sizeof(wozmon)], assembly);
			fprintf(log, "%04X\t%-12s\n", cpu.programCounter, assembly);
		}
	}

	fclose(log);
	DestroyAppleI(cpu.bus);

	return 0;
}
