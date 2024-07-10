#include "mos6502/instructionset.h"

#include "mos6502/addressing.h"
#include "mos6502/operation.h"

struct Instruction const instructionSet[256] =
{
	[0x00] = {BRK, IMP, 7},
	[0x08] = {PHP, IMP, 3},
	[0x18] = {CLC, IMP, 2},
	[0x28] = {PLP, IMP, 4},
	[0x38] = {SEC, IMP, 2},
	[0x40] = {RTI, IMP, 6},
	[0x48] = {PHA, IMP, 3},
	[0x4C] = {JMP, ABS, 3},
	[0x58] = {CLI, IMP, 2},
	[0x60] = {RTS, IMP, 6},
	[0x68] = {PLA, IMP, 4},
	[0x78] = {SEI, IMP, 2},
	[0x88] = {DEY, IMP, 2},
	[0x8A] = {TXA, IMP, 2},
	[0x8D] = {STA, ABS, 4},
	[0x98] = {TYA, IMP, 2},
	[0x9A] = {TXS, IMP, 2},
	[0xA0] = {LDY, IMM, 2},
	[0xA2] = {LDX, IMM, 2},
	[0xA8] = {TAY, IMP, 2},
	[0xA9] = {LDA, IMM, 2},
	[0xAA] = {TAX, IMP, 2},
	[0xAD] = {LDA, ABS, 4},
	[0xB8] = {CLV, IMP, 2},
	[0xBA] = {TSX, IMP, 2},
	[0xC8] = {INY, IMP, 2},
	[0xC9] = {CMP, IMM, 2},
	[0xCA] = {DEX, IMP, 2},
	[0xD0] = {BNE, REL, 2},
	[0xD8] = {CLD, IMP, 2},
	[0xE8] = {INX, IMP, 2},
	[0xEA] = {NOP, IMP, 2},
	[0xF0] = {BEQ, REL, 2},
	[0xF8] = {SED, IMP, 2},
};
