#include "oled_display.h"
#include "sensor_tmg3993.h"
#include "sensor_hb.h"
#include "sensor_bme.h"

SSD1306Wire oled_display(OLED_ADDR, OLED_FREQ, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

bool oled_display_init() {
  Wire.begin(SDA_OLED, SCL_OLED); // I2C Bus 0 for OLED display

  if (oled_display.init() == false) {
    Serial.println("[OLED] Failed to initialize oled display.");
    return false;
  }

  oled_display.setFont(ArialMT_Plain_10);

  Serial.println("[OLED] Device configured.");
  return true;
}

void oled_display_print_proximity(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Proximity: %u", tmg3993_data.prox);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_light(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "LUX: %d    CCT: %d", tmg3993_data.lux, tmg3993_data.cct);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_temperature_humidity(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "T: %.1f°C  H: %.1f %%", Sensor_BME_get_temperature(), Sensor_BME_get_humidity());
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_pressure(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Pressure: %.1f hPa", Sensor_BME_get_pressure());
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_gas_resistance(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Gas: %.1f KOhms", Sensor_BME_get_gas());
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_altitude(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Altitude: %.1f m", Sensor_BME_get_altitude());
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_hb(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Heartbeat: %.0f bpm", HB_data.print_value);
  oled_display.drawString(0, line_number*12, str);
}