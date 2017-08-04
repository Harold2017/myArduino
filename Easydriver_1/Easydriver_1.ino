#include <Stepper.h>

int dirPin = 6;
int stepperPin = 5;
int mov  = 2;
int dir = 3;
int value_1 = 0;
int value_2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  pinMode(mov, INPUT);
  pinMode(dir, INPUT);
}

void step(boolean dir_1, int steps){
  digitalWrite(dirPin,dir_1);
  for(int i=0; i < steps; i ++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(50);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(50);

    // speed control
    delayMicroseconds(100);
    
  }
  delay(2000);
}

void loop(){
  value_1 = digitalRead(mov);
  value_2 = digitalRead(dir);

  if (HIGH == value_1) {
    step(true,0);
    Serial.println("no motion");
  }
  else if (LOW == value_2) {
      step(true, 2048*8/6);
      Serial.println("clockwise");
    }
    else {
      step(false, 2048*8/6);
      Serial.println("counterclockwise");
      }
}

  

