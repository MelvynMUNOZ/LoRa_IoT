#include "oled_display.h"
#include "sensor_tmg3993.h"
#include "sensor_bme.h"
#include "sensor_hb.h"

unsigned long previousTempMillis = 0;
const long tempInterval = 5000; // Intervalle de récupération de température (5s)

void setup() {
  Serial.begin(115200);

  oled_display_init();
  Sensor_HB_init();

  bool bme_ready = Sensor_BME_init();
  bool tmg3993_ready = sensor_tmg3993_init();

  if (bme_ready == false || tmg3993_ready == false) {
    Serial.println("Failed to initialize devices. Waiting...");
    for (;;);
  }
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


  sensor_tmg3993_poll_light_color();
  sensor_tmg3993_poll_proximity();

  oled_display.clear();
  oled_display.drawString(0, 0, "Hello LoRa32 V3 !");
  oled_display_print_proximity();
  oled_display_print_light();
  oled_display.display();

}
