#include <Stepper.h>

const int stepsPerRevolution =4000;  
  int switchStatus_c =0;//12
  int switchStatus_cc =0;//13
  int steps = 4000/2.5*4/6;

Stepper myStepper(stepsPerRevolution, 6, 9);//pin 6 connect to motor 1, pin 9 connect to motor 2

int serialData;
void setup(void)
{
  myStepper.setSpeed(100);
  Serial.begin(9600);
  //pinMode(switchStatus_c,INPUT);
  //pinMode(switchStatus_cc,INPUT);

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

void loop(void)
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
    if (serialData==2){
        switchStatus_c = HIGH;
        switchStatus_cc = LOW;
        //Serial.println("IsOne");
    }else if(serialData==1){
      switchStatus_c = LOW;
      switchStatus_cc = HIGH;
      //Serial.println("IsZero");
    }else {
      switchStatus_c = LOW;
      switchStatus_cc = LOW;
      //Serial.println("Else");   
    }

    if(switchStatus_c == LOW && switchStatus_cc == HIGH){
      Serial.println("clockwise");
      digitalWrite(4, HIGH);//motor 1
      digitalWrite(5, HIGH);
      
      digitalWrite(7, LOW);//motor 2
      myStepper.step(steps);
      delay(1000);  
  }


  // step one revolution in the other direction:
  else if(switchStatus_c == HIGH && switchStatus_cc == LOW){
    Serial.println("counterclockwise");
    digitalWrite(4, LOW);//motor 1
    
    digitalWrite(7, HIGH);//motor 2
    digitalWrite(8, LOW);
    myStepper.step(steps);
    delay(1000);
  }
  else{
    Serial.println("No motion");
    digitalWrite(4, LOW);//motor 1
    digitalWrite(7, LOW);//motor 2
    myStepper.step(0);
    delay(1000);
  }
}
