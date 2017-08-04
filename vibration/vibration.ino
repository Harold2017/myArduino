
#define SensorLED     6
#define SensorINPUT   8  

unsigned char state = 0;

void setup() 
{ 
  pinMode(SensorLED, OUTPUT); 
  pinMode(SensorINPUT, INPUT);
  attachInterrupt(0, blink, FALLING);//D2口为外部中断0，当有下降沿触发的时候调用blink函数
  Serial.begin(9600);

}
void loop()
{
      if(state!=0)
      {
        state = 0;
        digitalWrite(SensorLED,HIGH);
        Serial.println("Close");
        delay(500);
      }  
      else 
        digitalWrite(SensorLED,LOW);
        Serial.println("Open");
        //delay(500);
}  


void blink()//数字输入传感器下降沿触发中断服务函数
{
  state++;
}
