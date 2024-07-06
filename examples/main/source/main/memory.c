#include "main/memory.h"

#include <mos6502/bus.h>

inline uint8_t MyReadMemory(struct Memory* memory, uint16_t address)
{
	++memory->readCount;
	return memory->ram[address];
}

inline void MyWriteMemory(struct Memory* memory, uint16_t address, uint8_t data)
{
	++memory->writeCount;
	memory->ram[address] = data;
}

uint8_t ReadMemory(void* memory, uint16_t address)
{
	return MyReadMemory(memory, address);
}

void WriteMemory(void* memory, uint16_t address, uint8_t data)
{
	MyWriteMemory(memory, address, data);
}
