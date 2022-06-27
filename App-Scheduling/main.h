/**
 * RP2040 FreeRTOS Template - App #2
 *
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.4.1
 * @licence   MIT
 *
 */
#ifndef MAIN_H
#define MAIN_H


// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
// CXX
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <algorithm>
// Pico SDK
#include "pico/stdlib.h"            // Includes `hardware_gpio.h`
#include "pico/binary_info.h"
#include "hardware/i2c.h"
// App
#include "../Common/i2c_utils.h"
#include "../Common/ht16k33.h"
#include "../Common/mcp9808.h"
#include "../Common/utils.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * CONSTANTS
 */
#define         RED_LED_PIN           20


/**
 * PROTOTYPES
 */
void setup();
void setup_led();
void setup_i2c();

void led_on();
void led_off();
void led_set(bool state = true);

void led_task_pico(void* unused_arg);
void led_task_gpio(void* unused_arg);
void sensor_read_task(void* unused_arg);

void display_int(int number);
void display_tmp(double value);


#ifdef __cplusplus
}           // extern "C"
#endif


#endif      // MAIN_H
