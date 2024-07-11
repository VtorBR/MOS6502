#include "mos6502/debug.h"

#include "mos6502/instructionset.h"
#include "mos6502/addressing.h"

#include <stdio.h>

void Disassemble(uint8_t* program, char buffer[13])
{
	struct Disassembler
	{
		void(*addressing)(struct CPU*);
		const char* format;
		unsigned int bytes;
	} static const disassemblers[] =
	{
		{ABS, "%s $%02X%02X", 3},
		{ABX, "%s $%02X%02X,X", 3},
		{ABY, "%s $%02X%02X,Y", 3},
		{ACC, "%s A", 1},
		{IDR, "%s ($%02X%02X)", 3},
		{IDX, "%s ($%02X,X)", 2},
		{IDY, "%s ($%02X),Y", 2},
		{IMM, "%s #$%02X", 2},
		{IMP, "%s", 1},
		{REL, "%s $%02X", 2},
		{ZPG, "%s $%02X", 2},
		{ZPX, "%s $%02X,X", 2},
		{ZPY, "%s $%02X,Y", 2},
	};

	for (size_t index = 0; index < sizeof(disassemblers) / sizeof(disassemblers[0]); ++index)
	{
		if (instructionSet[*program].Address == disassemblers[index].addressing)
		{
			sprintf(buffer, disassemblers[index].format, instructionMnemonics[*program], program[1], program[2]);
			
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
	[0x41] = "EOR",
	[0x45] = "EOR",
	[0x48] = "PHA",
	[0x49] = "EOR",
	[0x4C] = "JMP",
	[0x4D] = "EOR",
	[0x51] = "EOR",
	[0x55] = "EOR",
	[0x58] = "CLI",
	[0x59] = "EOR",
	[0x5D] = "EOR",
	[0x60] = "RTS",
	[0x68] = "PLA",
	[0x6C] = "JMP",
	[0x78] = "SEI",
	[0x81] = "STA",
	[0x85] = "STA",
	[0x88] = "DEY",
	[0x8A] = "TXA",
	[0x8D] = "STA",
	[0x91] = "STA",
	[0x95] = "STA",
	[0x98] = "TYA",
	[0x99] = "STA",
	[0x9A] = "TXS",
	[0x9D] = "STA",
	[0xA0] = "LDY",
	[0xA1] = "LDA",
	[0xA2] = "LDX",
	[0xA4] = "LDY",
	[0xA5] = "LDA",
	[0xA6] = "LDX",
	[0xA8] = "TAY",
	[0xA9] = "LDA",
	[0xAA] = "TAX",
	[0xAC] = "LDY",
	[0xAD] = "LDA",
	[0xAE] = "LDX",
	[0xB1] = "LDA",
	[0xB4] = "LDY",
	[0xB5] = "LDA",
	[0xB6] = "LDX",
	[0xB8] = "CLV",
	[0xB9] = "LDA",
	[0xBA] = "TSX",
	[0xBC] = "LDY",
	[0xBD] = "LDA",
	[0xBE] = "LDX",
	[0xC1] = "CMP",
	[0xC5] = "CMP",
	[0xC8] = "INY",
	[0xC9] = "CMP",
	[0xCA] = "DEX",
	[0xCD] = "CMP",
	[0xD0] = "BNE",
	[0xD1] = "CMP",
	[0xD5] = "CMP",
	[0xD8] = "CLD",
	[0xD9] = "CMP",
	[0xDD] = "CMP",
	[0xE8] = "INX",
	[0xEA] = "NOP",
	[0xF0] = "BEQ",
	[0xF8] = "SED",
};
