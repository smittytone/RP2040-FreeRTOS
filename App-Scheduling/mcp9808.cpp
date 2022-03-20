/**
 * RP2040 FreeRTOS Template - App #2
 * MCP9808 I2C temperature sensor driver
 *
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.2.0
 * @licence   MIT
 *
 */
#include "main.h"

using std::string;


/**
 * @brief Constructor: instantiate a new MCP9808 object.
 *
 * @param address: The I2C address of the device to write to.
 */
MCP9808::MCP9808(uint32_t address) {
    if (address == 0x00 || address > 0xFF) address = MCP9808_I2CADDR_DEFAULT;
    i2c_addr = address;
}


/**
 * @brief Check the device is connected and operational.
 *
 * @retval `true` if we can read values and they are right, otherwise `false`.
 */
bool MCP9808::begin() {
    // Prep data storage buffers
    uint8_t mid_data[2] = {0,0};
    uint8_t did_data[2] = {0,0};

    // Read bytes from the sensor: MID...
    I2C::write_byte(i2c_addr, MCP9808_REG_MANUF_ID);
    I2C::read_block(i2c_addr, mid_data, 2);

    // ...DID
    I2C::write_byte(i2c_addr, MCP9808_REG_DEVICE_ID);
    I2C::read_block(i2c_addr, did_data, 2);

    // Bytes to integers
    const uint16_t mid_value = (mid_data[0] << 8) | mid_data[1];
    const uint16_t did_value = (did_data[0] << 8) | did_data[1];

    // Returns True if the device is initialised, False otherwise.
    return (mid_value == 0x0054 && did_value == 0x0400);
}


/**
 * @brief Check the device is connected and operational.
 *
 * @retval `true` if the sensor is correct, otherwise `false`.
 */
double MCP9808::read_temp() {
    // Read sensor and return its value in degrees celsius.
    uint8_t temp_data[2] = {0,0};
    I2C::write_byte(i2c_addr, MCP9808_REG_AMBIENT_TEMP);
    I2C::read_block(i2c_addr, temp_data, 2);

    // Scale and convert to signed value.
    const uint32_t temp_raw = (temp_data[0] << 8) | temp_data[1];
    double temp_cel = (temp_raw & 0x0FFF) / 16.0;
    if (temp_raw & 0x1000) temp_cel -= 256.0;
    return temp_cel;
}
