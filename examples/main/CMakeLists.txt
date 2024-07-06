file(GLOB MAIN_HEADERS include/main/*.h)
file(GLOB MAIN_SOURCES source/main/*.c)
add_executable(Main ${MAIN_HEADERS} ${MAIN_SOURCES})
target_link_libraries(Main
    PRIVATE MOS6502
)
target_include_directories(Main
    PRIVATE include/
)
set_target_properties(Main PROPERTIES
    FOLDER "Examples"
)
