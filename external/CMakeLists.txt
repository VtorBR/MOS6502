include(FetchContent)

if (MOS6502_TEST)
	FetchContent_Declare(
		6502_65C02_functional_tests
		GIT_REPOSITORY https://github.com/Klaus2m5/6502_65C02_functional_tests.git
		SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/6502_65C02_functional_tests
	)

	FetchContent_Populate(6502_65C02_functional_tests)
endif()
