#ifndef _MAIN_H_
#define _MAIN_H_


// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
// C
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
// Pico SDK
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * CONSTANTS
 */
#define     GREEN_LED_PIN           20


/**
 * PROTOTYPES
 */
void led_task_pico(void* unused_arg);
void led_task_gpio(void* unused_arg);
void log_debug(const char* msg);


#ifdef __cplusplus
}           // extern "C"
#endif


#endif      // _MAIN_H_
