#pragma once

#include <stdint.h>

extern const char* instructionMnemonics[256];

void Disassemble(uint8_t* program, char* buffer);
