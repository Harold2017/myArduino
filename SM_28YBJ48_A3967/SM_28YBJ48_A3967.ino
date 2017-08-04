/*
  By :Super169
     2015-07-04
*/
#define PIN_DIR  3
#define PIN_STEP 2

#define STEPS_PER_ROUND 16384

unsigned long currentMicros;
unsigned long lastMicros;
unsigned int steps_left = STEPS_PER_ROUND;
unsigned long speed = 6;   // seconds for each round
unsigned long step_time = speed * 1000000 /  STEPS_PER_ROUND;
unsigned long elapse_ms = 0;
unsigned long last_ms = 0;

void setup()
{
  
  Serial.begin(115200);
  Serial.println("Stepper Moter 28YBJ48 with A3967 Testing");
  Serial.println("");
  Serial.print("Expected speed: ");
  Serial.print(speed);
  Serial.println(" s");
  Serial.println("");

  pinMode(PIN_STEP,OUTPUT);
  pinMode(PIN_DIR,OUTPUT);
}

void loop()
{
  digitalWrite(PIN_DIR,!(digitalRead(3)));
  steps_left = STEPS_PER_ROUND;
  lastMicros = micros() - step_time;  // Force to start immedicately
  last_ms = millis();
  while (steps_left > 0)  {
    currentMicros = micros();
    if (currentMicros - lastMicros > step_time) {
      digitalWrite(PIN_STEP,HIGH);
      digitalWrite(PIN_STEP,LOW) ;
      lastMicros = currentMicros;
      steps_left--;
    }
  }
  elapse_ms = millis() - last_ms;
  Serial.print("Elapse time for this rounnd: ");
  Serial.print(elapse_ms);
  Serial.println(" ms");
  delay(1000);
}
