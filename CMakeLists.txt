####
# To generate a dependency graph run:
#   > cmake --graphviz=graph ..
#   > dot graph -Tsvg -o graph.svg
# You can also install an extension like `SVG Viewer` to view the SVG file
# directly in VS Code.
#
# Author: @astroesteban
####
cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE cmake/toolchain/tm4c.cmake)

project(
    tm4c
    VERSION 1.0.0
    LANGUAGES C CXX
)
include(cmake/standard_project_settings.cmake)
include(cmake/prevent_in_source_builds.cmake)

# link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23 c_std_23)

# Add linker configuration
include(cmake/linker.cmake)
configure_linker(project_options)

# project options
option(USE_TIVAWARE "Download the TivaWare library" ON)
option(ENABLE_TESTING "Enable Test Builds" OFF)
option(ENABLE_EXAMPLES "Enable Example Builds" ON)

add_subdirectory(boards)
add_subdirectory(third-party)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

if(ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif()
