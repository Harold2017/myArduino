#include <Stepper.h>

const int stepsPerRevolution =4000;  
int steps = 4000/2.5*4/6;
int motor1 = 0;
int motor2 = 0;
int buff = 0;

Stepper myStepper(stepsPerRevolution, 6, 9);//pin 6 connect to motor 1, pin 9 connect to motor 2

void setup() {
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
  motor1 = HIGH;
  motor2 = HIGH;
}

void loop() {
  //String inString="";
        int serialData = -100;
  while (Serial.available()>0) {
      //int inChar=Serial.read();
      //if (isDigit(inChar)){
          //inString+=(char)inChar;
          //serialData=inChar - 48;
        //}
      //serialData=inString.length();
      char in = Serial.read();  
        //Serial.println(in); continue;  
        if (in >= 48 && in <= 57) {  
            serialData = in - 48;  
        } else {  
            break;  
        }  
     
    }

         //Serial.print(serialData);
    if (serialData == buff){
        digitalWrite(4, LOW);//motor 1
        digitalWrite(7, LOW);//motor 2
        myStepper.step(0);
        //Serial.println("IsZero");
    }
    else if(serialData==0){
        digitalWrite(4, LOW);//motor 1
        digitalWrite(7, LOW);//motor 2
        myStepper.step(0);
        //Serial.println("IsZero");
    }else if(serialData==1){
        digitalWrite(4, HIGH);//motor 1
        digitalWrite(5, HIGH);
      
        digitalWrite(7, LOW);//motor 2
        myStepper.step(steps);
        Serial.println("LeftOne");
    }else if(serialData==2){
        digitalWrite(4, HIGH);//motor 1
        digitalWrite(5, HIGH);
      
        digitalWrite(7, LOW);//motor 2
        myStepper.step(steps * 2);
        Serial.println("LeftTwo");
    }else if(serialData==3){
        digitalWrite(4, HIGH);//motor 1
        digitalWrite(5, HIGH);
      
        digitalWrite(7, LOW);//motor 2
        myStepper.step(steps * 3);
        Serial.println("LeftThree");
    }else if(serialData==4){
        digitalWrite(4, HIGH);//motor 1
        digitalWrite(5, HIGH);
      
        digitalWrite(7, LOW);//motor 2
        myStepper.step(steps * 4);;
        Serial.println("LeftFour");
    }else if(serialData==5){
        digitalWrite(7, HIGH);//motor 2
        digitalWrite(8, HIGH);
      
        digitalWrite(4, LOW);//motor 1
        myStepper.step(steps);
        Serial.println("RightOne");
    }else if(serialData==6){
        digitalWrite(7, HIGH);//motor 2
        digitalWrite(8, HIGH);
      
        digitalWrite(4, LOW);//motor 1
        myStepper.step(steps * 2);
        Serial.println("RightTwo");
    }else if(serialData==7){
        digitalWrite(7, HIGH);//motor 2
        digitalWrite(8, HIGH);
      
        digitalWrite(4, LOW);//motor 1
        myStepper.step(steps * 3);
        Serial.println("RightThree");
    }else if(serialData==8){
        digitalWrite(7, HIGH);//motor 2
        digitalWrite(8, HIGH);
      
        digitalWrite(4, LOW);//motor 1
        myStepper.step(steps * 4);
        Serial.println("RightFour");
    }else{
        //Serial.println("Else");   
    }
    buff = serialData;
    delay(1000);


}
