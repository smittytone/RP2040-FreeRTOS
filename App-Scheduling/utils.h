/**
 * RP2040 FreeRTOS Template - App #2
 * General utility functions
 *
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.2.0
 * @licence   MIT
 *
 */
#ifndef _UTILS_HEADER_
#define _UTILS_HEADER_

using std::vector;
using std::string;


/*
 * PROTOTYPES
 */
namespace Utils {
    vector<string>  split_to_lines(string str, string sep = "\r\n");
    string          split_msg(string msg, uint32_t want_line);
    string          get_sms_number(string line);
    string          get_field_value(string line, uint32_t field_number);
    string          uppercase(string base);
    uint32_t        bcd(uint32_t base);
}


#endif // _UTILS_HEADER_
