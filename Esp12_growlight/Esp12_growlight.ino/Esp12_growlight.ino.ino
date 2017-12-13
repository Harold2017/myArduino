#include <SoftwareSerial.h>

//nodeMCU 1.0 (esp12E)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Losant.h>


// Rx, Tx GPIO
SoftwareSerial mySerial(3, 1);// Rx, Tx
byte Readmv[8]={02,03,00,00,00,04,68,58};//measured value 对应的为02 03 00 00 00 04 44 3A
String comdata = "";

// WiFi credentials.
const char* WIFI_SSID = "nami-staffs";
const char* WIFI_PASS = "nami09access";

float CO2 = 0;
float temperature = 0;
float humidity = 0;
float light = 0;
int m[16];


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
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  mySerial.begin(9600);

  // Wait for serial to initialize.
  while(!Serial) { }

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");
  connect();
}

void report(float value, String api_address) {
  HTTPClient http;
  http.begin(api_address);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");
  
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["timestamp"] = "None";
  root["value"] = value;

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


void readData(){
  mySerial.write(&Readmv[0],8);
  while(mySerial.available() > 0){
    comdata+=char(mySerial.read());
    //delay(2);
  }  
/*if(comdata.length() > 0)             
  {
//    Serial.println(comdata); 
      for(int i=0;i<comdata.length();i++){
       Serial.print("comdata[");
       Serial.print(i,DEC);
       Serial.print("]=");
       Serial.println(comdata[i],HEX);  
      }
      
      
  } */
  }

int charToHex(char n){
  int x = n - '0';
  if (x < 10){
  return x;}
  else {
    return (x - 7);}
  }

void calculate(String n) {
  for (int i = 0; i <= 15; i++) {
    //m[i-9] = charToHex(n[i]);
    m[i] = n[i];
    }
        /*CO2 = (m[0]*16 + m[1])*256 + m[2]*16 + m[3];
        temperature = ((m[4]*16 + m[5])*256 + m[6]*16 + m[7])/100;
        humidity = ((m[8]*16 + m[9])*256 + m[10]*16 + m[11])/100;
        light = ((m[12]*16 + m[13])*256 + m[14]*16 + m[15])*4;*/
        CO2 = n.length();
        temperature = m[1];
        humidity = m[3];
        light = m[4];
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
  readData();
  calculate(comdata);
  delay(2000);
  comdata="";

  // Report every 2 seconds.
  if(timeSinceLastRead > 2000) {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

    // Check if any reads failed and exit early (to try again).
    if (isnan(CO2)) {
      Serial.println("Failed to read from sensors!");
      timeSinceLastRead = 0;
      return;
    }

    report(CO2, "http://namiiot.ap.ngrok.io/api/v2.0/d191f1037551707c08622d778bb1438a/36");
    //report(temperature, "http://namiiot.ap.ngrok.io/api/v2.0/d191f1037551707c08622d778bb1438a/34");
    //(humidity, "http://namiiot.ap.ngrok.io/api/v2.0/d191f1037551707c08622d778bb1438a/35");
    //report(light, "http://namiiot.ap.ngrok.io/api/v2.0/d191f1037551707c08622d778bb1438a/39");

    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}
