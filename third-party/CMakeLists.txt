
##
# With this new project I wanted to learn something new. A hopefully better
# approach to managing project dependencies via CMake's FetchContent. This is
# a great alternative to git submodules that allows CMake to manage all your
# project external dependencies for you at configuration time.
#
# https://cmake.org/cmake/help/latest/module/FetchContent.html
# https://eliasdaler.github.io/using-cmake/
##
include(FetchContent)

# force CMake to download the dependency only if it hasn't been populated yet
# without making further attempts to update it every time.
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

if(USE_TIVAWARE)
    add_subdirectory(tivaware)
endif()