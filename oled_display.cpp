#include <WiFi.h>
#include "oled_display.h"
#include "sensor_tmg3993.h"
#include "sensor_bme680.h"
#include "sensor_hb.h"

SSD1306Wire oled_display(OLED_ADDR, OLED_FREQ, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

void oled_display_init()
{
  Wire.begin(SDA_OLED, SCL_OLED); // I2C Bus 0 for OLED display

  if (oled_display.init() == false) {
    Serial.println("[OLED] Failed to initialize oled display.");
  }
  oled_display.setFont(ArialMT_Plain_10);

  Serial.println("[OLED] Device configured.");
}

void oled_display_print_error()
{
  oled_display.setTextAlignment(TEXT_ALIGN_CENTER);
  int x = oled_display.width()/2;
  int y = oled_display.height()/2 - 12;
  oled_display.drawString(x, y, "ERROR");
  oled_display.drawString(x, y + 12, "Check wiring, reboot");
}

void oled_display_print_web_server_address()
{
  char str[30];
  if (WiFi.status() == WL_CONNECTED) {
    snprintf(str, sizeof(str), "Server: %s", WiFi.localIP().toString());
  }
  else {
    Serial.println("[WEB_SERVER] Connection lost.");
    snprintf(str, sizeof(str), "Server: Not connected");
  }
  oled_display.drawString(0, 0, str);
}

void oled_display_print_proximity(uint8_t line_number)
{
  char str[30];
  snprintf(str, sizeof(str), "Proximity: %u", tmg3993_data.prox);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_light(uint8_t line_number)
{
  char str[30];
  snprintf(str, sizeof(str), "Luminosity: %d lm", tmg3993_data.lux);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_temperature_humidity(uint8_t line_number)
{
  char str[30];
  snprintf(str, sizeof(str), "T: %.1f°C  H: %.1f%%", bme680_data.temperature, bme680_data.humidity);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_pressure(uint8_t line_number)
{
  char str[30];
  snprintf(str, sizeof(str), "Pressure: %.1f hPa", bme680_data.pressure);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_air_quality(uint8_t line_number)
{
  char str[30];
  snprintf(str, sizeof(str), "Air Quality: %.1f KOhms", bme680_data.air_quality);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_altitude(uint8_t line_number)
{
  char str[30];
  snprintf(str, sizeof(str), "Altitude: %.1f m", bme680_data.altitude);
  oled_display.drawString(0, line_number*12, str);
}

void oled_display_print_hb(uint8_t line_number)
{
  char str[30];
  snprintf(str, sizeof(str), "Heartbeat: %.0f bpm", HB_data.bpm);
  oled_display.drawString(0, line_number*12, str);
}