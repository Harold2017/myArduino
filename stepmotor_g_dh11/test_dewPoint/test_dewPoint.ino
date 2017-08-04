// 
//    FILE: test_dewPoint.pde
// VERSION: 0.1.01
// PURPOSE: test dewpoint
//
// HISTORY:
// 2011-05-01 first version 
// 2013-08-04 updated
// 

// 
//   FILE:  dht11_test1.pde
// PURPOSE: DHT11 library test sketch for Arduino
//

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

// fast integer version with rounding
//int Celcius2Fahrenheit(int celcius)
//{
//  return (celsius * 18 + 5)/10 + 32;
//}


//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
  return celsius + 273.15;
}

// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
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

// delta max = 0.6544 wrt dewPoint()
// 6.9 x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}


void setup()
{
  Serial.begin(115200);
  double f;
  double x;

  unsigned long b = millis();
  for (int i=0; i<1000; i++)
  {
    x = dewPoint(10,50);
  }
  unsigned long e = millis();
  Serial.println(x, 4);
  Serial.println(e-b);
  f = e-b;


  b = millis();
  for (int i=0; i<1000; i++)
  {
    x = dewPointFast(10,50);
  }
  e = millis();
  Serial.println(x, 4);
  Serial.println(e-b);
  f /= (e-b);


  Serial.print("Factor: ");
  Serial.println(f);

  double m = 0;
  for (int t = -30; t < 70; t++)
  {
    for (int h = 0; h < 100; h++)
    {
      double x = dewPoint(t, h);
      double y = dewPointFast(t, h);
      m = max(abs(x-y), m);
      if (m > 0.5)
      {
        Serial.print(t);
        Serial.print("\t");
        Serial.println(h);
      }
    }
    Serial.print(".");
  } 
  Serial.println();
  Serial.print("max: ");
  Serial.println(m);
  Serial.println("done");
}

void loop()
{
}

