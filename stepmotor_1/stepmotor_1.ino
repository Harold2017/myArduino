#include <Stepper.h>

const int stepsPerRevolution = 2048;  
  int switchStatus_c =0;
  int switchStatus_cc =0;
// change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(5);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  switchStatus_c = HIGH;
  switchStatus_cc =LOW;
  //digitalWrite(12, switchStatus_c);
  //digitalWrite(13, switchStatus_cc);
}

void loop() {
  // step one revolution  in one direction:
  switchStatus_c = digitalRead(2);
   switchStatus_cc = digitalRead(3);
  //Serial.println(switchStatus_c);
  //Serial.println(switchStatus_cc);
    Serial.println(switchStatus_c);
    Serial.println(switchStatus_cc);
    if(switchStatus_c == LOW){
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution/6);
      delay(500);  
  }


  // step one revolution in the other direction:
  else if(switchStatus_cc == HIGH){
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution/6);
    delay(500);
  }
  else{
    Serial.println("No motion");
    myStepper.step(0);
    delay(100);
  }
}
