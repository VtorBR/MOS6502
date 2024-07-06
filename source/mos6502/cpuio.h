#pragma once

#include <stdint.h>

struct CPU;
struct Bus;

uint8_t Read(struct CPU* cpu);
void Write(struct CPU* cpu, uint8_t data);

uint8_t Pop(struct CPU* cpu);
void Push(struct CPU* cpu, uint8_t data);

uint16_t ReadAddress(struct CPU* cpu);
