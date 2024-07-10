#include "mos6502/debug.h"

#include "mos6502/instructionset.h"
#include "mos6502/addressing.h"

#include <stdio.h>

void Disassemble(uint8_t* program, char buffer[13])
{
	struct DisassembleFormat
	{
		void(*addressing)(struct CPU*);
		const char* format;
	} static const formats[] =
	{
		{ABS, "%s $%02X%02X"},
		{ABX, "%s $%02X%02X,X"},
		{ABY, "%s $%02X%02X,Y"},
		{ACC, "%s A",},
		{IDR, "%s ($%02X%02X)"},
		{IDX, "%s ($%02X,X)"},
		{IDY, "%s ($%02X),Y"},
		{IMM, "%s #$%02X"},
		{IMP, "%s"},
		{REL, "%s $%02X"},
		{ZPG, "%s $%02X"},
		{ZPX, "%s $%02X,X"},
		{ZPY, "%s $%02X,Y"},
	};

	for (size_t index = 0; index < sizeof(formats) / sizeof(formats[0]); ++index)
	{
		if (instructionSet[*program].Address == formats[index].addressing)
		{
			sprintf(buffer, formats[index].format, instructionMnemonics[*program], program[1], program[2]);
			
			return;
		}
	}

	sprintf(buffer, "%#02X ? %02X", *program, program[1]);
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
	[0x6C] = "JMP",
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
