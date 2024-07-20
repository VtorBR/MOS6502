#include "testbus.h"

#include <mos6502/bus.h>
#include <mos6502/cpu.h>
#include <mos6502/interrupt.h>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int reset_test(int argc, char* argv[])
{
	int result = EXIT_SUCCESS;

	struct CPU cpu =
	{
		.bus = CreateTestBus(),
	};

	((uint8_t*)cpu.bus->memory)[0xFFFC] = 0xEF;
	((uint8_t*)cpu.bus->memory)[0xFFFD] = 0xBE;

	Reset(&cpu);

    if(cpu.programCounter != 0xBEEF)
	{
		result = EXIT_FAILURE;
	}

	free(cpu.bus);

	return result;
}
