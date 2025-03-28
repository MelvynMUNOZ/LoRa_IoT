//This sensor gets temperature, pressure, humidity, gaz, altitude. 

#include "sensor_bme.h"

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

float Sensor_BME_get_temperature(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : temperature");
    return 0;
  } else {
    float temperature = bme.temperature;
    // Serial.print("Température: ");
    // Serial.print(temperature);
    // Serial.println(" °C");
    return temperature;
  }
}

float Sensor_BME_get_pressure(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : pressure");
    return 0;
  } else {
    float pressure = bme.pressure / 100.0; //ATTENTION hPa
    // Serial.print("Pressure = ");
    // Serial.print(pressure);
    // Serial.println(" hPa");
    return pressure;
  }
}

float Sensor_BME_get_humidity(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : humidity");
    return 0;
  } else {
    float humidity = bme.humidity; //%
    // Serial.print("Humidity = ");
    // Serial.print(humidity);
    // Serial.println(" %");
    return humidity;
  }
}

float Sensor_BME_get_gas(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : gaz");
    return 0;
  } else {
    float gas_resistance = bme.gas_resistance  / 1000.0; //ATTENTION : KOhms
    // Serial.print("Gas = ");
    // Serial.print(gas_resistance);
    // Serial.println(" KOhms");
    return gas_resistance;
  }
}

float Sensor_BME_get_altitude(){
  if (!bme.performReading()) {
    Serial.println("Erreur lecture BME680 : altitude");
    return 0;
  } else {
    float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); //m
    // Serial.print("Approx. Altitude = ");
    // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    // Serial.println(" m");
    return altitude;
  }
}
