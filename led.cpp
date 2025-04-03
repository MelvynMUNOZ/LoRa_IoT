#include "led.h"

void led_init()
{
  pinMode(GPIO_RED_LED, OUTPUT);
  pinMode(GPIO_YELLOW_LED, OUTPUT);
  pinMode(GPIO_GREEN_LED, OUTPUT);
  Serial.println("[LED] Initialized.");
}

void led_red(bool up){
  if(up){
    digitalWrite(GPIO_YELLOW_LED, LOW);
    digitalWrite(GPIO_GREEN_LED, LOW);
    digitalWrite(GPIO_RED_LED, HIGH);
  }else{
    digitalWrite(GPIO_RED_LED, LOW);
  }
}

void led_yellow(bool up){
  if(up){
    digitalWrite(GPIO_RED_LED, LOW);
    digitalWrite(GPIO_GREEN_LED, LOW);
    digitalWrite(GPIO_YELLOW_LED, HIGH);
  }else{
    digitalWrite(GPIO_YELLOW_LED, LOW);
  }
}

void led_green(bool up){
  if(up){
    digitalWrite(GPIO_RED_LED, LOW);
    digitalWrite(GPIO_YELLOW_LED, LOW);
    digitalWrite(GPIO_GREEN_LED, HIGH);
  }else{
    digitalWrite(GPIO_GREEN_LED, LOW);
  }
}