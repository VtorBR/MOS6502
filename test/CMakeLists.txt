add_executable(Tester tester.c)
target_link_libraries(Tester
	PRIVATE MOS6502
)

add_test(NAME FunctionalTest
	COMMAND Tester ${PROJECT_SOURCE_DIR}/external/6502_65C02_functional_tests/bin_files/6502_functional_test.bin 100000000 1024
)

set_property(TEST FunctionalTest
	PROPERTY PASS_REGULAR_EXPRESSION "Trapped at 3469"
)
