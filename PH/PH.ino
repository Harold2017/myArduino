void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  float data = 0;
  float PH = 0;
  float T = 0;
  data = analogRead(A0);
  T = analogRead(A2);
  data = data*5/1024;
  T = (T*5/1024)*100/5-20;

  PH = PH_V(data);

  Serial.print(PH);
  Serial.print("  ");
  Serial.print(T);
  Serial.println();
  delay(500);

}

float PH_V(float data) {
  float v;

    if (0.00<=data<=0.36) {
    v = data/0.36;
  }
  else if (0.36<data<=0.71) {
    v = (data-0.36)/0.35+1;
  }
  else if (0.71<data<=1.07) {
    v = (data-0.71)/0.36+2;
  }
  else if (1.07<data<=1.43) {
    v = (data-1.07)/0.36+3;
  }
  else if (1.43<data<=1.79) {
    v = (data-1.43)/0.36+4;
  }
  else if (1.79<data<=2.14) {
    v = (data-1.79)/0.35+5;
  }
  else if (2.14<data<=2.50) {
    v = (data-2.14)/0.36+6;
  }
  else if (2.50<data<=2.86) {
    v = (data-2.50)/0.36+7;
  }
  else if (2.86<data<=3.21) {
    v = (data-2.86)/0.35+8;
  }
  else if (3.21<data<=3.57) {
    v = (data-3.21)/0.36+9;
  }
  else if (3.57<data<=3.93) {
    v = (data-3.57)/0.36+10;
  }
  else if (3.93<data<=4.29) {
    v = (data-3.93)/0.36+11;
  }
  else if (4.29<data<=4.64) {
    v = (data-4.29)/0.35+12;
  }
  else if (4.64<data<=5.00) {
    v = (data-4.64)/0.36+13;
  }
  return v;
}

