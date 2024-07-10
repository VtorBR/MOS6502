#include "mos6502/addressing.h"

#include "mos6502/cpu.h"
#include "mos6502/cpuio.h"
#include "mos6502/u16.h"

void ABS(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t lo = Read(cpu);

	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t hi = Read(cpu);

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;
}

void ABX(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t lo = Read(cpu);

	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t hi = Read(cpu);

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;

	cpu->internal.address += cpu->xIndex;

	if (hi != *HI(&cpu->internal.address))
	{
		++cpu->internal.cycles;
	}
}

void ABY(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t lo = Read(cpu);

	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t hi = Read(cpu);

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;

	cpu->internal.address += cpu->yIndex;

	if (hi != *HI(&cpu->internal.address))
	{
		++cpu->internal.cycles;
	}
}

void ACC(struct CPU* cpu)
{

}

void IDR(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	uint8_t lo = Read(cpu);

	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	uint8_t hi = Read(cpu);

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;

	lo = Read(cpu);
	++*LO(&cpu->internal.address);
	hi = Read(cpu);

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;
}

void IDX(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	uint8_t lo = Read(cpu);
	uint8_t hi = 0x00;

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo + cpu->xIndex;

	lo = Read(cpu);
	++*LO(&cpu->internal.address);
	hi = Read(cpu);

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;
}

void IDY(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	uint8_t lo = Read(cpu);
	uint8_t hi = 0x00;

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;

	lo = Read(cpu);
	++*LO(&cpu->internal.address);
	hi = Read(cpu);

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;
	
	cpu->internal.address += cpu->yIndex;

	if (hi != *HI(&cpu->internal.address))
	{
		++cpu->internal.cycles;
	}
}

void IMM(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
}

void IMP(struct CPU* cpu)
{

}

void REL(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	uint16_t offset;
	
	*LO(&offset) = Read(cpu);

	if (offset & 0x80)
	{
		offset |= 0xFF00;
	}

	cpu->internal.address = cpu->programCounter + offset;
}

void ZPG(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t lo = Read(cpu);
	const uint8_t hi = 0x00;

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo;
}

void ZPX(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t lo = Read(cpu);
	const uint8_t hi = 0x00;

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo + cpu->xIndex;
}

void ZPY(struct CPU* cpu)
{
	cpu->internal.address = cpu->programCounter;
	++cpu->programCounter;
	const uint8_t lo = Read(cpu);
	const uint8_t hi = 0x00;

	*HI(&cpu->internal.address) = hi;
	*LO(&cpu->internal.address) = lo + cpu->yIndex;
}
