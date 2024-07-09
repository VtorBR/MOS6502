#pragma once

#include <stdint.h>

uint8_t ReadMemory(void* memory, uint16_t address);
void WriteMemory(void* memory, uint16_t address, uint8_t data);

struct Memory
{
	union
	{
		struct MemoryLayout
		{
			uint8_t zeropage[0x0100];
			uint8_t stack[0x0100];
			uint8_t ram[0xFDFA];
			uint16_t nmiVector;
			uint16_t resetVector;
			uint16_t irqVector;
		} mapped;
		uint8_t raw[sizeof(struct MemoryLayout)];
	};

	struct Stats
	{
		size_t readCount;
		size_t writeCount;
	} stats;
};
