#include "sensor_tmg3993.h"

void setup() {
  Serial.begin(9600);

  bool tmg3993_ready = sensor_tmg3993_init();

  if (!tmg3993_ready) {
    Serial.println("Sensors initialization failed.");
    for (;;);
  }
}

void loop() {
  sensor_tmg3993_poll_light_color();
  sensor_tmg3993_poll_proximity();

  sensor_tmg3993_print_light_color();
  sensor_tmg3993_print_proximity();
}
