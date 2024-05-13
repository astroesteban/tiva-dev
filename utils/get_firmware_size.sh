#!/bin/bash
###
# file name:
#   get_firmware_size.sh
#
# details:
#   pretty much a wrapper around arm-none-eabi-size that gives you the actual
#   usage of flash and ram of your firmware.
#
# example:
#   $ ./get_firmware_size.sh firmware_name.elf 0x40000 0x8000
#       Flash used: 10904 / 262144 (4%)
#       RAM used: 8376 / 32768 (25%)
#
# author(s):
#   @memfault
###


# `````````````````````````````````````````````````````````````````````````````
# function name: _print_region()
#
# description:
#   prints the memory region usage
#
function _print_region() {
    local size=$1
    local max_size=$2
    local name=$3

    if [[ $max_size == 0x* ]];
    then
        max_size=$(echo ${max_size:2})
        max_size=$(( 16#$max_size ))
    fi

    pct=$(( 100 * $size / $max_size ))
    echo "$name used: $size / $max_size ($pct%)"
}


# check that we have the correct number of command line arguments
if [  $# -le 2 ]
then
    echo "This script requires 3 arguments."
    echo -e "\nUsage:\nget-fw-size FILE MAX_FLASH_SIZE MAX_RAM_SIZE \n"
    exit 1
fi

# storage variables to hold our arguments
file=${1}
max_flash=${2}
max_ram=${3}

# invoke the arm-none-eabi-size tool and redirect the output to a variable
raw=$(arm-none-eabi-size $file)

# split the segments output by the size tool into separate variables
text=$(echo ${raw} | cut -d ' ' -f 7)
data=$(echo ${raw} | cut -d ' ' -f 8)
bss=$(echo ${raw} | cut -d ' ' -f 9)

# flash is text section plus data section
flash=$((${text} + ${data}))
# ram is data section plus bss section
ram=$((${data} + ${bss}))

# print the two regions
_print_region $flash $max_flash "Flash"
_print_region $ram $max_ram "RAM"