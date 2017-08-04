/**
 * Example for sending temperature and humidity
 * to the cloud using the DHT22 and ESP8266
 *
 * Copyright (c) 2016 Losant IoT. All rights reserved.
 * https://www.losant.com
 */


#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Losant.h>

#define DHTPIN 5     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // There are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials.
const char* WIFI_SSID = "SSID";
const char* WIFI_PASS = "PASSWORD";


WiFiClientSecure wifiClient;

void connect() {

  // Connect to Wifi.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  // WiFi fix: https://github.com/esp8266/Arduino/issues/2186
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long wifiConnectStart = millis();

  while (WiFi.status() != WL_CONNECTED) {
    // Check to see if
    if (WiFi.status() == WL_CONNECT_FAILED) {
      Serial.println("Failed to connect to WIFI. Please verify credentials: ");
      Serial.println();
      Serial.print("SSID: ");
      Serial.println(WIFI_SSID);
      Serial.print("Password: ");
      Serial.println(WIFI_PASS);
      Serial.println();
    }

    delay(500);
    Serial.println("...");
    // Only try for 5 seconds.
    if(millis() - wifiConnectStart > 5000) {
      Serial.println("Failed to connect to WiFi");
      Serial.println("Please attempt to send updated configuration parameters.");
      return;
    }
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Create JSON payload to sent to Losant
   *
   *   {
   *     "deviceId": "575ecf887ae143cd83dc4aa2",
   *     "key": "this_would_be_the_key",
   *     "secret": "this_would_be_the_secret"
   *   }
   *
   */
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");
  connect();
}

void report(float humidity) {
  HTTPClient http;
  http.begin("api_address");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");
  
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["timestamp"] = "None";
  root["value"] = humidity;

  String buffer;
  root.printTo(buffer);
  Serial.println("Reported!");
  Serial.println(buffer);
  int httpCode = http.POST(buffer);

  if(httpCode > 0) {
      if(httpCode == 201) {
          Serial.println("Uploaded.");
      } else {
        Serial.println("Failed to upload.");
        if(httpCode == 405) {
          Serial.println("No data uploaded.");
        } else if(httpCode == 404) {
          Serial.println("Invalid token.");
        } else {
           Serial.println("Unknown response from API");
        }
      }
    } else {
        Serial.println("Failed to connect.");

   }

  http.end();
}

int timeSinceLastRead = 0;
void loop() {
   bool toReconnect = false;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected from WiFi");
    toReconnect = true;
  }

  if (toReconnect) {
    connect();
  }

  // Report every 2 seconds.
  if(timeSinceLastRead > 900000) {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    //h = int(h*10000);
    //h = h/10000;
    report(h);

    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}
