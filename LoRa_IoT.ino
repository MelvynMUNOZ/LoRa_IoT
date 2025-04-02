#include "oled_display.h"
#include "web_server.h"
#include "sensor_tmg3993.h"
#include "sensor_bme680.h"
//#include "sensor_hb.h"
#include "led.h"

unsigned long previousTempMillis = 0;
const long tempInterval = 1000; // Intervalle de récupération des capteurs (en millisecondes)

void setup()
{
  Serial.begin(115200);

  led_init();
  oled_display_init();
  if (web_server_init()) {
    web_server_start();
  }

  bool bme_ready = sensor_bme680_init();
  bool tmg3993_ready = sensor_tmg3993_init();
  //Sensor_HB_init();

  if (bme_ready == false || tmg3993_ready == false) {
    Serial.println("Failed to initialize devices. Waiting...");
    oled_display.clear();
    oled_display_print_error();
    oled_display.display();
    for (;;);
  }
}

void loop()
{
  unsigned long currentMillis = millis();

  // Lire les capteurs toutes les 1s
  if (currentMillis - previousTempMillis >= tempInterval) {
    previousTempMillis = currentMillis;

    web_server_get_timestamp();

    sensor_bme680_get_temperature();
    sensor_bme680_get_pressure();
    sensor_bme680_get_humidity();
    sensor_bme680_get_gas();
    sensor_bme680_get_altitude();
    sensor_tmg3993_get_light();
    sensor_tmg3993_get_proximity();

    oled_display.clear();
    oled_display_print_web_server_address();
    oled_display_print_light(1);
    oled_display_print_temperature_humidity(2);
    oled_display_print_pressure(3);
    oled_display_print_gas_resistance(4);
    oled_display.display();
  }

  //Recupere en boucle les bpm (ne les affiches que si il a plusieurs battements à la suite)
  // Sensor_HB_get_value();
}
