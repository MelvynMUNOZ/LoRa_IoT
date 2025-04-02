#ifndef LORA_IOT_LED_H
#define LORA_IOT_LED_H

#include <Arduino.h>
#include "esp32-hal-gpio.h"

#define GPIO_LED 6

void led_init();

void led_red(bool up);

#endif // LORA_IOT_LED_H