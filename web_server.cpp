#include "web_server.h"
#include "oled_display.h"
#include "plant_health.h"

const char *wifi_ssid = "Vinh Diesel sans diesel";
const char *wifi_passwd = "..........";

AsyncWebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;
String day;
String hour;
String timestamp;

bool web_server_init()
{
  web_server_connect_wifi();

  // Initialize file system
  if (LittleFS.begin() == false) {
    Serial.println("[WEB_SERVER] Failed to init LittleFS.");
    return false;
  }

  // Setup routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", String(), false, web_server_process_data);
  });
  server.on("/timestamp", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", timestamp.c_str());
  });
  server.on("/health", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(indicators.health_state).c_str());
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(bme680_data.temperature).c_str());
  });
  server.on("/luminosity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(tmg3993_data.lux).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(bme680_data.humidity).c_str());
  });
  server.on("/airquality", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", sensor_bme680_air_quality_state().c_str()); 
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(bme680_data.pressure).c_str());
  });
  server.on("/wood", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/wood.jpg", "image/jpg");
  });

  Serial.println("[WER_SERVER] Initialized.");
  return true;
}

bool web_server_connect_wifi()
{
  if (wifi_ssid == "") {
    Serial.println("[WEB_SERVER] Invalid SSID.");
    oled_display.clear();
    oled_display.drawString(0, 0, "Invalid WiFi SSID.");
    oled_display.display();
    return false;
  }

  Serial.print("[WEB_SERVER] Connecting to ");
  Serial.print(wifi_ssid);
  oled_display.clear();
  oled_display.print("Connecting");
  oled_display.display();

  WiFi.begin(wifi_ssid, wifi_passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    oled_display.print(".");
    oled_display.display();
  }
  Serial.println("");
  Serial.println("[WEB_SERVER] Connected.");
  Serial.print("[WEB_SERVER] IP address: ");
  Serial.println(WiFi.localIP());

  oled_display.clear();
  oled_display_print_web_server_address();
  oled_display.display();
  return true;
}

void web_server_start()
{
  server.begin();
  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void web_server_get_timestamp()
{
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();

  // Extract date
  int splitT = formattedDate.indexOf("T");
  day = formattedDate.substring(0, splitT);
  // Extract time
  hour = formattedDate.substring(splitT+1, formattedDate.length()-1);
  timestamp = day + " " + hour;
}

String web_server_process_data(const String& var)
{
  // Transform placeholder text into actual data
  if (var == "TIMESTAMP") {
    return timestamp;
  }
  else if (var == "HEALTH") {
    return String(indicators.health_state);
  }
  else if (var == "TEMPERATURE") {
    return String(bme680_data.temperature);
  }
  else if (var == "LUMINOSITY") {
    return String(tmg3993_data.lux);
  }
  else if (var == "HUMIDITY") {
    return String(bme680_data.humidity);
  }
  else if (var == "AIRQUALITY") {
    return sensor_bme680_air_quality_state();
  }
  else if (var == "PRESSURE") {
    return String(bme680_data.pressure);
  }
  return String();
}
