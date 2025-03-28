#include "oled_display.h"
#include "sensor_tmg3993.h"

void setup() {
  Serial.begin(115200);

  oled_display_init();
  bool tmg3993_ready = sensor_tmg3993_init();

  if (tmg3993_ready == false) {
    Serial.println("Failed to initialize devices. Waiting...");
    for (;;);
  }
}

void loop() {
  sensor_tmg3993_poll_light_color();
  sensor_tmg3993_poll_proximity();

  oled_display.clear();
  oled_display.drawString(0, 0, "Hello LoRa32 V3 !");
  oled_display_print_proximity();
  oled_display_print_light();
  oled_display.display();

  delay(200);
}
