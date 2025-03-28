//This sensor gets heartbeat. 

#include "sensor_hb.h"

int sensorPin = 7;

Sensor_HB_Data HB_data;

void Sensor_HB_init(){
  for (int i = 0; i < samp_siz; i++) 
	  HB_data.reads[i] = 0; 
	HB_data.sum = 0; 
	HB_data.ptr = 0;
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
  HB_data.sum -= HB_data.reads[HB_data.ptr]; 
  HB_data.sum += reader; 
  HB_data.reads[HB_data.ptr] = reader; 
  last = HB_data.sum / samp_siz; 
  // now last holds the average of the values in the array 
  // check for a rising curve (= a heart beat) 
  if (last > HB_data.before) 
  { 
    HB_data.rise_count++; 
    if (!HB_data.rising && HB_data.rise_count > rise_threshold) 
    { 
      // Ok, we have detected a rising curve, which implies a heartbeat. 
      // Record the time since last beat, keep track of the two previous 
      // times (first, second, third) to get a weighed average. 
      // The rising flag prevents us from detecting the same rise  
      // more than once. 
      HB_data.rising = true; 
      HB_data.first = millis() - HB_data.last_beat; 
      HB_data.last_beat = millis(); 
      // Calculate the weighed average of heartbeat rate 
      // according to the three last beats 
      HB_data.print_value = 60000. / (0.4 * HB_data.first + 0.3 * HB_data.second + 0.3 * HB_data.third); 
      Serial.println(HB_data.print_value); 
      //Serial.print(''); 
      //*Sensor_HB_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third); 
      HB_data.third = HB_data.second; 
      HB_data.second = HB_data.first; 
    } 
  } 
  else 
  { 
    // Ok, the curve is falling 
    HB_data.rising = false; 
    HB_data.rise_count = 0; 
  } 
  HB_data.before = last; 
  HB_data.ptr++; 
  HB_data.ptr %= samp_siz; 
}

