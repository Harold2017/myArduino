#include <Stepper.h>

const int stepsPerRevolution =4000;  
int steps = 4000/2.5*4;
int motor1 = 0;
int motor2 = 0;

//Stepper myStepper(stepsPerRevolution, 6, 9);//pin 6 connect to motor 1, pin 9 connect to motor 2

int serialData;
void setup(void)
{
  //myStepper.setSpeed(20);
  Serial.begin(9600);

  //pinMode(4,OUTPUT);//Enable pin of motor 1
  pinMode(5,OUTPUT);//Direction pin of motor 1
  //pinMode(7, OUTPUT);//Enable pin of motor 2
  pinMode(8, OUTPUT);//Direction pin of motor 2

        
  //digitalWrite(4, HIGH);//disable motor first
  //digitalWrite(7, HIGH);//disable motor first
  pinMode(2, INPUT);//clockwise switch status readin
  pinMode(3, INPUT);//counterclockwise switch status readin
  motor1 = HIGH;
  motor2 = HIGH;
}

void loop(void)
{
    motor1 = digitalRead(2);
    motor2 = digitalRead(3);

    
    if(motor1 == LOW && motor2 == HIGH){
      Serial.println("clockwise");
      Stepper myStepper(stepsPerRevolution, 6, 10);//pin 6 connect to motor 1, pin 9 connect to motor 2
      myStepper.setSpeed(20);
      //digitalWrite(4, HIGH);//motor 1
      digitalWrite(5, HIGH);
      
      //digitalWrite(7, HIGH);//motor 2
      myStepper.step(steps);
      delay(1000);  
  }


  // step one revolution in the other direction:
  else if(motor1 == HIGH && motor2 == LOW){
    Serial.println("counterclockwise");
    Stepper myStepper(stepsPerRevolution, 10, 9);//pin 6 connect to motor 1, pin 9 connect to motor 2
      myStepper.setSpeed(20);
    //digitalWrite(4, HIGH);//motor 1
    
    //digitalWrite(7, HIGH);//motor 2
    digitalWrite(8, HIGH);
    myStepper.step(steps);
    delay(1000);
  }
  else{
    Serial.println("No motion");
    //digitalWrite(4, LOW);//motor 1
    //digitalWrite(7, LOW);//motor 2
    //myStepper.step(0);
    delay(1000);
  }
}
