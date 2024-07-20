#include "applei/applei.h"
#include "applei/wozmon.h"

#include <mos6502/bus.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t ReadMemory(void* memory, uint16_t address);
void WriteMemory(void* memory, uint16_t address, uint8_t data);

struct AppleI
{
	union
	{
		struct
		{
			uint8_t zeropage[0x100];
			uint8_t stack[0x100];
			uint8_t in[0x80];
		};
		uint8_t ram[0x8000];
	};
	const uint8_t* rom;
};

struct Bus* CreateAppleI()
{
	struct AppleI* apple = malloc(sizeof(struct AppleI));
	assert(apple);

	apple->rom = wozmon;

	struct Bus* bus = malloc(sizeof(struct Bus));
	assert(bus);

	bus->Read = ReadMemory;
	bus->Write = WriteMemory;
	bus->memory = apple;

	return bus;
}

void DestroyAppleI(struct Bus* bus)
{
	free(bus->memory);
	free(bus);
}

#define KBD 0xD010
#define KBDCR 0xD011
#define DSP 0xD012
#define DSPCR 0xD013

uint8_t ReadMemory(void* memory, uint16_t address)
{
	switch (address)
	{
	case KBD:
	{
		char character = getchar();
		if (character == '\n')
		{
			character = '\r';
		}

		return character | 0x80;
	}
	case KBDCR:
		return 0x80;
	case DSP:
		return 0x00;
	case DSPCR:
		return 0x00;
	default:
		if (address >> 15)
		{
			return ((struct AppleI*)memory)->rom[address % 0x100];
		}
		else
		{
			return ((struct AppleI*)memory)->ram[address % 0x8000];
		}
	}
}

void WriteMemory(void* memory, uint16_t address, uint8_t data)
{
	switch (address)
	{
	case KBD:
		break;
	case KBDCR:
		break;
	case DSP:
		if (data == 0x8D)
		{
			putchar('\n');
		}
		else if (data & 0x80)
		{
			putchar(data & 0x7F);
		}
		break;
	case DSPCR:
		break;
	default:
		((uint8_t*)memory)[address] = data;
		break;
	}
}
