#ifndef LORA_IOT_WEB_SERVER_H
#define LORA_IOT_WEB_SERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

bool web_server_init();
bool web_server_connect_wifi();
void web_server_start();
String web_server_process_data(const String& var);

#endif // LORA_IOT_WEB_SERVER_H