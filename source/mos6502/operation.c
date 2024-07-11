#include "mos6502/operation.h"

#include "mos6502/cpu.h"
#include "mos6502/cpuio.h"
#include "mos6502/u16.h"

void ADC(struct CPU* cpu)
{
	const uint8_t input = Read(cpu);
	const uint16_t value = (uint16_t)cpu->accumulator + (uint16_t)input + cpu->status.carry;

	cpu->status.negative = (value & 0x80) == 0x80;
	cpu->status.overflow = (value ^ cpu->accumulator) & (value ^ input) & 0x0080;
	cpu->status.zero = value == 0x00;
	cpu->status.carry = (value & 0x0100) == 0x0100;

	cpu->accumulator = value & 0x00FF;
}

void BEQ(struct CPU* cpu)
{
	if (cpu->status.zero == 1)
	{
		++cpu->internal.cycles;
		if (*HI(&cpu->programCounter) != *HI(&cpu->internal.address))
		{
			++cpu->internal.cycles;
		}

		cpu->programCounter = cpu->internal.address;
	}
}

void BNE(struct CPU* cpu)
{
	if (cpu->status.zero == 0)
	{
		++cpu->internal.cycles;
		if (*HI(&cpu->programCounter) != *HI(&cpu->internal.address))
		{
			++cpu->internal.cycles;
		}

		cpu->programCounter = cpu->internal.address;
	}
}

void BPL(struct CPU* cpu)
{
	if (cpu->status.negative == 0)
	{
		++cpu->internal.cycles;
		if (*HI(&cpu->programCounter) != *HI(&cpu->internal.address))
		{
			++cpu->internal.cycles;
		}

		cpu->programCounter = cpu->internal.address;
	}
}

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

void CMP(struct CPU* cpu)
{
	const uint8_t input = Read(cpu);
	const uint16_t value = (uint16_t)cpu->accumulator - (uint16_t)input;

	cpu->status.negative = (value & 0x80) == 0x80;
	cpu->status.zero = value == 0x00;
	cpu->status.carry = cpu->accumulator >= input;
}

void DEX(struct CPU* cpu)
{
	--cpu->xIndex;

	cpu->status.negative = (cpu->xIndex & 0x80) == 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void DEY(struct CPU* cpu)
{
	--cpu->yIndex;

	cpu->status.negative = (cpu->yIndex & 0x80) == 0x80;
	cpu->status.zero = cpu->yIndex == 0x00;
}

void EOR(struct CPU* cpu)
{
	cpu->accumulator ^= Read(cpu);

	cpu->status.negative = (cpu->accumulator & 0x80) == 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void INX(struct CPU* cpu)
{
	++cpu->xIndex;

	cpu->status.negative = (cpu->xIndex & 0x80) == 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void INY(struct CPU* cpu)
{
	++cpu->yIndex;

	cpu->status.negative = (cpu->yIndex & 0x80) == 0x80;
	cpu->status.zero = cpu->yIndex == 0x00;
}

void JMP(struct CPU* cpu)
{
	cpu->programCounter = cpu->internal.address;
}

void LDA(struct CPU* cpu)
{
	cpu->accumulator = Read(cpu);

	cpu->status.negative = (cpu->accumulator & 0x80) == 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void LDX(struct CPU* cpu)
{
	cpu->xIndex = Read(cpu);

	cpu->status.negative = (cpu->xIndex & 0x80) == 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void LDY(struct CPU* cpu)
{
	cpu->yIndex = Read(cpu);

	cpu->status.negative = (cpu->yIndex & 0x80) == 0x80;
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

	cpu->status.negative = (cpu->accumulator & 0x80) == 0x80;
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

void STA(struct CPU* cpu)
{
	Write(cpu, cpu->accumulator);
}

void STX(struct CPU* cpu)
{
	Write(cpu, cpu->xIndex);
}

void STY(struct CPU* cpu)
{
	Write(cpu, cpu->yIndex);
}

void TAX(struct CPU* cpu)
{
	cpu->xIndex = cpu->accumulator;

	cpu->status.negative = (cpu->accumulator & 0x80) == 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void TAY(struct CPU* cpu)
{
	cpu->yIndex = cpu->accumulator;

	cpu->status.negative = (cpu->accumulator & 0x80) == 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void TSX(struct CPU* cpu)
{
	cpu->xIndex = cpu->stackPointer;

	cpu->status.negative = (cpu->xIndex & 0x80) == 0x80;
	cpu->status.zero = cpu->xIndex == 0x00;
}

void TXA(struct CPU* cpu)
{
	cpu->accumulator = cpu->xIndex;

	cpu->status.negative = (cpu->accumulator & 0x80) == 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}

void TXS(struct CPU* cpu)
{
	cpu->stackPointer = cpu->xIndex;
}

void TYA(struct CPU* cpu)
{
	cpu->accumulator = cpu->yIndex;

	cpu->status.negative = (cpu->accumulator & 0x80) == 0x80;
	cpu->status.zero = cpu->accumulator == 0x00;
}
