file(GLOB APPLEI_HEADERS source/applei/*.h)
file(GLOB APPLEI_SOURCES source/applei/*.c)
add_executable(AppleI ${APPLEI_HEADERS} ${APPLEI_SOURCES})
target_link_libraries(AppleI
	PRIVATE MOS6502
)
target_include_directories(AppleI
	PRIVATE source/
)
set_target_properties(AppleI PROPERTIES
	FOLDER "Example"
)
