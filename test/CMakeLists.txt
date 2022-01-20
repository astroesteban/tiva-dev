add_executable(test_tm4c_blinky test_tm4c_blinky.cpp)

target_link_libraries(
    test_tm4c_blinky
    PRIVATE
    project_options
    $<IF:$<STREQUAL:${TARGET_MICROCONTROLLER},tm4c123gxl>,texas_instruments::tm4c,>
    $<IF:$<BOOL:${USE_TIVAWARE}>,tivaware::tivaware,>
)

target_include_directories(test_tm4c_blinky PRIVATE ${PROJECT_SOURCE_DIR}/include)

# We need to convert our ELF file to a binary file before flashing.
# Here is a custom helper command to help you do that.
add_custom_target(test_tm4c_blinky.bin ALL DEPENDS test_tm4c_blinky)
add_custom_command(TARGET test_tm4c_blinky.bin
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary test_tm4c_blinky${CMAKE_EXECUTABLE_SUFFIX_C} test_tm4c_blinky.bin)

# Need to flash from the CLI using `sudo make flash` in the build dir
add_custom_target(flash DEPENDS test_tm4c_blinky.bin)
set_target_properties(flash PROPERTIES EXCLUDE_FROM_ALL TRUE)
add_custom_command(TARGET flash USES_TERMINAL COMMAND lm4flash test_tm4c_blinky.bin)