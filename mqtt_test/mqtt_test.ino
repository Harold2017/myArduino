void setup() {
    Serial.begin(9600);
}

void loop() {
  String inString="";
        int serialData = -100;
  while (Serial.available()>0) {
      int inChar=Serial.read();
      if (isDigit(inChar)){
          //inString+=(char)inChar;
          serialData=inChar;
        }
      //serialData=inString.length();
      
    }

         Serial.print(serialData);
    if (serialData==48){
        Serial.println("IsZero");
    }else if(serialData==49){
        Serial.println("IsOne");
    }else if(serialData==50){
        Serial.println("IsTwo");
    }else if(serialData==51){
        Serial.println("IsThree");
    }else if(serialData==52){
        Serial.println("IsFour");
    }else{
        Serial.println("Else");   
    }
    delay(1000);


}
