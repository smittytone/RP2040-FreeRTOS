cmake_minimum_required(VERSION 3.14)

# Set the version number
set(VERSION_NUMBER "1.0.0")

# Set the build number
# TODO Script to increment this with each build
set(BUILD_NUMBER "1")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})

# Set env variable 'PICO_SDK_PATH' to the local Pico SDK
# Comment out this line if you have a global copy of the
# SDK set and $PICO_SDK_PATH defined in your $PATH
set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/pico-sdk")

# Inlcude the Pico SDK
include(pico_sdk_import.cmake)

# Name the project
project(FREERTOS_PROJECT C CXX ASM
        VERSION ${VERSION_NUMBER}
        DESCRIPTION "FreeRTOS-based RP2040 application"
)

# Initialise the Pico SDK
pico_sdk_init()

# Set flags and directory variables
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DTSDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTSDEBUG")
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/Config")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel")
set(APP_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/App")

# Add FreeRTOS as a library
add_library(FreeRTOS STATIC
    ${FREERTOS_SRC_DIRECTORY}/event_groups.c
    ${FREERTOS_SRC_DIRECTORY}/list.c
    ${FREERTOS_SRC_DIRECTORY}/queue.c
    ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
    ${FREERTOS_SRC_DIRECTORY}/tasks.c
    ${FREERTOS_SRC_DIRECTORY}/timers.c
    ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
)

# Build FreeRTOS
target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_CFG_DIRECTORY}/
    ${FREERTOS_SRC_DIRECTORY}/include
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
)

# Include the application source code
add_subdirectory(${APP_SRC_DIRECTORY})

# Clean up
unset(FREERTOS_CFG_DIRECTORY)
unset(FREERTOS_SRC_DIRECTORY)
unset(APP_SRC_DIRECTORY)
