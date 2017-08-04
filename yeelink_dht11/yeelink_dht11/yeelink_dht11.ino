#ifndef dht11_h
#define dht11_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


#define DHTLIB_OK        0
#define DHTLIB_ERROR_CHECKSUM -1
#define DHTLIB_ERROR_TIMEOUT  -2

class dht11
{
public:
    int read(int pin);
  int humidity;
  int temperature;
};
#endif

double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

double Kelvin(double celsius)
{
  return celsius + 273.15;
}

double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

        // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;

        // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP/0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}

double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}


dht11 DHT11;

#define DHT11PIN 11


#include <Stepper.h>

const int stepsPerRevolution =4000;  
  int switchStatus_c =0;//12
  int switchStatus_cc =0;//13
  int steps = 4000/2.5*4/6;

Stepper myStepper(stepsPerRevolution, 6, 9);
int serialData;


void setup()
{
  myStepper.setSpeed(100);
  Serial.begin(9600);

  pinMode(4,OUTPUT);//Enable pin of motor 1
  pinMode(5,OUTPUT);//Direction pin of motor 1
  pinMode(7, OUTPUT);//Enable pin of motor 2
  pinMode(8, OUTPUT);//Direction pin of motor 2

        
  digitalWrite(4, LOW);//disable motor first
  digitalWrite(7, LOW);//disable motor first
  pinMode(2, INPUT);//clockwise switch status readin
  pinMode(3, INPUT);//counterclockwise switch status readin
  switchStatus_c = HIGH;
  switchStatus_cc =HIGH;
        
}

void loop()
{
  
  String inString="";
  int serialData = 100;
  while (Serial.available()>0) {
      int inChar=Serial.read();
      if (isDigit(inChar)){
          inString+=(char)inChar;
        }
      serialData=inString.toInt() + 1;
         //Serial.println(serialData);
    }
    
  //Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);

  /*Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
    //Serial.println("OK"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.println("Checksum error"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.println("Time out error"); 
    break;
    default: 
    Serial.println("Unknown error"); 
    break;
  }*/

  //Serial.print("Humidity (%): ");
  //Serial.println((float)DHT11.humidity, 2);
  Serial.print((float)DHT11.humidity, 2);
  Serial.print("  ");

  //Serial.print("Temperature (C): ");
  //Serial.println((float)DHT11.temperature, 2);
  Serial.print((float)DHT11.temperature, 2);
  Serial.println(";");

  //delay(2000);

switch (serialData){
      case 1:
        switchStatus_c = LOW;
        switchStatus_cc = HIGH;
        break;
      //Serial.println("IsZero");
      
      case 2:
        switchStatus_c = HIGH;
        switchStatus_cc = LOW;
        break;
        //Serial.println("IsOne");

      //case 3:
      //case 4:
      //case 5:
      //case 6:
      //case 7:
      
      default:
        switchStatus_c = LOW;
        switchStatus_cc = LOW;
        break;
      //Serial.println("Else");   
    }
    
    if(switchStatus_c == LOW && switchStatus_cc == HIGH){
      //Serial.println("clockwise");
      digitalWrite(4, HIGH);//motor 1
      digitalWrite(5, HIGH);
      
      digitalWrite(7, LOW);//motor 2
      myStepper.step(steps);
      delay(1000);  
  }


  // step one revolution in the other direction:
  else if(switchStatus_c == HIGH && switchStatus_cc == LOW){
    //Serial.println("counterclockwise");
    digitalWrite(4, LOW);//motor 1
    
    digitalWrite(7, HIGH);//motor 2
    digitalWrite(8, LOW);
    myStepper.step(steps);
    delay(1000);
  }
  else{
    //Serial.println("No motion");
    digitalWrite(4, LOW);//motor 1
    digitalWrite(7, LOW);//motor 2
    myStepper.step(0);
    delay(1000);
  }
    
}

