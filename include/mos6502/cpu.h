#pragma once

#include <stdint.h>

struct Bus;

struct CPU
{
	struct Bus* const bus;

	struct State
	{
		uint16_t address;
		uint8_t cycles;
		uint8_t opcode;
	} internal;

	uint16_t programCounter;
	uint8_t accumulator;
	uint8_t xIndex;
	uint8_t yIndex;
	uint8_t stackPointer;

	union
	{
		struct Status
		{
			uint8_t carry : 1;
			uint8_t zero : 1;
			uint8_t irqDisable : 1;
			uint8_t decimalMode : 1;
			uint8_t brkCommand : 1;
			uint8_t unused : 1;
			uint8_t overflow : 1;
			uint8_t negative : 1;
		};
		uint8_t flags;
	} status;
};
