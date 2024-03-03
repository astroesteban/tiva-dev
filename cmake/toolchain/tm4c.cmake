# Cross-Compilation Toolchain for the TM4C123GH6PM microcontroller. This
# toolchain was made following the guidelines of "Professional CMake: A 
# Practical Guide" by Craig Scott. A good toolchain file is as minimal as
# possible.

# Set the system information
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_CROSSCOMPILING TRUE)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY" CACHE STRING "Try Static Lib Type" FORCE)
set(TARGET_MICROCONTROLLER "tm4c123gxl" CACHE STRING "The name of the target microcontroller" FORCE)
message("-- Set the target microcontroller to the ${TARGET_MICROCONTROLLER}")

# Set the GNU ARM toolchain
set(CMAKE_AR            arm-none-eabi-ar)
set(CMAKE_C_COMPILER    arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER  arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-as)
set(CMAKE_OBJCOPY       arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP       arm-none-eabi-objdump)
set(CMAKE_C_GDB         gdb-multiarch)

# Setup your compiler flags. The XXX_INIT initializes the cache entry the first 
# time a build tree is configured. That way the user can add or remove their own
# flags without overriding the flags set by this toolchain.
#
# One thing that always confused me is that '-specs' argument we pass. That
# specifies the standard library implementation. GNU defaults to Newlib which 
# is an implementation of the C Standard Library targeted at bare-metal 
# embedded systems that is maintained by RedHat. When code-size constrained, 
# you may choose to use a variant of newlib, called newlib-nano, which does 
# away with some C99 features, and some printf bells and whistles to deliver a 
# more compact standard library. You can set your specifications as follows:
# -specs=nosys.specs                -- defines that system calls should be implemented as stubs that return errors when called
# -specs=nano.specs                 -- used for Newlib-nano
# -specs=rdimon.specs               -- for semihosting, you can use system calls (and also printf), but this relies on a debugger being attached, and the CPU may crash if no debugger is present.
# -nostdlib                         -- no standard library at all
# You can also see what sections it removes by adding -Wl,--print-gc-sections to CMAKE_C_FLAGS_INIT
set(CMAKE_C_FLAGS_INIT "-mcpu=cortex-m4 -march=armv7e-m -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -fno-common -fstack-usage -Wdouble-promotion -Wconversion -Wstack-usage=32000 --specs=nano.specs -Wl,--gc-sections")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -fno-exceptions -fno-rtti -fno-unwind-tables")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-e Reset_Handler -T${CMAKE_CURRENT_LIST_DIR}/support/tm4c123gh6pm.ld")

# Force the toolchain to generate ELF files
set(CMAKE_EXECUTABLE_SUFFIX_C   .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)