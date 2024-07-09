#pragma once

#include <stdint.h>

struct Bus;

uint8_t Fetch(struct Bus* bus, uint16_t address);
void Store(struct Bus* bus, uint16_t address, uint8_t data);
