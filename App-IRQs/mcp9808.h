/**
 * RP2040 FreeRTOS Template - App #3
 * MCP9808 I2C temperature sensor driver
 * 
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.2.0
 * @licence   MIT
 *
 */
#ifndef _MCP9808_HEADER_
#define _MCP9808_HEADER_


/*
 * PROTOTYPES
 */
// Default I2C address for device
#define MCP9808_I2CADDR_DEFAULT     0x18

// Register addresses
#define MCP9808_REG_CONFIG          0x01
#define MCP9808_REG_UPPER_TEMP      0x02
#define MCP9808_REG_LOWER_TEMP      0x03
#define MCP9808_REG_CRIT_TEMP       0x04
#define MCP9808_REG_AMBIENT_TEMP    0x05
#define MCP9808_REG_MANUF_ID        0x06
#define MCP9808_REG_DEVICE_ID       0x07

#define MCP9808_CONFIG_CLR_ALRT_INT 0x20
#define MCP9808_CONFIG_ENABLE_ALRT  0x08
#define MCP9808_CONFIG_ALRT_POL     0x02
#define MCP9808_CONFIG_ALRT_MODE    0x01

/**
    A very basic driver for the I2C-connected MCP9808 temperature sensor.
 */
class MCP9808 {

    public:
        // Constructor
        MCP9808(uint32_t i2c_address = MCP9808_I2CADDR_DEFAULT);

        bool        begin();
        double      read_temp();
        void        clear_alert(bool do_enable);
        void        set_upper_limit(uint16_t upper_temp);
        void        set_lower_limit(uint16_t lower_temp);
        void        set_critical_limit(uint16_t critical_temp);
        void        set_temp_limit(uint8_t register, uint16_t lower_temp);
    
    private:
        double      get_temp(uint8_t* data);
        
        uint8_t     i2c_addr;
};


#endif // _MCP9808_HEADER_
