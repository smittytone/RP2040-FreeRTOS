/**
 * RP2040 FreeRTOS Template - App #4
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
#include <timers.h>
#include <semphr.h>
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
// App
#include "../Common/utils.h"


using std::string;


/**
 * CONSTANTS
 */
#define         LED_FLASH_PERIOD_MS         2000
#define         LED_OFF_PERIOD_MS           100

#define         TIMER_ID_LED_ON             0
#define         TIMER_ID_LED_OFF            255

#define         LED_ON                      1
#define         LED_OFF                     0
#define         LED_ERROR_FLASHES           5


#ifdef __cplusplus
extern "C" {
#endif


/**
 * PROTOTYPES
 */
void setup_led();
void led_on();
void led_off();
void led_set(bool state = true);

void task_led_pico(void* unused_arg);

void timer_fired_callback(TimerHandle_t timer);


#ifdef __cplusplus
}           // extern "C"
#endif


#endif      // MAIN_H
