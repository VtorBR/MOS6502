#include "mos6502/operation.h"

#include "mos6502/cpu.h"
#include "mos6502/cpuio.h"
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

void CLC(struct CPU* cpu)
{
	cpu->status.carry = 0;
}

void CLD(struct CPU* cpu)
{
	cpu->status.decimalMode = 0;
}

void CLI(struct CPU* cpu)
{
	cpu->status.irqDisable = 0;
}

void CLV(struct CPU* cpu)
{
	cpu->status.overflow = 0;
}

void DEX(struct CPU* cpu)
{
	--cpu->xIndex;

	cpu->status.negative = cpu->xIndex & 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void DEY(struct CPU* cpu)
{
	--cpu->yIndex;

	cpu->status.negative = cpu->yIndex & 0x80;
	cpu->status.zero = cpu->yIndex == 0x00;
}

void INX(struct CPU* cpu)
{
	++cpu->xIndex;

	cpu->status.negative = cpu->xIndex & 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void INY(struct CPU* cpu)
{
	++cpu->yIndex;

	cpu->status.negative = cpu->yIndex & 0x80;
	cpu->status.zero = cpu->yIndex == 0x00;
}

void JMP(struct CPU* cpu)
{
	cpu->programCounter = cpu->internal.address;
}

void LDA(struct CPU* cpu)
{
	cpu->accumulator = Read(cpu);

	cpu->status.negative = cpu->accumulator & 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void LDX(struct CPU* cpu)
{
	cpu->xIndex = Read(cpu);

	cpu->status.negative = cpu->xIndex & 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void LDY(struct CPU* cpu)
{
	cpu->yIndex = Read(cpu);

	cpu->status.negative = cpu->yIndex & 0x80;
	cpu->status.zero = cpu->yIndex == 0x00;
}

void NOP(struct CPU* cpu)
{

}

void PHA(struct CPU* cpu)
{
	Push(cpu, cpu->accumulator);
}

void PHP(struct CPU* cpu)
{
	Push(cpu, cpu->status.flags);
}

void PLA(struct CPU* cpu)
{
	cpu->accumulator = Pop(cpu);

	cpu->status.negative = cpu->accumulator & 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void PLP(struct CPU* cpu)
{
	cpu->status.flags = Pop(cpu);
}

void RTI(struct CPU* cpu)
{
	cpu->status.flags = Pop(cpu);
	*LO(&cpu->programCounter) = Pop(cpu);
	*HI(&cpu->programCounter) = Pop(cpu);
}

void RTS(struct CPU* cpu)
{
	*LO(&cpu->programCounter) = Pop(cpu);
	*HI(&cpu->programCounter) = Pop(cpu);
}

void SEC(struct CPU* cpu)
{
	cpu->status.carry = 1;
}

void SED(struct CPU* cpu)
{
	cpu->status.decimalMode = 1;
}

void SEI(struct CPU* cpu)
{
	cpu->status.irqDisable = 1;
}

void TAX(struct CPU* cpu)
{
	cpu->xIndex = cpu->accumulator;

	cpu->status.negative = cpu->accumulator & 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void TAY(struct CPU* cpu)
{
	cpu->yIndex = cpu->accumulator;

	cpu->status.negative = cpu->accumulator & 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void TSX(struct CPU* cpu)
{
	cpu->xIndex = cpu->stackPointer;

	cpu->status.negative = cpu->xIndex & 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void TXA(struct CPU* cpu)
{
	cpu->accumulator = cpu->xIndex;

	cpu->status.negative = cpu->accumulator & 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void TXS(struct CPU* cpu)
{
	cpu->stackPointer = cpu->xIndex;

	cpu->status.negative = cpu->xIndex & 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void TYA(struct CPU* cpu)
{
	cpu->accumulator = cpu->yIndex;

	cpu->status.negative = cpu->accumulator & 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}
