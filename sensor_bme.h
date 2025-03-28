#ifndef SENSOR_BME_H
#define SENSOR_BME_H

#include "Adafruit_BME680.h"
#include <Adafruit_Sensor.h>
#include <SPI.h>

#define BME_SCK 35
#define BME_MOSI 34 //SDA
#define BME_MISO 37 //SDO
#define BME_CS 33

#define SEALEVELPRESSURE_HPA (1013.25)

bool Sensor_BME_init();

float Sensor_BME_get_temperature();
float Sensor_BME_get_pressure();
float Sensor_BME_get_humidity();
float Sensor_BME_get_gas();
float Sensor_BME_get_altitude();

#endif //SENSOR_BME_H