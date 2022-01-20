###
# Includes system-required definitions like the startup file and the system
# calls for the TM4C.
# The linker script is also stored here but it is added in the
# toolchain-tm4c.cmake file.
#
# I couldn't figure out why my syscalls were still being "not found" during
# linking and this blog post helped me resolve that bug:
# https://jonathanhamberg.com/post/gcc-archive-linker-oddity/
###
add_library(tm4c startup.c syscalls.c)
# target_link_libraries(tm4c PRIVATE project_options)
target_link_options(tm4c PUBLIC -Wl,--whole-archive ${CMAKE_CURRENT_BINARY_DIR}/libtm4c.a -Wl,--no-whole-archive)
add_library(texas_instruments::tm4c ALIAS tm4c)