#include "testbus.h"

#include <mos6502/bus.h>

#include <stdlib.h>

uint8_t ReadMemory(void* memory, uint16_t address)
{
    return ((uint8_t*)memory)[address];
}

void WriteMemory(void* memory, uint16_t address, uint8_t data)
{
    ((uint8_t*)memory)[address] = data;
}

struct Bus* CreateTestBus()
{
    struct TestBus
    {
        struct Bus bus;
        uint8_t memory[0x10000];
    } *testBus = malloc(sizeof(struct TestBus));
    
    testBus->bus.Read = ReadMemory;
    testBus->bus.Write = WriteMemory;
    testBus->bus.memory = testBus->memory;

    return &testBus->bus;
}
