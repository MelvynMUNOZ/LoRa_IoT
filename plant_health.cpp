#include "plant_health.h"
#include "oled_display.h"

bool plant_health_sensors_init()
{
  bool bme_ready = sensor_bme680_init();
  bool tmg3993_ready = sensor_tmg3993_init();
  //Sensor_HB_init();

  if (bme_ready == false || tmg3993_ready == false) {
    Serial.println("Failed to initialize devices. Waiting...");
    return false;
  }

  return true;
}

char* plant_health_indicator()
{


}

void plant_health_monitor()
{
  // sensor_bme680_get_temperature();
  // sensor_bme680_get_pressure();
  // sensor_bme680_get_humidity();
  // sensor_bme680_get_air_quality();
  // sensor_bme680_get_altitude();
  
  sensor_bme680_get_all_data();
  sensor_tmg3993_get_light();
  sensor_tmg3993_get_proximity();

  oled_display.clear();
  oled_display_print_web_server_address();
  oled_display_print_light(1);
  oled_display_print_temperature_humidity(2);
  oled_display_print_pressure(3);
  oled_display_print_air_quality(4);
  oled_display.display();

  //plant_health_indicator();

  //Recupere en boucle les bpm (ne les affiches que si il a plusieurs battements à la suite)
  // Sensor_HB_get_value();
}