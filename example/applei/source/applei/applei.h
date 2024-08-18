#pragma once

#include <stdint.h>

struct Bus;

struct Bus* CreateAppleI();
void DestroyAppleI(struct Bus*);
const uint8_t* GetAddress(struct Bus*, uint16_t);
