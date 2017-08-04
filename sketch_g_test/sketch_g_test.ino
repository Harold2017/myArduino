#include <Stepper.h>

const int stepsPerRevolution =4000;  
  int switchStatus_c =0;
  int switchStatus_cc =0;
  int steps = 4000/2.5*4/6;


Stepper myStepper(stepsPerRevolution, 6, 9);//pin 6 connect to motor 1, pin 7 connect to motor 2

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(100);
  // initialize the serial port:
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
  digitalWrite(12, switchStatus_c);
  digitalWrite(13, switchStatus_cc);
}

void loop() {
  // step one revolution  in one direction:
  switchStatus_c = digitalRead(2);
  switchStatus_cc = digitalRead(3);
  Serial.println(switchStatus_c);
  Serial.println(switchStatus_cc);
      switchStatus_c == LOW;
      Serial.println("clockwise");
      digitalWrite(4, HIGH);//motor 1
      digitalWrite(5, HIGH);
      
      digitalWrite(7, LOW);//motor 2
      myStepper.step(steps);
      delay(2000);  

}
