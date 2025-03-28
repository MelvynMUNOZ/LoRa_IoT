#include <WiFi.h>
#include "oled_display.h"
#include "sensor_tmg3993.h"
#include "sensor_hb.h"
#include "sensor_bme.h"

SSD1306Wire oled_display(OLED_ADDR, OLED_FREQ, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

void oled_display_init() {
  Wire.begin(SDA_OLED, SCL_OLED); // I2C Bus 0 for OLED display

  if (oled_display.init() == false) {
    Serial.println("[OLED] Failed to initialize oled display.");
  }
  oled_display.setFont(ArialMT_Plain_10);

  Serial.println("[OLED] Device configured.");
}

void oled_display_print_web_server_address() {
  char str[32];
  snprintf(str, sizeof(str), "Web server: %s", WiFi.localIP().toString());
  oled_display.drawString(0, 0, str);
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
  snprintf(str, sizeof(str), "T: %.1f°C  H: %.1f %%", BME_data.temperature, BME_data.humidity);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_pressure(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Pressure: %.1f hPa", BME_data.pressure);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_air_quality(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Air: %.1f KOhms", BME_data.air_quality);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_altitude(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Altitude: %.1f m", BME_data.altitude);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_hb(uint8_t line_number) {
  char str[32];
  snprintf(str, sizeof(str), "Heartbeat: %.0f bpm", HB_data.bpm);
  oled_display.drawString(0, line_number*12, str);
}