#include "oled_display.h"
#include "sensor_tmg3993.h"
#include "sensor_bme.h"
#include "sensor_hb.h"
#include "led.h"

unsigned long previousTempMillis = 0;
const long tempInterval = 1000; // Intervalle de récupération des capteurs (en millisecondes)

void setup() {
  Serial.begin(115200);

  led_init();
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

  // Lire les capteurs toutes les 1s
  if (currentMillis - previousTempMillis >= tempInterval) {
    previousTempMillis = currentMillis;
    float temp = Sensor_BME_get_temperature();
    float pressure = Sensor_BME_get_pressure();
    float humidity = Sensor_BME_get_humidity();
    uint32_t gas = Sensor_BME_get_gas();
    float altitude = Sensor_BME_get_altitude();

    sensor_tmg3993_poll_light_color();
    sensor_tmg3993_poll_proximity();

    oled_display.clear();
    oled_display.drawString(0, 0, "Holà amigo !");
    oled_display_print_light(1);
    oled_display_print_temperature_humidity(2);
    oled_display_print_pressure(3);
    oled_display_print_gas_resistance(4);
    oled_display.display();

  }

  //Recupere en boucle les bpm (ne les affiches que si il a plusieurs battements à la suite)
  Sensor_HB_get_value();

}
