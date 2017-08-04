float A = 0;
float Data = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A6, INPUT);
pinMode(6,OUTPUT);
digitalWrite(6,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(6,LOW);
A = analogRead(A6);
Data = (A*5/1024)*1000;
Serial.print(A);
Serial.print("  ");
Serial.print(Data);
Serial.println(" ");
delay(500);
}
