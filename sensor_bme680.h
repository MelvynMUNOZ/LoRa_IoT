#ifndef LORA_IOT_SENSOR_BME680_H
#define LORA_IOT_SENSOR_BME680_H

#include <Adafruit_BME680.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>

#define BME_SCK 35
#define BME_MOSI 34 //SDA
#define BME_MISO 37 //SDO
#define BME_CS 33

#define SEALEVELPRESSURE_HPA (1013.25)

struct data_bme680_t {
  float temperature;
  float pressure;
  float humidity;
  float air_quality;
  float altitude;
};

extern data_bme680_t bme680_data;

bool sensor_bme680_init();

void sensor_bme680_get_temperature();
void sensor_bme680_get_pressure();
void sensor_bme680_get_humidity();
void sensor_bme680_get_air_quality();
void sensor_bme680_get_altitude();

#endif // LORA_IOT_SENSOR_BME680_H