#ifndef LORA_IOT_PLANT_HEALTH_H
#define LORA_IOT_PLANT_HEALTH_H

#include "sensor_tmg3993.h"
#include "sensor_bme680.h"
//#include "sensor_hb.h"
#include "led.h"

#define LUM_MIN 60
#define LUM_MAX 1000
#define LUM_INDIC 0.3

#define TEMP_MIN 17.0
#define TEMP_MAX 29.0
#define TEMP_INDIC 0.3

#define HUM_MIN 30.0
#define HUM_MAX 70.0

#define AIR_GOOD 100.0
#define AIR_VERY_GOOD 500.0

struct data_pourcent{
  int lum_pourcent;
  int temp;

};

bool plant_health_sensors_init();
void plant_health_monitor();

#endif // LORA_IOT_PLANT_HEALTH_H