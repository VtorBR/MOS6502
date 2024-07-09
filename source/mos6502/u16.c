#include "mos6502/u16.h"

uint8_t* HI(uint16_t* value)
{
	return (uint8_t*)(value) + 1;
}

uint8_t* LO(uint16_t* value)
{
	return (uint8_t*)(value);
}
