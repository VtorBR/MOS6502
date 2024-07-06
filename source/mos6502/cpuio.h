#pragma once

#include <stdint.h>

struct CPU;
struct Bus;

inline uint8_t Read(struct CPU* cpu);
inline void Write(struct CPU* cpu, uint8_t data);

inline uint8_t Pop(struct CPU* cpu);
inline void Push(struct CPU* cpu, uint8_t data);

inline uint16_t ReadAddress(struct CPU* cpu);
