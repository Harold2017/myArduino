#include <Stepper.h>

const int stepsPerRevolution =4000;  
int steps = 4000/2.5*4*2;
int buff = 0;

Stepper myStepper_1(stepsPerRevolution, 6, 10);//pin 6 connect to motor 1, pin 9 connect to motor 2
Stepper myStepper_2(stepsPerRevolution, 11, 9);

void setup() {
  myStepper_1.setSpeed(100);
  myStepper_2.setSpeed(100);
  Serial.begin(9600);

  pinMode(5,OUTPUT);//Direction pin of motor 1
  pinMode(8, OUTPUT);//Direction pin of motor 2
}

void loop() {

        int serialData = -100;
  while (Serial.available()>0) {
      char in = Serial.read();  
        //Serial.println(in); continue;  
        if (in >= 48 && in <= 57) {  
            serialData = in - 48;  
        } else {  
            break;  
        }  
     
    }
    if (serialData == buff){
        myStepper_1.step(0);
        myStepper_2.step(0);
        //Serial.println("IsZero");
    }
    else if(serialData==0){
        myStepper_1.step(0);
        myStepper_2.step(0);
        //Serial.println("IsZero");
    }else if(serialData==1){
        digitalWrite(5, LOW);
      
        myStepper_1.step(steps);
        Serial.println("LeftOne");
    }else if(serialData==2){
        digitalWrite(5, LOW);
      
        myStepper_1.step(steps * 2);
        Serial.println("LeftTwo");
    }else if(serialData==3){
        digitalWrite(5, LOW);
      
        myStepper_1.step(steps * 3);
        Serial.println("LeftThree");
    }else if(serialData==4){
        digitalWrite(5, LOW);
      
        myStepper_1.step(steps * 4);
        Serial.println("LeftFour");
    }else if(serialData==5){
        digitalWrite(8, HIGH);
      
        myStepper_2.step(steps);
        Serial.println("RightOne");
    }else if(serialData==6){
        digitalWrite(8, HIGH);
      
        myStepper_2.step(steps * 2);
        Serial.println("RightTwo");
    }else if(serialData==7){
        digitalWrite(8, HIGH);
      
        myStepper_2.step(steps * 3);
        Serial.println("RightThree");
    }else if(serialData==8){
        digitalWrite(8, HIGH);
      
        myStepper_2.step(steps * 4);
        Serial.println("RightFour");
    }else{
        //Serial.println("Else");   
    }
    buff = serialData;
    delay(1000);


}
