#pragma once

#include <stdint.h>

uint8_t ReadMemory(void* memory, uint16_t address);
void WriteMemory(void* memory, uint16_t address, uint8_t data);

struct Memory
{
	uint8_t* const ram;
	size_t readCount;
	size_t writeCount;
};
