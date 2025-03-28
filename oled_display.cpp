#include "oled_display.h"
#include "sensor_tmg3993.h"

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

void oled_display_print_proximity() {
  char str[32];
  snprintf(str, 64, "Proximity: %u", tmg3993_data.prox);
  oled_display.drawString(0, 12, str);
}

void oled_display_print_light() {
  char str[32];
  snprintf(str, 64, "LUX: %d    CCT: %d", tmg3993_data.lux, tmg3993_data.cct);
  oled_display.drawString(0, 24, str);
}