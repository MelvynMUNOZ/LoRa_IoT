//This sensor gets temperature, pressure, humidity, gaz, altitude. 

#include "sensor_bme.h"

Sensor_BME_data BME_data;

Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

bool Sensor_BME_init(){
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    return false;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  
  return true;
}

void Sensor_BME_get_temperature(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : temperature");
  } else {
    BME_data.temperature = bme.temperature;
    // Serial.print("Température: ");
    // Serial.print(temperature);
    // Serial.println(" °C");
  }
}

void Sensor_BME_get_pressure(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : pressure");
  } else {
    BME_data.pressure = bme.pressure / 100.0; //ATTENTION hPa
    // Serial.print("Pressure = ");
    // Serial.print(pressure);
    // Serial.println(" hPa");
  }
}

void Sensor_BME_get_humidity(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : humidity");
  } else {
    BME_data.humidity = bme.humidity; //%
    // Serial.print("Humidity = ");
    // Serial.print(humidity);
    // Serial.println(" %");
  }
}

void Sensor_BME_get_air_quality(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : gaz");
  } else {
    BME_data.air_quality = bme.gas_resistance  / 1000.0; //ATTENTION : KOhms
    // Serial.print("Gas = ");
    // Serial.print(gas_resistance);
    // Serial.println(" KOhms");
  }
}

void Sensor_BME_get_altitude(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : altitude");
  } else {
    BME_data.altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); //m
    // Serial.print("Approx. Altitude = ");
    // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    // Serial.println(" m");
  }
}
