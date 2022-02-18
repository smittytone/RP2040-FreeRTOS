#include "main.h"


/**
 * @brief Repeatedly flash the Pico's built-in LED.
 */
void led_task_pico(void* unused_arg) {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    while (true) {
        log_debug("PICO LED FLASH");
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        vTaskDelay(50);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        vTaskDelay(50);
    }
}


/**
 * @brief Repeatedly flash an LED connected to GPIO pin 20.
 */
void led_task_gpio(void* unused_arg) {
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    
    while (true) {
        log_debug("GPIO LED FLASH");
        gpio_put(GREEN_LED_PIN, 0);
        vTaskDelay(50);
        gpio_put(GREEN_LED_PIN, 1);
        vTaskDelay(50);
    }
}


/**
 * @brief Generate and print a debug message from a supplied string.
 *
 * @param msg: The base message to which `[DEBUG]` will be prefixed.
 */
void log_debug(const char* msg) {
    uint msg_length = 9 + strlen(msg);
    char* sprintf_buffer = malloc(msg_length);
    sprintf(sprintf_buffer, "[DEBUG] %s\n", msg);
    printf("%s", sprintf_buffer);
    free(sprintf_buffer);
}


/**
 * RUNTIME START
 */
int main() {
    // Enable STDIO
    stdio_usb_init();
    
    // Set up two tasks
    xTaskCreate(led_task_pico, "PICO_LED_TASK", 256, NULL, 1, NULL);
    xTaskCreate(led_task_gpio, "GPIO_LED_TASK", 256, NULL, 1, NULL);
    
    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
    
    // We shoild never get here, but just in case...
    while(true) {
        // NOP
    };
}
