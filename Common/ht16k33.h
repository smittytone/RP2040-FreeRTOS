/**
 * RP2040 FreeRTOS Template - App #2
 * HT16K33-based I2C 4-digit, 7-segment LED display driver
 * 
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.4.1
 * @licence   MIT
 *
 */
#ifndef HT16K33_HEADER
#define HT16K33_HEADER


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
#include "i2c_utils.h"
#include "utils.h"


/*
 * CONSTANTS
 */
#define HT16K33_GENERIC_DISPLAY_ON          0x81
#define HT16K33_GENERIC_DISPLAY_OFF         0x80
#define HT16K33_GENERIC_SYSTEM_ON           0x21
#define HT16K33_GENERIC_SYSTEM_OFF          0x20
#define HT16K33_GENERIC_DISPLAY_ADDRESS     0x00
#define HT16K33_GENERIC_CMD_BRIGHTNESS      0xE0
#define HT16K33_GENERIC_CMD_BLINK           0x81
#define HT16K33_ADDRESS                     0x70

#define HT16K33_SEGMENT_COLON_ROW           0x04
#define HT16K33_SEGMENT_MINUS_CHAR          0x10
#define HT16K33_SEGMENT_DEGREE_CHAR         0x11
#define HT16K33_SEGMENT_SPACE_CHAR          0x00


/**
    A basic driver for I2C-connected HT16K33-based four-digit, seven-segment displays.
 */
class HT16K33_Segment {

    public:
        HT16K33_Segment(uint32_t address = HT16K33_ADDRESS);

        void                init();
        void                power_on(bool turn_on = true);

        void                set_brightness(uint32_t brightness = 15);
        HT16K33_Segment&    set_colon(bool is_set = false);
        HT16K33_Segment&    set_glyph(uint32_t glyph, uint32_t digit, bool has_dot = false);
        HT16K33_Segment&    set_number(uint32_t number, uint32_t digit, bool has_dot = false);
        HT16K33_Segment&    set_alpha(char chr, uint32_t digit, bool has_dot = false);

        HT16K33_Segment&    clear();
        void                draw();


    private:
        uint8_t             buffer[16];
        uint32_t            pos[4];
        uint32_t            i2c_addr;
};


#endif  // HT16K33_HEADER
