#include <SoftwareSerial.h> 
SoftwareSerial BT(6, 7);
void setup()
{
       Serial.begin(9600); 
       Serial.println("BT is ready!");
       // HC-05默认，38400
       BT.begin(38400);
       /*delay(100);
       BT.println("AT");
       Serial.println(BT.read());
       delay(100);
       BT.println("AT+NAME=TEST");//命名模块名
       delay(100);
       Serial.println("AT+ROLE=0");//设置主从模式：0从机，1主机
       delay(100);
       Serial.println(BT.read());
       Serial.println("AT+PSWD=1234");//设置配对密码，如1234
       delay(100);
       Serial.println("AT+UART=9600,0,0");//设置波特率9600，停止位1，校验位无
       delay(100);
       Serial.println("AT+RMAAD");//清空配对列表*/
}
void loop()
{
       if (BT.available()){
       Serial.write(BT.read());}
       // Keep reading from Arduino Serial Monitor and send to HC-05
       if (Serial.available()){
       BT.write(Serial.read());}
}
