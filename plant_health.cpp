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

/**
 * Calibrate the health indicator.
 */
// void plant_health_indicator(int indic_type)
// {
//   int indicator = 0;
//   float weight = 0;
//   int min = 0;
//   int max = 0;
  
//   switch (indic_type)
//   {
//     case HUM_DATA:
//       indicator = indicators.humidity;
//       weight = HUM_WEIGHT;
//       min = HUM_MIN;
//       max = HUM_MAX;
//       break;

//     case TEMP_DATA:
//       indicator = indicators.temperature;
//       weight = TEMP_WEIGHT;
//       min = TEMP_MIN;
//       max = TEMP_MAX;
//       break;

//     case AIR_DATA:
//       indicator = indicators.air_quality;
//       weight = AIR_WEIGHT;
//       min = AIR_GOOD;
//       max = AIR_VERY_GOOD;
//       break;

//     case LUM_DATA:
//       indicator = indicators.luminosity;
//       weight = LUM_WEIGHT;
//       min = LUM_MIN;
//       max = LUM_MAX;
//       break;

//     default:
//       break;
//   }

//   /* Calculates contribution based on range and weight */
//   if (indicator < min) {
//     /* Below the optimum range, interpolation between 0 and min */
//     indicators.health += (int)(weight * (indicator / (float)min) * INDIC_1);
//   }
//   else if (indicator >= min && indicator <= max) {
//     /* In the optimum range, interpolation between min and max */
//     indicators.health += (int)(weight * (INDIC_2 + ((indicator - min) / (float)(max - min)) * (INDIC_3 - INDIC_2)));
//   }
//   else if (indicator > max && indicator <= INDIC_MAX) {
//     /* Above the optimum range, interpolation between max et INDIC_MAX */
//     indicators.health += (int)(weight * (INDIC_3 + ((INDIC_MAX - indicator) / (float)(INDIC_MAX - max)) * (INDIC_MAX - INDIC_3)));
//   } else {
//     /* Value out of the range, higher penalty */
//     indicators.health -= (int)(weight * (indicator - INDIC_MAX));
//   }
// }

void plant_health_global_health_indicator()
{  
  indicators.health = 0;

  //get pourcentage value
  plant_health_humidity_indicator();
  plant_health_air_quality_indicator();
  plant_health_luminosity_indicator();
  indicators.temperature = bme680_data.temperature;

  //calcul for the general health
  // plant_health_indicator(HUM_DATA);
  // Serial.print("1 : health : ");
  // Serial.println(indicators.health);

  // plant_health_indicator(TEMP_DATA);
  // Serial.print("2 : health : ");
  // Serial.println(indicators.health);

  // plant_health_indicator(AIR_DATA);
  // Serial.print("3 : health : ");
  // Serial.println(indicators.health);

  // plant_health_indicator(LUM_DATA);
  // Serial.print("4 : health : ");
  // Serial.println(indicators.health);

  // Moyenne pondérée des indicateurs
  indicators.health = (int)(
      (indicators.humidity * HUM_WEIGHT) +
      (indicators.temperature * TEMP_WEIGHT) +
      (indicators.air_quality * AIR_WEIGHT) +
      (indicators.luminosity * LUM_WEIGHT)
  );
  
  if (indicators.health < INDIC_MIN)
  {
    indicators.health = INDIC_MIN;
  }
  else if (indicators.health > INDIC_MAX)
  {
    indicators.health = INDIC_MAX;
  }
}

void plant_health_set_state()
{

  plant_health_global_health_indicator();

  if (indicators.health >= INDIC_MIN && indicators.health < INDIC_1)
  {
    indicators.health_state = "BAD";
    led_red(true);
  }
  else if (indicators.health >= INDIC_1 && indicators.health < INDIC_2)
  {
    indicators.health_state = "NORMAL";
    led_yellow(true);
  }
  else if (indicators.health >= INDIC_2 && indicators.health < INDIC_3)
  {
    indicators.health_state = "GOOD";
    led_green(true);
  }
  else if (indicators.health >= INDIC_3 && indicators.health <= INDIC_MAX)
  {
    indicators.health_state = "VERY GOOD";
    led_green(true);
  }
  else
  {
    indicators.health_state = "ERROR";
    led_red(true);
    led_yellow(true);
    led_green(true);
  }
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

    plant_health_set_state();
    Serial.println(indicators.health_state);


  //Recupere en boucle les bpm (ne les affiches que si il a plusieurs battements à la suite)
  // Sensor_HB_get_value();
}