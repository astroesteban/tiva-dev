####
# 'fprime-tm4c' Deployment:
#
# This sets up the build for the 'fprime-tm4c' library package, including the
# custom components. In addition, it imports FPrime.cmake, which includes the
# core F Prime components.
#
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
    VERSION 0.1.0
    LANGUAGES C CXX
)
include(cmake/standard_project_settings.cmake)
include(cmake/prevent_in_source_builds.cmake)

# link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_11 c_std_11)

# Add linker configuration
include(cmake/linker.cmake)
configure_linker(project_options)

# project options
option(USE_TIVAWARE "Download the TivaWare library" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)

add_subdirectory(boards)
add_subdirectory(third-party)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
