int pulsePin = 0;                

void setup(){
  //pinMode(blinkPin,OUTPUT);         
Serial.begin(9600);             
}

void loop(){
int sensorValue = analogRead(pulsePin);   
Serial.println(sensorValue, DEC);
}
/*if(sensorValue>510)  
        {  
digitalWrite(blinkPin, HIGH);   
        }
   else{
digitalWrite(blinkPin, LOW);       
       }
delay(30);     
*/
