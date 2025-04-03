#include "oled_display.h"
#include "web_server.h"
#include "plant_health.h"

void setup()
{
  Serial.begin(115200);

  led_init();
  oled_display_init();
  if (web_server_init()) {
    web_server_start();
  }

  if (plant_health_sensors_init() == false) {
    oled_display.clear();
    oled_display_print_error();
    oled_display.display();
    for (;;);
  }
}

void loop()
{
  web_server_get_timestamp();
  plant_health_monitor();
}
