#ifndef LORA_IOT_PLANT_HEALTH_H
#define LORA_IOT_PLANT_HEALTH_H

#include "sensor_tmg3993.h"
#include "sensor_bme680.h"
//#include "sensor_hb.h"
#include "led.h"

#define HUM_MIN 30.0
#define HUM_MAX 60.0
#define HUM_WEIGHT 0.3

#define TEMP_WEIGHT 0.25

#define AIR_GOOD 100.0
#define AIR_VERY_GOOD 300.0
#define AIR_WEIGHT 0.2

#define LUM_MIN 60
#define LUM_MAX 1500
#define LUM_WEIGHT 0.25

/* Plant health global indicator bounds values. */
#define INDIC_MIN 0 // BAD >
#define INDIC_1   30 // NORMAL >
#define INDIC_2   50 // GOOD >
#define INDIC_3   70 // VERY GOOD
#define INDIC_MAX 100

enum indic_type {
  LUM_DATA,
  TEMP_DATA,
  HUM_DATA,
  AIR_DATA
};

struct indic_t {
  int health;
  char *health_state;
  int humidity;
  int temperature;
  int air_quality;
  int luminosity;
};

extern indic_t indicators;

bool plant_health_sensors_init();
void plant_health_humidity_indicator();
void plant_health_air_quality_indicator();
void plant_health_luminosity_indicator();
void plant_health_global_health_indicator();
void plant_health_monitor();

#endif // LORA_IOT_PLANT_HEALTH_H