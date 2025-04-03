#ifndef LORA_IOT_LED_H
#define LORA_IOT_LED_H

#include <Arduino.h>
#include "esp32-hal-gpio.h"

#define GPIO_RED_LED 6
#define GPIO_YELLOW_LED 5
#define GPIO_GREEN_LED 4

void led_init();

void led_red(bool up);
void led_yellow(bool up);
void led_green(bool up);

#endif // LORA_IOT_LED_H