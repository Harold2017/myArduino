
#include <DHT.h>

#define DHTPIN 7     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE); 

#define         MG_PIN                       (A6)     //define which analog input channel you are going to use
#define         DC_GAIN                      (3.2)   //define the DC gain of amplifier
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interval(in milisecond) between each samples in 
#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         REACTION_VOLTGAE             (0.020) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};


int chk;
float hum;  
float temp; 

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
    hum = dht.readHumidity();
    temp= dht.readTemperature();

    int percentage;
    float volts;
     volts = MGRead(MG_PIN);
     percentage = MGGetPercentage(volts,CO2Curve);
     if (percentage == -1) {
        Serial.print(float(hum),2);
        Serial.print("  ");
        Serial.print(float(temp),2);
        Serial.print("  ");
        Serial.print( "400" );
    } else {
        Serial.print(float(hum),2);
        Serial.print("  ");
        Serial.print(float(temp),2);
        Serial.print("  ");
        Serial.print(percentage);
    }
    
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

   
