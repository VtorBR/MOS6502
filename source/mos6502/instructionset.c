#include "mos6502/instructionset.h"

#include "mos6502/addressing.h"
#include "mos6502/operation.h"

struct Instruction const instructionSet[256] =
{
	[0x00] = {BRK, IMP, 7},
	[0x40] = {RTI, IMP, 6},
	[0xEA] = {NOP, IMP, 2},
};
