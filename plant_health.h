#ifndef LORA_IOT_PLANT_HEALTH_H
#define LORA_IOT_PLANT_HEALTH_H

#include "sensor_tmg3993.h"
#include "sensor_bme680.h"
//#include "sensor_hb.h"
#include "led.h"

bool plant_health_sensors_init();
void plant_health_monitor();

#endif // LORA_IOT_PLANT_HEALTH_H