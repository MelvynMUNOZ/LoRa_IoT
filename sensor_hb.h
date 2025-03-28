#ifndef SENSOR_HB_H
#define SENSOR_HB_H

#include <Adafruit_Sensor.h>

#define samp_siz 4 
#define rise_threshold 3

struct Sensor_HB_Data{
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
};

extern Sensor_HB_Data HB_data;

void Sensor_HB_init();

void Sensor_HB_get_value();

#endif //SENSOR_HB_H

