#pragma once

#include <stdint.h>

typedef uint8_t(*BusReadFunction)(void* memory, uint16_t address);
typedef void(*BusWriteFunction)(void* memory, uint16_t address, uint8_t data);

struct Bus
{
	BusReadFunction Read;
	BusWriteFunction Write;

	void* memory;
};
