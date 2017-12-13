String incomingByte;   // for incoming serial data
unsigned int output;
byte Readmv[8]={0x02,0x03,0x00,0x00,0x00,0x04,0x44,0x3A};//measured value 对应的为02 03 00 00 00 04 44 3A
String comdata = "";

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void myPtHex(int g){ // 把 g 最右邊 byte 印成 Hex 倆位
  int a = g& 0xf0;  // 左邊 4 bits
  int b = g& 0x0f;  // 右邊 4 bits
  char c = a < 10 ? a + '0' : a + 'A' - 10;
  Serial.write(c);
  c = b < 10 ? b + '0' : b + 'A' - 10;
  Serial.write(c);
} // myPtHex(

int charToHex(char n){
  int x = n - '0';
  if (x < 10){
  return x;}
  else {
    return (x - 7);}
  }

void loop() {
  Serial.print(Readmv)

        // send data only when you receive data:
        while (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte += char(Serial.read());
        }

                // say what you got:
                for (int i=0; i<incomingByte.length(); i++){
                  Serial.print("incomingByte[");
                  Serial.print(i,DEC);
                  Serial.print("]=");
                  //myPtHex(incomingByte[i]);
                  //output = incomingByte[i];
                  Serial.println( charToHex(incomingByte[i]));
                }
                delay(2000);
        
}
