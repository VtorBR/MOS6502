#pragma once

#include <stdint.h>

struct CPU;

struct Instruction
{
	void(*Operate)(struct CPU*);
	void(*Address)(struct CPU*);
	uint8_t cycles;
} extern const instructionSet[256];
