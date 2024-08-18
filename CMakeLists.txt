cmake_minimum_required(VERSION 3.21)

project(MOS6502 LANGUAGES C)

option(MOS6502_TEST "Includes tests for MOS6502" ON)
option(MOS6502_EXAMPLES "Includes examples of MOS6502 usage" ON)

add_subdirectory(external)

file(GLOB MOS6502_HEADERS include/mos6502/*.h source/mos6502/*.h)
file(GLOB MOS6502_SOURCES source/mos6502/*.c)
add_library(MOS6502 STATIC ${MOS6502_SOURCES} ${MOS6502_HEADERS})
target_include_directories(MOS6502
	PUBLIC include/
	PRIVATE source/
)

if (MOS6502_EXAMPLES)
	add_subdirectory(example)
endif()

if (MOS6502_TEST)
	enable_testing()
	add_subdirectory(test)
endif()
