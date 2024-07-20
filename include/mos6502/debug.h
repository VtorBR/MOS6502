#pragma once

#include <stdint.h>

extern const char* instructionMnemonics[256];

uint8_t Disassemble(const uint8_t* program, char buffer[13]);
