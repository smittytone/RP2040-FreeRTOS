cmake_minimum_required(VERSION 3.14)

# Should we set app-level debugging?
# NOTE Equivalent of `#define DEBUG 1`
if(${DO_DEBUG})
    add_compile_definitions(DEBUG=1)
    message(STATUS "App-side debugging set")
else()
    message(STATUS "App-side debugging disabled")
endif()

# Include app source code file(s)
add_executable(${APP_NAME}
    main.c
)

# Link to built libraries
target_link_libraries(${APP_NAME} LINK_PUBLIC
    pico_stdlib
    hardware_gpio
    FreeRTOS)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_NAME} 1)
pico_enable_stdio_uart(${APP_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${APP_NAME})
