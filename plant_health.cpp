#include "plant_health.h"
#include "oled_display.h"

indic_t indicators;

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

void plant_health_humidity_indicator()
{    
  if (bme680_data.humidity <= HUM_MIN) {
    indicators.humidity = INDIC_MIN;
  }
  else if (bme680_data.humidity >= HUM_MAX) {
    indicators.humidity = INDIC_MAX;
  } 
  
  indicators.humidity = (int)((bme680_data.humidity / HUM_MAX) * 100);
}

void plant_health_air_quality_indicator()
{    
  if (bme680_data.air_quality <= AIR_GOOD) {
    indicators.air_quality = INDIC_MIN;
  }
  else if (bme680_data.air_quality >= AIR_VERY_GOOD) {
    indicators.air_quality = INDIC_MAX;
  } 
  
  indicators.air_quality = (int)((bme680_data.air_quality / AIR_VERY_GOOD) * 100);
}

void plant_health_luminosity_indicator()
{    
  if (tmg3993_data.lux <= LUM_MIN) {
    indicators.luminosity = INDIC_MIN;
  }
  else if (tmg3993_data.lux >= LUM_MAX) {
    indicators.luminosity = INDIC_MAX;
  } 
  
  indicators.luminosity = (int)((tmg3993_data.lux / LUM_MAX) * 100);
}

void plant_health_global_health_indicator()
{  
  indicators.health = 0;

  // Indicateurs en %
  plant_health_humidity_indicator();
  plant_health_air_quality_indicator();
  plant_health_luminosity_indicator();
  indicators.temperature = bme680_data.temperature;

  // Moyenne pondérée des indicateurs
  indicators.health = (int)(
      (indicators.humidity * HUM_WEIGHT) +
      (indicators.temperature * TEMP_WEIGHT) +
      (indicators.air_quality * AIR_WEIGHT) +
      (indicators.luminosity * LUM_WEIGHT)
  );
  
  if (indicators.health < INDIC_MIN) {
    indicators.health = INDIC_MIN;
  }
  else if (indicators.health > INDIC_MAX)  {
    indicators.health = INDIC_MAX;
  }
}

void plant_health_set_state()
{
  plant_health_global_health_indicator();

  if (indicators.health >= INDIC_MIN && indicators.health < INDIC_1) {
    indicators.health_state = "BAD";
    led_red(true);
  }
  else if (indicators.health >= INDIC_1 && indicators.health < INDIC_2) {
    indicators.health_state = "NORMAL";
    led_yellow(true);
  }
  else if (indicators.health >= INDIC_2 && indicators.health < INDIC_3) {
    indicators.health_state = "GOOD";
    led_green(true);
  }
  else if (indicators.health >= INDIC_3 && indicators.health <= INDIC_MAX) {
    indicators.health_state = "VERY GOOD";
    led_green(true);
  }
  else {
    indicators.health_state = "ERROR";
    led_red(true);
    led_yellow(true);
    led_green(true);
  }
}


void plant_health_monitor()
{
  // Get sensors data
  sensor_bme680_get_all_data();
  sensor_tmg3993_get_light();
  sensor_tmg3993_get_proximity();

  // Display data on OLED display
  oled_display.clear();
  oled_display_print_web_server_address();
  oled_display_print_light(1);
  oled_display_print_temperature_humidity(2);
  oled_display_print_pressure(3);
  oled_display_print_air_quality(4);
  oled_display.display();

  // Compute plant global health indicator
  plant_health_set_state();
  Serial.println(indicators.health_state);

  //Recupere en boucle les bpm (ne les affiches que si il a plusieurs battements à la suite)
  // Sensor_HB_get_value();
}