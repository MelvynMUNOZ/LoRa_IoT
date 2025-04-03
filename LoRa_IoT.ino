#include "esp_sleep.h"
#include "oled_display.h"
#include "web_server.h"
#include "plant_health.h"

#define US_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 5          /* Time ESP32 will go to sleep (in seconds) */

bool sensors_ready = false;

void setup()
{
  Serial.begin(115200);

  // Check deepsleep wakeup
  // if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
  //   Serial.println("Réveil après Deep Sleep");
  // }
  // else {
  //   Serial.println("Démarrage initial");
  // }

  // Init modules and sensors
  led_init();
  oled_display_init();
  if (web_server_init()) {
    web_server_start();
  }
  sensors_ready = plant_health_sensors_init();
  if (sensors_ready == false) {
    oled_display.clear();
    oled_display_print_error();
    oled_display.display();
  }

  // Configure deepsleep timer
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * US_TO_S_FACTOR);
}

void loop()
{
  if (sensors_ready) {
    web_server_get_timestamp();
    plant_health_monitor();
  }
  delay(2000);

  // Start deepsleep
  // Serial.println("Going to sleep now");
  // esp_deep_sleep_start();
}
