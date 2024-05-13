add_executable(switches src/switches.cpp)

target_link_libraries(
    switches
    PRIVATE
    project_options
    $<IF:$<STREQUAL:${TARGET_MICROCONTROLLER},tm4c123gxl>,texas_instruments::tm4c,>
    $<IF:$<BOOL:${USE_TIVAWARE}>,tivaware::tivaware,>
)

target_include_directories(switches PRIVATE inc)

# We need to convert our ELF file to a binary file before flashing.
# Here is a custom helper command to help you do that.
add_custom_target(switches.bin ALL DEPENDS switches)
add_custom_command(TARGET switches.bin
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary switches${CMAKE_EXECUTABLE_SUFFIX_C} switches.bin)

# # Need to flash from the CLI using `sudo make flash` in the build dir
# add_custom_target(flash DEPENDS switches.bin)
# set_target_properties(flash PROPERTIES EXCLUDE_FROM_ALL TRUE)
# add_custom_command(TARGET flash USES_TERMINAL COMMAND lm4flash switches.bin)
