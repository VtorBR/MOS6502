#pragma once

struct CPU;

void Clock(struct CPU* cpu);
void Reset(struct CPU* cpu);
void IRQ(struct CPU* cpu);
void NMI(struct CPU* cpu);
