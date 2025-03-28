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

struct Sensor_BME_data{
  float temperature;
  float pressure;
  float humidity;
  float gas;
  float altitude;
};

extern Sensor_BME_data BME_data;

bool Sensor_BME_init();

void Sensor_BME_get_temperature();
void Sensor_BME_get_pressure();
void Sensor_BME_get_humidity();
void Sensor_BME_get_gas();
void Sensor_BME_get_altitude();

#endif //SENSOR_BME_H