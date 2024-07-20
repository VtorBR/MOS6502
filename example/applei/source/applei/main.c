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

	FILE* log = freopen("6502.log", "w", stderr);
	assert(log);

	Reset(&cpu);

	while (1)
	{
		const struct CPU old = cpu;

		Clock(&cpu);
		
		if (old.internal.cycles == 0)
		{
			char buffer[13];
			Disassemble(&wozmon[old.programCounter % sizeof(wozmon)], buffer);
			fprintf(log, "%04X\t%-12s\n", old.programCounter, buffer);
		}
	}

	fclose(log);
	DestroyAppleI(cpu.bus);

	return 0;
}
