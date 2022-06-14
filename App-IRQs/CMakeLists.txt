cmake_minimum_required(VERSION 3.14)

# Should we set app-level debugging?
# NOTE Equivalent of `#define DEBUG 1`
if(${DO_DEBUG})
    add_compile_definitions(DEBUG=1)
    message(STATUS "App-side debugging enabled for ${APP_3_NAME}")
else()
    message(STATUS "App-side debugging disabled for ${APP_3_NAME}")
endif()

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APP_3_NAME}")
add_compile_definitions(APP_VERSION="${APP_3_VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})

# Include app source code file(s)
add_executable(${APP_3_NAME}
    ${APP_3_SRC_DIRECTORY}/main.cpp
    ${COMMON_CODE_DIRECTORY}/ht16k33.cpp
    ${COMMON_CODE_DIRECTORY}/i2c_utils.cpp
    ${COMMON_CODE_DIRECTORY}/mcp9808.cpp
    ${COMMON_CODE_DIRECTORY}/utils.cpp
)

# Link to built libraries
target_link_libraries(${APP_3_NAME} LINK_PUBLIC
    pico_stdlib
    hardware_i2c
    FreeRTOS)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_3_NAME} 1)
pico_enable_stdio_uart(${APP_3_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${APP_3_NAME})
