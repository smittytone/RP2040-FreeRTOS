/**
 * RP2040 FreeRTOS Template
 * 
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.0.0
 * @license   MIT
 *
 */
#include "main.h"


/**
 * GLOBALS
 */
// This is the inter-task queue
volatile QueueHandle_t queue = NULL;

// Set a delay time of exactly 500ms
const TickType_t ms_delay = 500 / portTICK_PERIOD_MS;

/**
 * FUNCTIONS
 */

/**
 * @brief Repeatedly flash the Pico's built-in LED.
 */
void led_task_pico(void* unused_arg) {
    // Store the Pico LED state
    uint8_t pico_led_state = 0;
    
    // Configure the Pico's on-board LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    while (true) {
        // Turn Pico LED on an add the LED state
        // to the FreeRTOS xQUEUE
        log_debug("PICO LED FLASH");
        pico_led_state = 1;
        gpio_put(PICO_DEFAULT_LED_PIN, pico_led_state);
        xQueueSendToBack(queue, &pico_led_state, 0);
        vTaskDelay(ms_delay);
        
        // Turn Pico LED off an add the LED state
        // to the FreeRTOS xQUEUE
        pico_led_state = 0;
        gpio_put(PICO_DEFAULT_LED_PIN, pico_led_state);
        xQueueSendToBack(queue, &pico_led_state, 0);
        vTaskDelay(ms_delay);
    }
}


/**
 * @brief Repeatedly flash an LED connected to GPIO pin 20
 *        based on the value passed via the inter-task queue
 */
void led_task_gpio(void* unused_arg) {
    // This variable will take a copy of the value
    // added to the FreeRTOS xQueue
    uint8_t passed_value_buffer = 0;
    
    // Configure the GPIO LED
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    
    while (true) {
        // Check for an item in the FreeRTOS xQueue
        if (xQueueReceive(queue, &passed_value_buffer, portMAX_DELAY) == pdPASS) {
            // Received a value so flash the GPIO LED accordingly
            // (NOT the sent value)
            if (passed_value_buffer) log_debug("GPIO LED FLASH");
            gpio_put(GREEN_LED_PIN, passed_value_buffer == 1 ? 0 : 1);
        }
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
 * @brief Show basic device info.
 */
void log_device_info(void) {
    printf("App: %s %s\n Build: %i\n", APP_NAME, APP_VERSION, BUILD_NUM);
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
    
    // Set up the event queue
    queue = xQueueCreate(5, sizeof(uint8_t));
    
    // Log app info
    log_device_info();
    
    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
    
    // We shoild never get here, but just in case...
    while(true) {
        // NOP
    };
}
