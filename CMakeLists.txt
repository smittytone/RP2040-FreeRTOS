cmake_minimum_required(VERSION 3.14)

# Set project data
set(PROJECT_NAME "RP2040_FREERTOS_PROJECT")
set(BUILD_NUMBER "1")

# Set app name(s) and version(s)
set(APP_1_NAME "TEMPLATE")
set(APP_1_VERSION_NUMBER "1.1.0")

set(APP_2_NAME "SCHEDULING_DEMO")
set(APP_2_VERSION_NUMBER "1.1.0")

# Set app-side debugging ON or OFF
set(DO_DEBUG ON)

# Introduction...
message("Building ${PROJECT_NAME} ${VERSION_NUMBER} (${BUILD_NUMBER})")

# Set env variable 'PICO_SDK_PATH' to the local Pico SDK
# Comment out the set() if you have a global copy of the
# SDK set and $PICO_SDK_PATH defined in your $PATH
set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/pico-sdk")

# Set flags and directory variables
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DTSDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTSDEBUG")
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/Config")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel")

# Specify the app(s) source code
set(APP_1_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/App-Template")
set(APP_2_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/App-Scheduling")

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Name the project
project(${PROJECT_NAME}
        LANGUAGES C CXX ASM
        DESCRIPTION "FreeRTOS-based RP2040 applications"
)

# Initialise the Pico SDK
pico_sdk_init()

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

# Include the apps' source code
add_subdirectory(${APP_1_SRC_DIRECTORY})
add_subdirectory(${APP_2_SRC_DIRECTORY})

# Clean up
unset(FREERTOS_CFG_DIRECTORY)
unset(FREERTOS_SRC_DIRECTORY)
unset(APP_SRC_DIRECTORY)
