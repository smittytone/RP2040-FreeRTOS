#!/usr/bin/env bash

#
# deploy
#
# Deploy RP2040 application code
#
# @author    Tony Smith
# @copyright 2022, Tony Smith @smittytone
# @version   1.0.1
# @license   MIT
#

# GLOBALS
timeout=30
uf2_path="./build/App/PICO_PROJECT_NAME.uf2"
rpi_path="/Volumes/RPI-RP2"

# FUNCTIONS
show_help() {
    echo -e "Usage:\n"
    echo -e "  deploy [-h] /optional/path/to/Microvisor/app/bunde.zip\n"
    echo -e "Options:\n"
    echo "  -h / --help     Show this help screen"
    echo
}

# RUNTIME START
for arg in "$@"; do
    check_arg=${arg,,}
    if [[ "$check_arg" = "--help" || "$check_arg" = "-h" ]]; then
        show_help
        exit 0
    else
        zip_path="$arg"
    fi
done

# Check we have what looks like a UF2
extension="${uf2_path##*.}"
if [[ "${extension}" != "uf2" ]]; then
    echo "[ERROR] ${uf2_path} does not indicate a .uf2 file"
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
echo "Copying ${uf2_path##*/} to ${rpi_path}/${uf2_path##*/}"

# Copy file
if cp "${uf2_path}" "${rpi_path}/${uf2_path##*/}"; then
    echo "${uf2_path##*/} copied to ${rpi_path}"
else
    echo "[ERROR] Could not copy ${uf2_path##*/} to ${rpi_path}/${uf2_path##*/}"
    exit 1
fi

exit 0