#include "sensor_bme680.h"

Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
data_bme680_t bme680_data;

bool sensor_bme680_init()
{
  if (!bme.begin()) {
    Serial.println("[BME680] Device not found. Check wiring.");
    return false;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  
  Serial.println("[BME680] Device configured.");
  return true;
}

void sensor_bme680_get_all_data(){
  if (!bme.performReading()) {
    Serial.println("[BME680] Failed to read data");
  }
  else {
    bme680_data.temperature = bme.temperature;                     //°C
    bme680_data.pressure = bme.pressure / 100.0;                   //ATTENTION hPa
    bme680_data.humidity = bme.humidity;                           //%
    bme680_data.air_quality = bme.gas_resistance  / 1000.0;        //ATTENTION : KOhms
    bme680_data.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); //m
  }
}