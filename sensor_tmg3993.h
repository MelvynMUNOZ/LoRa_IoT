#ifndef LORA_IOT_SENSOR_TMG3993_H
#define LORA_IOT_SENSOR_TMG3993_H

#include <cstdint>
#include <Arduino.h>
#include <Wire.h>
#include "Seeed_TMG3993.h"

#define I2C_SDA 41
#define I2C_SCL 42

struct data_tmg3993_t {
  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t c;
  int32_t lux;
  int32_t cct;
  uint8_t prox;
};

extern TMG3993 tmg3993;
extern data_tmg3993_t tmg3993_data;

bool sensor_tmg3993_init();
void sensor_tmg3993_poll_light_color();
void sensor_tmg3993_poll_proximity();
void sensor_tmg3993_print_light_color();
void sensor_tmg3993_print_proximity();

#endif // LORA_IOT_SENSOR_TMG3993_H