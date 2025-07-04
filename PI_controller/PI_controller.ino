#include <Servo.h>

Servo myServo;

// Khai bao cac chan cua Linear TSL1401
const int AO = A7;
const int SI = 7;
const int CLK = 6;
// Khai bao mang cho diem anh
int pixel[128];

// Khai bao goc quay cua servo
int angle;

// Khai bao diem anh mau trang ben trai va ben phai
int trang_L, trang_R;

// khai bao do sai so giua mau trang va mau den
int err_L, err_R;
// khai bao bien xac dinh can lane trai va phai
int R,L;

void setup(){
  // Thiet Lap cac chan cua Linear TSL1401
  pinMode(AO, INPUT);
  pinMode(CLK, OUTPUT);
  pinMode(SI, OUTPUT);

  // Thiet lap chan cua servo
  myServo.attach(13); 

  // Thiet lap chan cua H brid 
  pinMode(2, OUTPUT); //ENA
  pinMode(3, OUTPUT); //IN1
  pinMode(4, OUTPUT); //IN2

  Serial.begin(9600);

}

// Doc du lieu tu Linear TSL1401
void Linear_cam(int data[128]){
  // Tao xung bat dau
  digitalWrite(SI,DF
  digitalWrite(CLK1);
  delayMicroseconds(10);
  digitalWrite(SI, 0);
  digitalWrite(CLK, 0);

  // Tao 128 xung thu chan CLK 
  for(int i = 0; i < 128; i++){
    digitalWrite(CLK, 1);
    delayMicroseconds(10);
    digitalWrite(CLK, 0);
  }
  // Tao xung ket thuc
  digitalWrite(SI, 1);
  digitalWrite(CLK, 1);
  delayMicroseconds(10);
  digitalWrite(SI, 0);
  digitalWrite(CLK, 0);

  // Thu du lieu anh ve chan analog
  for(int i = 0; i < 128; i++){
    digitalWrite(CLK, 1);
    delayMicroseconds(5);
    digitalWrite(CLK, 0);
    pixel[i] = analogRead(AO);
  }
}


void loop(){
  // Thu du lieu tu Line scaner vao mang pixel
  Linear_cam (pixel);

  // kiem tra xe co can lane trai
  for (int i = 0; i < 50; i++){
    if (pixel[i] > 70) trang_L++;
  }

   for (int i = 60; i < 120; i++){
    if (pixel[i] > 85) trang_R++;
  }


  //Tao bo dieu khien PI cho goc lai angle 
  if (trang_L > 30 ){
    for( int i = 0; i < 50; i++){
      err_L = trang_L; // Sai so giua den tuc thoi den chay thang
      angle= -1*err_L + 90;
      if (angle < 65) angle = 65;
    }
  }
  if (trang_R > 30 ){
    for( int i = 60; i < 120; i++){
      err_R = trang_R;
      angle = 1*err_R + 90;
      if (angle > 114) angle = 114;
    }
  }
  // Goc lai thang
  if (trang_L < 30 && trang_R < 30) angle = 90;

  // Dieu khien mach cau H
  analogWrite(2, 220); // Dieu xung chan ENA voi ti le: 220/255
  digitalWrite(3, 1); // Chieu quay cua motor
  digitalWrite(4, 0);
  // Dieu khien goc quay servo
  myServo.write(angle);
  delay(200);
  Serial.println(angle);
  // Khoi tao lai gia tri cho lan tinh toan tiep theo  
  trang_R = 0;
  trang_L = 0;
  R = 0;
  L = 0;
}