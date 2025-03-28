#include "sensor_bme.h"
#include "sensor_hb.h"

#define I2C_SDA 41
#define I2C_SCL 42 

unsigned long previousTempMillis = 0;
const long tempInterval = 5000; // Intervalle de récupération de température (5s)

void setup() {
  Serial.begin(115200);
  while (!Serial);

  //Initialise les variables pour la recuperations de : température, pression, humidité, gaz et altitude
  Sensor_BME_init();

  //Initialise les variables pour la recuperations des bpm
  Sensor_HB_init();
}

void loop() {
  
  unsigned long currentMillis = millis();

  // Lire la température toutes les 500ms
  if (currentMillis - previousTempMillis >= tempInterval) {
    previousTempMillis = currentMillis;
    float temp = Sensor_BME_get_temperature();
    float pressure = Sensor_BME_get_pressure();
    float humidity = Sensor_BME_get_humidity();
    uint32_t gas = Sensor_BME_get_gas();
    float altitude = Sensor_BME_get_altitude();

  }

  //Recupere en boucle les bpm (ne les affiches que si il a 3 battements à la suite)
  Sensor_HB_get_value();

}