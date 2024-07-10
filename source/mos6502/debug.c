#include "mos6502/debug.h"

#include <stdio.h>

void DisassembleABS(uint8_t* program, char* buffer);
void DisassembleABX(uint8_t* program, char* buffer);
void DisassembleABY(uint8_t* program, char* buffer);
void DisassembleACC(uint8_t* program, char* buffer);
void DisassembleIDR(uint8_t* program, char* buffer);
void DisassembleIDX(uint8_t* program, char* buffer);
void DisassembleIDY(uint8_t* program, char* buffer);
void DisassembleIMM(uint8_t* program, char* buffer);
void DisassembleIMP(uint8_t* program, char* buffer);
void DisassembleREL(uint8_t* program, char* buffer);
void DisassembleZPG(uint8_t* program, char* buffer);
void DisassembleZPX(uint8_t* program, char* buffer);
void DisassembleZPY(uint8_t* program, char* buffer);

void(*disassemblers[256])(uint8_t*, char*) =
{
	[0x00] = DisassembleIMP,
	[0x08] = DisassembleIMP,
	[0x10] = DisassembleREL,
	[0x18] = DisassembleIMP,
	[0x28] = DisassembleIMP,
	[0x38] = DisassembleIMP,
	[0x40] = DisassembleIMP,
	[0x48] = DisassembleIMP,
	[0x4C] = DisassembleABS,
	[0x58] = DisassembleIMP,
	[0x60] = DisassembleIMP,
	[0x68] = DisassembleIMP,
	[0x78] = DisassembleIMP,
	[0x88] = DisassembleIMP,
	[0x8A] = DisassembleIMP,
	[0x8D] = DisassembleABS,
	[0x98] = DisassembleIMP,
	[0x9A] = DisassembleIMP,
	[0xA0] = DisassembleIMM,
	[0xA2] = DisassembleIMM,
	[0xA8] = DisassembleIMP,
	[0xA9] = DisassembleIMM,
	[0xAA] = DisassembleIMP,
	[0xAD] = DisassembleABS,
	[0xB8] = DisassembleIMP,
	[0xBA] = DisassembleIMP,
	[0xC8] = DisassembleIMP,
	[0xC9] = DisassembleIMM,
	[0xCA] = DisassembleIMP,
	[0xD0] = DisassembleREL,
	[0xD8] = DisassembleIMP,
	[0xE8] = DisassembleIMP,
	[0xEA] = DisassembleIMP,
	[0xF0] = DisassembleREL,
	[0xF8] = DisassembleIMP,
};

void Disassemble(uint8_t* program, char* buffer)
{
	if (disassemblers[*program])
	{
		disassemblers[*program](program, buffer);
	}
	else
	{
		sprintf(buffer, "%#02X ? %02X", *program, program[1]);
	}
}

const char* instructionMnemonics[256] =
{
	[0x00] = "BRK",
	[0x08] = "PHP",
	[0x10] = "BPL",
	[0x18] = "CLC",
	[0x28] = "PLP",
	[0x38] = "SEC",
	[0x40] = "RTI",
	[0x48] = "PHA",
	[0x4C] = "JMP",
	[0x58] = "CLI",
	[0x60] = "RTS",
	[0x68] = "PLA",
	[0x78] = "SEI",
	[0x88] = "DEY",
	[0x8A] = "TXA",
	[0x8D] = "STA",
	[0x98] = "TYA",
	[0x9A] = "TXS",
	[0xA0] = "LDY",
	[0xA2] = "LDX",
	[0xA8] = "TAY",
	[0xA9] = "LDA",
	[0xAA] = "TAX",
	[0xAD] = "LDA",
	[0xB8] = "CLV",
	[0xBA] = "TSX",
	[0xC8] = "INY",
	[0xC9] = "CMP",
	[0xCA] = "DEX",
	[0xD0] = "BNE",
	[0xD8] = "CLD",
	[0xE8] = "INX",
	[0xEA] = "NOP",
	[0xF0] = "BEQ",
	[0xF8] = "SED",
};

void DisassembleABS(uint8_t* program, char* buffer)
{
	sprintf(buffer, "%s $%02X%02X", instructionMnemonics[program[0]], program[1], program[2]);
}

void DisassembleIMM(uint8_t* program, char* buffer)
{
	sprintf(buffer, "%s #$%02X", instructionMnemonics[program[0]], program[1]);
}

void DisassembleIMP(uint8_t* program, char* buffer)
{
	sprintf(buffer, "%s", instructionMnemonics[program[0]]);
}

void DisassembleREL(uint8_t* program, char* buffer)
{
	sprintf(buffer, "%s $%02X", instructionMnemonics[program[0]], program[1]);
}
