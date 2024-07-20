file(GLOB TestFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test.c)

create_test_sourcelist (Tests MOS6502_Tester.c ${TestFiles}
	EXTRA_INCLUDE testbus.h
)

add_executable (MOS6502_Tester ${Tests} testbus.c)

target_link_libraries(MOS6502_Tester
	PRIVATE MOS6502
)

target_include_directories(MOS6502_Tester
	PRIVATE /
	PRIVATE ../source/
)
set_target_properties(MOS6502_Tester PROPERTIES
	FOLDER "Test"
)

foreach (TestFile ${TestFiles})
	get_filename_component (TestName ${TestFile} NAME_WE)
	add_test (NAME ${TestName} COMMAND MOS6502_Tester ${TestName})
endforeach ()
