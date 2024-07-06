#pragma once

#include <stdint.h>

struct Bus;

uint8_t ReadBus(struct Bus* bus, uint16_t address);
void WriteBus(struct Bus* bus, uint16_t address, uint8_t data);
