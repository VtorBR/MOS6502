#include "mos6502/busio.h"

#include "mos6502/bus.h"

uint8_t Fetch(struct Bus* bus, uint16_t address)
{
	return bus->Read(bus->memory, address);
}

void Store(struct Bus* bus, uint16_t address, uint8_t data)
{
	bus->Write(bus->memory, address, data);
}
