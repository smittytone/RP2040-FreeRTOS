#!/usr/bin/env bash

#
# deploy
#
# Deploy RP2040 application code
#
# @copyright 2022, Tony Smith @smittytone
# @version   1.0.0
# @license   MIT
#

# GLOBALS
timeout=30
do_build=0
rpi_path="/Volumes/RPI-RP2"
uf2_path="UNDEFINED"

# FUNCTIONS
show_help() {
    echo -e "Usage:\n"
    echo -e "  deploy [-b][-h] /path/to/compiled/uf2/file\n"
    echo -e "Options:\n"
    echo "  -b / --build    Build the app first. Default: use a"
    echo "                  pre-built version of the app" 
    echo "  -h / --help     Show this help screen"
    echo
}

# RUNTIME START
for arg in "$@"; do
    check_arg=${arg,,}
    if [[ "$check_arg" = "--help" || "$check_arg" = "-h" ]]; then
        show_help
        exit 0
    elif [[ "$check_arg" = "--build" || "$check_arg" = "-b" ]]; then
        do_build=1
    else
        uf2_path="$arg"
    fi
done

if [[ "${uf2_path}" == "UNDEFINED" ]]; then
    show_help
    exit 0
fi

# Check we have what looks like a UF2
extension="${uf2_path##*.}"
if [[ "${extension}" != "uf2" ]]; then
    echo "[ERROR] ${uf2_path} does not indicate a .uf2 file"
    exit 1
fi

# Do we build first?
err=0
if [[ ${do_build} -eq 1 ]]; then
    if [[ ! -e "./build" ]]; then
        # No build folder? Then create it
        # and configure the build
        cmake -S . -B build/
        err=$?
    fi
    
    # Build the app
    cmake --build build
    err=$?
fi

# Check for errors
if [[ ${err} -ne 0 ]]; then
    exit 1
fi

# Wait for the RPI_R2 mount
count=0
if [ ! -e "${rpi_path}" ]; then
    echo "Waiting for RP2040 device to mount"
    while [ ! -e "${rpi_path}" ]; do
        sleep 1
        ((count+=1))
        if [[ $count -eq $timeout ]]; then
            echo "[ERROR] RP2040 device not mounted after ${timeout}s... exiting"
            exit 1
        fi
    done
fi

echo "RP2040 device mounted..."

# Check for available app file
if [ ! -e "${uf2_path}" ]; then
    echo "[ERROR] Cannot find file ${uf2_path}... exiting"
    exit 1
fi

echo "Copying ${uf2_path##*/} to ${rpi_path}/${uf2_path##*/}"

# Copy file
if cp "${uf2_path}" "${rpi_path}"; then
    echo "${uf2_path##*/} copied to ${rpi_path}"
else
    echo "[ERROR] Could not copy ${uf2_path##*/} to ${rpi_path}/${uf2_path##*/}"
    exit 1
fi

exit 0
