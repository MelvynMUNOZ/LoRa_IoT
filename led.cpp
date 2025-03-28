#include "esp32-hal-gpio.h"
#include "led.h"

void led_init(){
  pinMode(GPIO_LED, OUTPUT);
}

void led_red(bool up){
  if(up){
    digitalWrite(GPIO_LED, HIGH);
  }else{
    digitalWrite(GPIO_LED, LOW);
  }
}