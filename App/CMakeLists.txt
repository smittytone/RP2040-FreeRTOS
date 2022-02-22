cmake_minimum_required(VERSION 3.14)

if(${DO_DEBUG})
    add_compile_definitions(DEBUG=1)
    message(STATUS "App-side debugging set")
else()
    message(STATUS "App-side debugging disabled")
endif()

add_executable(${APP_NAME}
    main.c
)

target_link_libraries(${APP_NAME} LINK_PUBLIC
    pico_stdlib
    hardware_gpio
    FreeRTOS)

pico_enable_stdio_usb(${APP_NAME} 1)
pico_enable_stdio_uart(${APP_NAME} 1)
pico_add_extra_outputs(${APP_NAME})
