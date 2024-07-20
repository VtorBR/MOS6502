#include "testbus.h"

#include <mos6502/bus.h>
#include <mos6502/cpu.h>
#include <mos6502/operation.h>
#include <mos6502/interrupt.h>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int adc_test(int argc, char* argv[])
{
	int result = EXIT_SUCCESS;

	struct CPU cpu =
	{
		.bus = CreateTestBus(),
	};

    cpu.internal.address = 0x0001;
    cpu.programCounter = 0x0000;
    cpu.accumulator = 0x0F;
    cpu.xIndex = 0x00;
    cpu.yIndex = 0x00;
    cpu.stackPointer = 0xFF;
    cpu.status.flags = 0x01;

	((uint8_t*)cpu.bus->memory)[cpu.internal.address] = 0xF0;

	const struct CPU old = cpu;

	ADC(&cpu);

    if(cpu.accumulator != 0x00)
	{
		result = EXIT_FAILURE;
	}

	if (cpu.status.negative != 0)
	{
		result = EXIT_FAILURE;
	}

	if (cpu.status.zero != 1)
	{
		result = EXIT_FAILURE;
	}

	if (cpu.status.overflow != 0)
	{
		result = EXIT_FAILURE;
	}

	if (cpu.status.carry != 1)
	{
		result = EXIT_FAILURE;
	}

	free(cpu.bus);

	return result;
}
