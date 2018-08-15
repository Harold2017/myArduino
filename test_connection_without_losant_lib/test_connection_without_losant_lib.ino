#include <ESP8266WiFi.h>
#include "PubSubClient.h"

// WiFi credentials.
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

// Losant credentials.
const char* LOSANT_DEVICE_ID = "";
const char* LOSANT_ACCESS_KEY = "";
const char* LOSANT_ACCESS_SECRET = "";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Command received.");
}

WiFiClient wiFiclient;
PubSubClient client("broker.losant.com", 1883, callback, wiFiclient);


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
   // WiFi fix: https://github.com/esp8266/Arduino/issues/2186
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  if(client.connect(LOSANT_DEVICE_ID, LOSANT_ACCESS_KEY, LOSANT_ACCESS_SECRET)) {
    Serial.println("Connected to Losant");
  }
  else {
    Serial.println("Failed to connect.");
    Serial.println(client.state());
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}

