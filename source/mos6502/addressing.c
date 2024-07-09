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

void IMP(struct CPU* cpu)
{

}
