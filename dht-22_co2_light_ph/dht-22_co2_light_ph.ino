
#include <DHT.h>

#define DHTPIN 7     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE); 

#define         MG_PIN                       (6)     //define which analog input channel you are going to use
#define         DC_GAIN                      (3.2)   //define the DC gain of amplifier
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interval(in milisecond) between each samples in 
#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         REACTION_VOLTGAE             (0.020) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};


int chk;
float hum;  
float temp; 

float Light_Analog_In = 0;
int Light_Output = 0;
#define Light_In_Pin      (A1)
#define Light_Low_Pin     (3)

void setup()
{
  Serial.begin(9600);
  pinMode(Light_In_Pin, INPUT);
pinMode(Light_Low_Pin,OUTPUT);
digitalWrite(Light_Low_Pin ,LOW);

pinMode(A0, INPUT);
  pinMode(A2, INPUT);

  dht.begin();
}

void loop()
{
    hum = dht.readHumidity();
    temp= dht.readTemperature();

    int percentage;
  float volts;

   float data = 0;
  float PH = 0;
  float T = 0;
  data = analogRead(A0);
  T = analogRead(A2);
  data = data*5/1024;
  T = (T*5/1024)*100/5-20;

  PH = PH_V(data);

  digitalWrite(Light_Low_Pin ,LOW);
  Light_Analog_In = analogRead(Light_In_Pin);
  Light_Output = (Light_Analog_In*5/1024)*1000;
   
    Serial.print(float(hum),2);

    Serial.print("  ");
    Serial.print(float(temp),2);
    Serial.print("  ");

    Serial.print(PH);
  Serial.print("  ");
  Serial.print(T);
  Serial.print("  ");

    volts = MGRead(MG_PIN);
     percentage = MGGetPercentage(volts,CO2Curve);
     if (percentage == -1) {
        Serial.print( "400" );
    } else {
        Serial.print(percentage);
    }

    Serial.print("  ");
    Serial.print(Light_Output);
    Serial.print("     ");
    
  Serial.println();

    delay(500);
}

float MGRead(int mg_pin)
{
    int i;
    float v=0;

    for (i=0;i<READ_SAMPLE_TIMES;i++) {
        v += analogRead(mg_pin);
        delay(READ_SAMPLE_INTERVAL);
    }
    v = (v/READ_SAMPLE_TIMES) *5/1024 ;
    return v;  
}

int  MGGetPercentage(float volts, float *pcurve)
{
   if ((volts/DC_GAIN )>=ZERO_POINT_VOLTAGE) {
      return -1;
   } else { 
      return pow(10, ((volts/DC_GAIN)-pcurve[1])/pcurve[2]+pcurve[0]);
   }
}

float PH_V(float data) {
  float v;

    if (0.00<=data<=0.36) {
    v = data/0.36;
  }
  else if (0.36<data<=0.71) {
    v = (data-0.36)/0.35+1;
  }
  else if (0.71<data<=1.07) {
    v = (data-0.71)/0.36+2;
  }
  else if (1.07<data<=1.43) {
    v = (data-1.07)/0.36+3;
  }
  else if (1.43<data<=1.79) {
    v = (data-1.43)/0.36+4;
  }
  else if (1.79<data<=2.14) {
    v = (data-1.79)/0.35+5;
  }
  else if (2.14<data<=2.50) {
    v = (data-2.14)/0.36+6;
  }
  else if (2.50<data<=2.86) {
    v = (data-2.50)/0.36+7;
  }
  else if (2.86<data<=3.21) {
    v = (data-2.86)/0.35+8;
  }
  else if (3.21<data<=3.57) {
    v = (data-3.21)/0.36+9;
  }
  else if (3.57<data<=3.93) {
    v = (data-3.57)/0.36+10;
  }
  else if (3.93<data<=4.29) {
    v = (data-3.93)/0.36+11;
  }
  else if (4.29<data<=4.64) {
    v = (data-4.29)/0.35+12;
  }
  else if (4.64<data<=5.00) {
    v = (data-4.64)/0.36+13;
  }
  return v;
}

   
