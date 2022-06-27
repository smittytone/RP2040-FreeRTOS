/**
 * RP2040 FreeRTOS Template - App #3
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
#define         RED_LED_PIN                 20
#define         ALERT_LED_PIN               26
#define         ALERT_SENSE_PIN             16

#define         SENSOR_TASK_DELAY_TICKS     20
#define         ALERT_DISPLAY_PERIOD_MS     10000

#define         LED_ON                      1
#define         LED_OFF                     0
#define         LED_ERROR_FLASHES           5

#define         TEMP_LOWER_LIMIT_C          10
#define         TEMP_UPPER_LIMIT_C          25
#define         TEMP_CRIT_LIMIT_C           50


/**
 * PROTOTYPES
 */
void setup();
void setup_led();
void setup_i2c();
void setup_gpio();

void enable_irq(bool state = true);
void gpio_isr(uint gpio, uint32_t events);

void led_on();
void led_off();
void led_set(bool state = true);

void task_led_pico(void* unused_arg);
void task_led_gpio(void* unused_arg);
void task_sensor_read(void* unused_arg);
void task_sensor_alrt(void* unused_arg);

void display_int(int number);
void display_tmp(double value);

void timer_fired_callback(TimerHandle_t timer);
void set_alert_timer();


#ifdef __cplusplus
}           // extern "C"
#endif


#endif      // MAIN_H
