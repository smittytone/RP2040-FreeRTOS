# RP2040-FreeRTOS

This repo contains my base project for [FreeRTOS](https://freertos.org/) on the [Raspberry Pi RP2040 microcontroller](https://www.raspberrypi.com/products/rp2040/).

## Project Structure

```
/RP2040-FreeRTOS
|___/App                    // Application source code
    |___CMakeLists.txt      // Application-level CMake config file
|___/Config
    |___FreeRTOSConfig.h    // FreeRTOS project config file
|___/FreeRTOS-Kernel        // FreeRTOS kernel files, included as a submodule
|___/pico-sdk               // Raspberry Pi Pico SDK, included as a submodule
|___CMakeLists.txt          // Top-level project CMake config file
|___pico_sdk_import.cmake   // Raspberry Pi Pico SDK CMake import script
|___deploy.sh               // Build-and-deploy shell script
|___rp2040.code-workspace   // Visual Studio Code workspace
|___rp2040.xcworkspace      // Xcode workspace
|___README.md
|___LICENSE.md
```

## Prerequisites

To use the code in this repo, your system must be set up for RP2040 C/C++ development. See [this blog post of mine](https://blog.smittytone.net/2021/02/02/program-raspberry-pi-pico-c-mac/) for setup details.

## Usage

1. Clone the repo: `git clone https://github.com/smittytone/RP2040-FreeRTOS`.
1. Enter the repo: `cd RP2040-FreeRTOS`.
1. Install the submodules: `git submodule update --init --recursive`.
1. Optionally, edit `CMakeLists.txt` and `/App/CMakeLists.txt` to rename the project.
1. Configure the tools: `cmake -S . -B build/`.
1. Build the app: `cmake --build build`.
1. Connect your device.
1. Install the app: `./deploy.sh`.
    * If you have changed the name of the project, run this as: `./deploy.sh build/App/<MY_PROJECT>.uf2`.
    
## IDEs

Workspace files are included for the Visual Studio Code and Xcode IDEs.

## Copyright and Licences

Application source © 2022, Tony Smith and licensed under the terms of the [MIT Licence](./LICENSE.md).

[FreeRTOS](https://freertos.org/) © 2021, Amazon Web Services, Inc. It is also licensed under the terms of the [MIT Licence](./LICENSE.md).

The [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) is © 2020, Raspberry Pi (Trading) Ltd. It is licensed under the terms of the [BSD 3-Clause "New" or "Revised" Licence](https://github.com/raspberrypi/pico-sdk/blob/master/LICENSE.TXT).
