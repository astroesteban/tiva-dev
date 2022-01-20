###
# File Name:
#   flash.sh
#
# Details:
#   Flashes the Texas Instruments TM4C launchpad with the user-provided exe.
#   This script serves as an alternative to CMake's `flash` target for macOS
#   due to the limitation of accessing USB devices on macOS from Docker.
###
#!/bin/bash

# `````````````````````````````````````````````````````````````````````````````
# Function name: _help()
#
# Description:
#   Provides help information
#
function _help() {
    echo "Usage: $0 [arguments]"
    echo "Options:"
    echo "    -h) Print usage information"
    echo "    -p {path}) The path to the executable to flash"
}

# Get CLI options & arguments
while getopts "hp:" flag; do
case "${flag}" in
    p) EXE_PATH=${OPTARG};;
    h) _help; exit 0;
esac
done

# If no options were passed in
if [ $OPTIND -eq 1 ]; then _help; exit 0; fi

lm4flash ${EXE_PATH}