int dirPin = 6;
int stepperPin = 5;
int switch1  = 2;
int switch2 = 3;
int value;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
}

void step(boolean dir,int steps){
  digitalWrite(dirPin,dir);
  for(int i=0; i < steps; i ++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(50);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(50);

    // speed control
    delayMicroseconds(100);
  }
}

void loop(){
  value = digitalRead(switch1);
  if (LOW == value) {
    step(true,2048/6);
  }

  value = digitalRead(switch2);
  if (HIGH == value) {
      step(false,2048/6);
  }

}
