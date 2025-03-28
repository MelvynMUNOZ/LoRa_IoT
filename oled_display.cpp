#include <WiFi.h>
#include "oled_display.h"
#include "sensor_tmg3993.h"

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
  oled_display.clear();
  oled_display.drawString(0, 0, str);
  oled_display.display();
}

void oled_display_print_proximity() {
  char str[32];
  snprintf(str, sizeof(str), "Proximity: %u", tmg3993_data.prox);
  oled_display.drawString(0, 12, str);
}

void oled_display_print_light() {
  char str[32];
  snprintf(str, sizeof(str), "LUX: %d    CCT: %d", tmg3993_data.lux, tmg3993_data.cct);
  oled_display.drawString(0, 24, str);
}