#include <Wire.h>               
#include "HT_SSD1306Wire.h"
#include "sensor_tmg3993.h"

#define OLED_ADDR 0x3C
#define OLED_FREQ 500000

SSD1306Wire oled_display(OLED_ADDR, OLED_FREQ, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); 

void setup() {
  Serial.begin(115200);

  oled_display_init();

  bool tmg3993_ready = sensor_tmg3993_init();

  if (!tmg3993_ready) {
    Serial.println("Sensors initialization failed.");
    // for (;;);
  }
}

void loop() {
  sensor_tmg3993_poll_light_color();
  sensor_tmg3993_poll_proximity();

  oled_display.clear();
  oled_display.drawString(0, 0, "Hello LoRa32 V3 !");
  oled_display_print_proximity();
  oled_display.display();

  delay(200);
}

void oled_display_init() {
  oled_display.init();
  oled_display.setFont(ArialMT_Plain_10);
  oled_display.connect();
}

void oled_display_print_proximity() {
  char str[32];
  snprintf(str, 64, "Proximity: %u", tmg3993_data.prox);
  oled_display.drawString(0, 12, str);

}
