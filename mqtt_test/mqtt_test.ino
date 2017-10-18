#include <Stepper.h>

const int stepsPerRevolution =4000;  
int steps = 4000/2.5*4*2;
int buff = 0;

Stepper myStepper(stepsPerRevolution, 6, 9);//pin 6 connect to motor 1, pin 9 connect to motor 2

void setup() {
  myStepper.setSpeed(100);
  Serial.begin(9600);

  pinMode(5,OUTPUT);//Direction pin of motor 1
  pinMode(8, OUTPUT);//Direction pin of motor 2
  pinMode(4, OUTPUT);//Enable pin of motor 1
  pinMode(7, OUTPUT);//Enable pin of motor 2
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
        myStepper.step(0);
        //Serial.println("IsZero");
    }
    else if(serialData==0){
        myStepper.step(0);
        //Serial.println("IsZero");
    }else if(serialData==1){
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
      
        myStepper.step(steps);
        Serial.println("LeftOne");
    }else if(serialData==2){
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
      
        myStepper.step(steps * 2);
        Serial.println("LeftTwo");
    }else if(serialData==3){
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
      
        myStepper.step(steps * 3);
        Serial.println("LeftThree");
    }else if(serialData==4){
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
      
        myStepper.step(steps * 4);
        Serial.println("LeftFour");
    }else if(serialData==5){
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(4, LOW);
      
        myStepper.step(steps);
        Serial.println("RightOne");
    }else if(serialData==6){
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(4, LOW);
      
        myStepper.step(steps * 2);
        Serial.println("RightTwo");
    }else if(serialData==7){
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(4, LOW);
      
        myStepper.step(steps * 3);
        Serial.println("RightThree");
    }else if(serialData==8){
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(4, LOW);
      
        myStepper.step(steps * 4);
        Serial.println("RightFour");
    }else{
        //Serial.println("Else");   
    }
    buff = serialData;
    delay(500);


}
