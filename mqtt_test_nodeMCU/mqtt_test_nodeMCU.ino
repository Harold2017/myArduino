
int p = 2;


void setup() {
  Serial.begin(9600);
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
    if (serialData==0){
        Serial.print(p);
        Serial.println("IsZero");
    }else if(serialData==1){
        
        p = p - 1;
        Serial.print(p);
        Serial.println("IsOne");
    }else if(serialData==2){
        
        p = p - 2;
        Serial.print(p);
        Serial.println("IsTwo");
    }else if(serialData==3){

        p = p + 1;
        Serial.print(p);
        Serial.println("IsThree");
    }else if(serialData==4){
       
        p = p + 2;
        Serial.print(p);
        Serial.println("IsFour");
    }else{
        Serial.print(p);
        Serial.println("Else");   
    }
    delay(1000);


}
