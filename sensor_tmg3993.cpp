#include <Wire.h>
#include "Seeed_TMG3993.h"
#include "sensor_tmg3993.h"

TMG3993 tmg3993;
data_tmg3993_t tmg3993_data;

bool sensor_tmg3993_init() {
  Wire.begin(I2C_SDA, I2C_SCL);
    
  if (tmg3993.initialize() == false) {
    Serial.println("[TMG3993] Device not found. Check I2C wiring.");
    return false;
  }

  tmg3993.setADCIntegrationTime(0xdb);
  tmg3993.setupRecommendedConfigForProximity();
  tmg3993.enableEngines(ENABLE_PON | ENABLE_PEN | ENABLE_PIEN | ENABLE_AEN | ENABLE_AIEN);

  Serial.println("[TMG3993] Device configured !");
  
  return true;
}

void sensor_tmg3993_poll_light_color() {
  if (tmg3993.getSTATUS() & STATUS_AVALID) {
    // Get RGB and Clear
    tmg3993.getRGBCRaw(&tmg3993_data.r, &tmg3993_data.g, &tmg3993_data.b, &tmg3993_data.c);

    // Get Luminosty
    tmg3993_data.lux = tmg3993.getLux(tmg3993_data.r, tmg3993_data.g, tmg3993_data.b, tmg3993_data.c);

    // Get Color Temperature
    tmg3993_data.cct = tmg3993.getCCT(tmg3993_data.r, tmg3993_data.g, tmg3993_data.b, tmg3993_data.c);

    // Clear interruption bits
    tmg3993.clearALSInterrupts();
  }
}

void sensor_tmg3993_poll_proximity() {
  if (tmg3993.getSTATUS() & STATUS_PVALID) {
    // Get proximity
    tmg3993_data.prox = tmg3993.getProximityRaw();
  }
}

void sensor_tmg3993_print_light_color() {
  Serial.print("RGBC: ");
  Serial.print(tmg3993_data.r);
  Serial.print("\t");
  Serial.print(tmg3993_data.g);
  Serial.print("\t");
  Serial.print(tmg3993_data.b);
  Serial.print("\t");
  Serial.println(tmg3993_data.c);

  Serial.print("LUX: ");
  Serial.print(tmg3993_data.lux);
  Serial.print("\tCCT: ");
  Serial.println(tmg3993_data.cct);
  Serial.println("----");
}

void sensor_tmg3993_print_proximity() {
  
}
