#define Aout    (6)
#define Dout    (2)
#define Tcm     (3)

#define         READ_SAMPLE_INTERVAL         (50)  
#define         READ_SAMPLE_TIMES            (5) 

#define         V400        (984)               
#define         V40000   (745)   

float slope=(V40000-V400)/(4.602-2.602);
           //校正線的斜率計算
           //log40000=4.602
           //log400=2.602

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Aout, INPUT);
pinMode(Dout, INPUT);
pinMode(Tcm, INPUT);
}


float aout = 0;
int dout = 3;
float tcm = 0;
void loop() {
  // put your main code here, to run repeatedly:
 aout = MGRead(Aout);
 dout = digitalRead(Dout);
 tcm = analogRead(Tcm);
 Serial.print(aout);
 Serial.print("\n");
 Serial.print(dout);
 Serial.print("\n");
 Serial.print(tcm);
 Serial.print("\n");
 Serial.print("\n");
 delay(500);
}


float MGRead(int mg_pin)
{
    int i;
    float v=0;
 
    for (i=0;i<READ_SAMPLE_TIMES;i++) {
        v += analogRead(mg_pin);
        delay(READ_SAMPLE_INTERVAL);
    }
    v =v/READ_SAMPLE_TIMES ;
    return v;  
}
 

int  MGGetPercentage(float analogValue)
{   
     float logConc=2.602 +(analogValue-V400)/slope; //計算目前二氧化碳的濃度log值
      return pow(10,logConc );
 
}
