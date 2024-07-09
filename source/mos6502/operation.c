#include "mos6502/operation.h"

#include "mos6502/cpu.h"
#include "mos6502/u16.h"

void BRK(struct CPU* cpu)
{
	Push(cpu, *HI(&cpu->programCounter));
	Push(cpu, *LO(&cpu->programCounter));
	Push(cpu, cpu->status.flags);

	cpu->internal.address = 0xFFFE;
	*LO(&cpu->programCounter) = Read(cpu);
	++cpu->internal.address;
	*HI(&cpu->programCounter) = Read(cpu);
}

void NOP(struct CPU* cpu)
{

}

void RTI(struct CPU* cpu)
{
	cpu->status.flags = Pop(cpu);
	*HI(&cpu->programCounter) = Pop(cpu);
	*LO(&cpu->programCounter) = Pop(cpu);
}
