#include <mos6502/bus.h>
#include <mos6502/cpu.h>
#include <mos6502/debug.h>
#include <mos6502/interrupt.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t ReadMemory(void* memory, uint16_t address)
{
    return ((uint8_t*)memory)[address];
}

void WriteMemory(void* memory, uint16_t address, uint8_t data)
{
    ((uint8_t*)memory)[address] = data;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s rom_file [max_cycle_count] [starting_address]\n", argv[0]);

        return EXIT_FAILURE;
    }

    uint8_t* memory = malloc(1 << 16);

	FILE* rom = fopen(argv[1], "rb");
	if (rom)
	{
		fread(memory, 1, 1 << 16, rom);
		fclose(rom);
	}
    else
    {
        fprintf(stderr, "Could not open ROM file at %s\n", argv[1]);

        return EXIT_FAILURE;
    }

    struct Bus bus =
	{
		.Read = ReadMemory,
		.Write = WriteMemory,
		.memory = memory,
	};

	struct CPU cpu =
	{
		.bus = &bus
	};

    uint64_t maxCycleCount = 1e8;

    if (argc > 2)
    {
        maxCycleCount = atoi(argv[2]);
    }

    if (argc > 3)
    {
        cpu.programCounter = atoi(argv[3]);
    }
    else
    {
        Reset(&cpu);
    }

	uint64_t cycleCount = 0;
    uint16_t lastInstruction = cpu.programCounter;

	while (cycleCount++ < maxCycleCount)
	{
        Clock(&cpu);

        if (cpu.internal.cycles == 0)
        {
            if (lastInstruction == cpu.programCounter)
            {
                char assembly[13];
			    Disassemble(memory + cpu.programCounter, assembly);
                fprintf(stderr, "Trapped at %04X : %-12s\n", cpu.programCounter, assembly);

                return cpu.programCounter;
            }

            lastInstruction = cpu.programCounter;
        }
	}

	free(memory);
    
    fprintf(stderr, "Exceeded max cycle count: %llu\n", maxCycleCount);

    return EXIT_FAILURE;
}
