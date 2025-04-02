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

void sensor_bme680_get_temperature()
{
  if (!bme.performReading()) {
    Serial.println("[BME680] Failed to read temperature");
  }
  else {
    bme680_data.temperature = bme.temperature;
    // Serial.print("Température: ");
    // Serial.print(temperature);
    // Serial.println(" °C");
  }
}

void sensor_bme680_get_pressure()
{
  if (!bme.performReading()) {
    Serial.println("[BME680] Failed to read pressure");
  }
  else {
    bme680_data.pressure = bme.pressure / 100.0; //ATTENTION hPa
    // Serial.print("Pressure = ");
    // Serial.print(pressure);
    // Serial.println(" hPa");
  }
}

void sensor_bme680_get_humidity()
{
  if (!bme.performReading()) {
    Serial.println("[BME680] Failed to read humidity");
  }
  else {
    bme680_data.humidity = bme.humidity; //%
    // Serial.print("Humidity = ");
    // Serial.print(humidity);
    // Serial.println(" %");
  }
}

void sensor_bme680_get_air_quality()
{
  if (!bme.performReading()) {
    Serial.println("[BME680] Failed to read air quality");
  }
  else {
    bme680_data.air_quality = bme.gas_resistance  / 1000.0; //ATTENTION : KOhms
    // Serial.print("Gas = ");
    // Serial.print(gas_resistance);
    // Serial.println(" KOhms");
  }
}

void sensor_bme680_get_altitude()
{
  if (!bme.performReading()) {
    Serial.println("[BME680] Failed to read altitude");
  }
  else {
    bme680_data.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); //m
    // Serial.print("Approx. Altitude = ");
    // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    // Serial.println(" m");
  }
}
