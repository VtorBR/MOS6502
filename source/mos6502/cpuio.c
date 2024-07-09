#include "mos6502/cpuio.h"

#include "mos6502/busio.h"
#include "mos6502/cpu.h"

uint8_t Read(struct CPU* cpu)
{
	return Fetch(cpu->bus, cpu->internal.address);
}

void Write(struct CPU* cpu, uint8_t data)
{
	Store(cpu->bus, cpu->internal.address, data);
}

uint8_t Pop(struct CPU* cpu)
{
	++cpu->stackPointer;
	return Fetch(cpu->bus, 0x0100 | cpu->stackPointer);
}

void Push(struct CPU* cpu, uint8_t data)
{
	Store(cpu->bus, 0x0100 | cpu->stackPointer, data);
	--cpu->stackPointer;
}
