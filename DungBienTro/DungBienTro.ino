
#include <Servo.h>

Servo myServo;

int TinhHieu;             
int GocLai;            

void setup() {
  myServo.attach(8);  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  digitalWrite(2, 1);

  TinhHieu = analogRead(A0); 
  GocLai = map(TinhHieu, 0, 1023, 140, 180);

  Serial.print("TinhHieu ");
  Serial.print(TinhHieu);
  Serial.print(", GocLai ");
  Serial.println(GocLai);

  myServo.write(GocLai);

  
  delay(15);
}
