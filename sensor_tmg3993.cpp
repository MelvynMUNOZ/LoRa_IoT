#include "sensor_tmg3993.h"

TwoWire wire1 = TwoWire(1);
TMG3993 tmg3993(wire1);
data_tmg3993_t tmg3993_data;

bool sensor_tmg3993_init()
{
  wire1.begin(I2C_SDA, I2C_SCL); // I2C Bus 1 for I2C devices, especially TMG3993
  wire1.setClock(500000);

  if (tmg3993.initialize() == false) {
    Serial.println("[TMG3993] Device not found. Check I2C wiring.");
    return false;
  }

  tmg3993.setADCIntegrationTime(0xdb);
  tmg3993.setupRecommendedConfigForProximity();
  // tmg3993.setProximityPulseCntLen(16, 1);
  tmg3993.enableEngines(ENABLE_PON | ENABLE_PEN | ENABLE_PIEN | ENABLE_AEN | ENABLE_AIEN);

  Serial.println("[TMG3993] Device configured.");
  return true;
}

void sensor_tmg3993_get_light()
{
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

void sensor_tmg3993_get_proximity()
{
  if (tmg3993.getSTATUS() & STATUS_PVALID) {
    // Get proximity
    tmg3993_data.prox = tmg3993.getProximityRaw();
  }
}
