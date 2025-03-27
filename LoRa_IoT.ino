#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define BME_SCK 35
#define BME_MOSI 34 //SDA
#define BME_MISO 37 //SDO
#define BME_CS 33

#define I2C_SDA 41
#define I2C_SCL 42

#define samp_siz 3 
#define rise_threshold 3 

#define SEALEVELPRESSURE_HPA (1013.25)

int sensorPin = 7; 

struct {
  float reads[samp_siz];
  float sum; 
	long int ptr; 
	float first;
  float second;
  float third;
  float before;
  float print_value;
	bool rising; 
	int rise_count; 
	long int last_beat;
} Sensor_HB_Data;

unsigned long previousTempMillis = 0;
const long tempInterval = 5000; // Intervalle de récupération de température (5s)

Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  //Initialise les variables pour la recuperations des bpm
  Sensor_HB_init();
}

void loop() {

  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  
  unsigned long currentMillis = millis();

  // Lire la température toutes les 500ms
  if (currentMillis - previousTempMillis >= tempInterval) {
    previousTempMillis = currentMillis;

    if (!bme.performReading()) {
      Serial.println("Erreur lecture BME680");
    } else {
      Serial.print("Température: ");
      Serial.print(bme.temperature);
      Serial.println(" °C");
    }
  }

  //Recupere en boucle les bpm (ne les affiches que si il a 3 battements à la suite)
  Sensor_HB_get_value();

  
  // Serial.print("Temperature = ");
  // Serial.print(bme.temperature);
  // Serial.println(" *C");

  // Serial.print("Pressure = ");
  // Serial.print(bme.pressure / 100.0);
  // Serial.println(" hPa");

  // Serial.print("Humidity = ");
  // Serial.print(bme.humidity);
  // Serial.println(" %");

  // Serial.print("Gas = ");
  // Serial.print(bme.gas_resistance / 1000.0);
  // Serial.println(" KOhms");

  // Serial.print("Approx. Altitude = ");
  // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  // Serial.println(" m");
}

void Sensor_HB_init(){
  for (int i = 0; i < samp_siz; i++) 
	  Sensor_HB_Data.reads[i] = 0; 
	Sensor_HB_Data.sum = 0; 
	Sensor_HB_Data.ptr = 0;
}

void Sensor_HB_get_value(){
	
  float last, reader, start; 
  long int now;
	int n; 
	 
  // calculate an average of the sensor 
  // during a 20 ms period (this will eliminate 
  // the 50 Hz noise caused by electric light 
  n = 0; 
  start = millis(); 
  reader = 0.; 
  do 
  { 
    reader += analogRead (sensorPin); 
    n++; 
    now = millis(); 
  } 
  while (now < start + 10);   
  reader /= n;  // we got an average 
  // Add the newest measurement to an array 
  // and subtract the oldest measurement from the array 
  // to maintain a sum of last measurements 
  Sensor_HB_Data.sum -= Sensor_HB_Data.reads[Sensor_HB_Data.ptr]; 
  Sensor_HB_Data.sum += reader; 
  Sensor_HB_Data.reads[Sensor_HB_Data.ptr] = reader; 
  last = Sensor_HB_Data.sum / samp_siz; 
  // now last holds the average of the values in the array 
  // check for a rising curve (= a heart beat) 
  if (last > Sensor_HB_Data.before) 
  { 
    Sensor_HB_Data.rise_count++; 
    if (!Sensor_HB_Data.rising && Sensor_HB_Data.rise_count > rise_threshold) 
    { 
      // Ok, we have detected a rising curve, which implies a heartbeat. 
      // Record the time since last beat, keep track of the two previous 
      // times (first, second, third) to get a weighed average. 
      // The rising flag prevents us from detecting the same rise  
      // more than once. 
      Sensor_HB_Data.rising = true; 
      Sensor_HB_Data.first = millis() - Sensor_HB_Data.last_beat; 
      Sensor_HB_Data.last_beat = millis(); 
      // Calculate the weighed average of heartbeat rate 
      // according to the three last beats 
      Sensor_HB_Data.print_value = 60000. / (0.4 * Sensor_HB_Data.first + 0.3 * Sensor_HB_Data.second + 0.3 * Sensor_HB_Data.third); 
      Serial.println(Sensor_HB_Data.print_value); 
      //Serial.print(''); 
      //*Sensor_HB_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third); 
      Sensor_HB_Data.third = Sensor_HB_Data.second; 
      Sensor_HB_Data.second = Sensor_HB_Data.first; 
    } 
  } 
  else 
  { 
    // Ok, the curve is falling 
    Sensor_HB_Data.rising = false; 
    Sensor_HB_Data.rise_count = 0; 
  } 
  Sensor_HB_Data.before = last; 
  Sensor_HB_Data.ptr++; 
  Sensor_HB_Data.ptr %= samp_siz; 
}