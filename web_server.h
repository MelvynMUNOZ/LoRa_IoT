#ifndef LORA_IOT_WEB_SERVER_H
#define LORA_IOT_WEB_SERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

bool web_server_init();

bool web_server_connect_wifi();
void web_server_start();
void web_server_get_timestamp();
String web_server_process_data(const String& var);

#endif // LORA_IOT_WEB_SERVER_H