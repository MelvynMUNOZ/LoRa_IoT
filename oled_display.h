#ifndef LORA_IOT_OLED_DISPLAY_H
#define LORA_IOT_OLED_DISPLAY_H

#include <cstdint>
#include <Arduino.h>
#include <Wire.h>               
#include "HT_SSD1306Wire.h"

#define OLED_ADDR 0x3C
#define OLED_FREQ 500000

extern SSD1306Wire oled_display;

bool oled_display_init();

void oled_display_print_proximity(uint8_t line_number);
void oled_display_print_light(uint8_t line_number);
void oled_display_print_temperature_humidity(uint8_t line_number);
void oled_display_print_pressure(uint8_t line_number);
void oled_display_print_gas_resistance(uint8_t line_number);
void oled_display_print_altitude(uint8_t line_number);
void oled_display_print_hb(uint8_t line_number);

#endif // LORA_IOT_OLED_DISPLAY_H