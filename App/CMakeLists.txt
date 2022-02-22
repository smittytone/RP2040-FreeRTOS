cmake_minimum_required(VERSION 3.14)

# Comment out the following for a release
add_compile_definitions(DEBUG=1)

add_executable(FREERTOS_PROJECT
    main.c
)

target_link_libraries(FREERTOS_PROJECT LINK_PUBLIC
    pico_stdlib
    hardware_gpio
    FreeRTOS)

pico_enable_stdio_usb(FREERTOS_PROJECT 1)
pico_enable_stdio_uart(FREERTOS_PROJECT 1)
pico_add_extra_outputs(FREERTOS_PROJECT)
