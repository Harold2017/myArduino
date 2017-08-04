#include <Stepper.h>

const int stepsPerRevolution = 2048;  
// change this to fit the number of steps per revolution
// for your motor
static int switchStatus_c;
static int switchStatus_cc;
static unsigned long lastDebounceTime;
#define DEBOUNCE_DELAY 200

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(5);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  switchStatus_c = LOW;
  switchStatus_cc =LOW;
  //digitalWrite(12, switchStatus_c);
  //digitalWrite(13, switchStatus_cc);
}

void updateSwitch(){
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTime) > DEBOUNCE_DELAY){
    lastDebounceTime = currentTime;
   
    switchStatus_c = switchStatus_c == HIGH ? LOW : HIGH;
    switchStatus_cc = switchStatus_cc == HIGH ? LOW : HIGH;
    //digitalWrite(12, switchStatus_c);
    //digitalWrite(13, switchStatus_cc);
    Serial.println(switchStatus_c);
    Serial.println(switchStatus_cc);
    if(switchStatus_c == HIGH){
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution/4);
      delay(100);  
  }


  // step one revolution in the other direction:
  else if(switchStatus_cc == HIGH){
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution/4);
    delay(100);
  }
  }
}
void loop() {
  // step one revolution  in one direction:
  int switchStatus_c = digitalRead(2);
  int switchStatus_cc = digitalRead(3);
  //Serial.println(switchStatus_c);
  //Serial.println(switchStatus_cc);
  if(switchStatus_c == HIGH || switchStatus_cc == HIGH){
    updateSwitch();
  }
  else{
    Serial.println("No motion");
    myStepper.step(0);
    delay(100);
  }
}
