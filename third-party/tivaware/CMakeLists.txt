###
# Download the tivaware dependency.
###
FetchContent_Declare(
  tivaware
  URL https://github.com/astroesteban/tivaware/archive/refs/tags/v2.2.0.295.zip
  URL_HASH MD5=f4239367bc4d7cdbda27625106006101
)

message(STATUS "Downloading TivaWare...")

# download the release zip
FetchContent_MakeAvailable(tivaware)

# set the path to the tivaware source folder
set(TIVAWARE_PATH ${tivaware_SOURCE_DIR} CACHE PATH "Path to the TivaWare library" FORCE)

# build the tivaware library. We only need the driverlib for now.
execute_process(
  COMMAND make -j 8
  WORKING_DIRECTORY ${tivaware_SOURCE_DIR}/driverlib
)

add_library(tivaware STATIC IMPORTED GLOBAL)
set_target_properties(tivaware PROPERTIES IMPORTED_LOCATION ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a)
target_include_directories(tivaware SYSTEM INTERFACE ${TIVAWARE_PATH})
target_compile_definitions(tivaware INTERFACE PART_TM4C123GH6PM TARGET_IS_TM4C123_RA1)
add_library(tivaware::tivaware ALIAS tivaware)