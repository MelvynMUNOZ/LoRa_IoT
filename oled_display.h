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

void oled_display_print_proximity();
void oled_display_print_light();

#endif // LORA_IOT_OLED_DISPLAY_H