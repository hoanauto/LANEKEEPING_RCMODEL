#include <Servo.h>

Servo myServo;

// Khai bao cac chan cua Linear TSL1401
const int AO = A0;
const int SI = 7;
const int CLK = 6;

int pixel[128];
int angle;
int trang;


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

  digitalWrite(SI, 1);
  digitalWrite(CLK, 1);
  delayMicroseconds(10);
  digitalWrite(SI, 0);
  digitalWrite(CLK, 0);


  for(int i = 0; i < 128; i++){
    digitalWrite(CLK, 1);
    delayMicroseconds(10);
    digitalWrite(CLK, 0);
  }
  digitalWrite(SI, 1);
  digitalWrite(CLK, 1);
  delayMicroseconds(10);
  digitalWrite(SI, 0);
  digitalWrite(CLK, 0);

  for(int i = 0; i < 128; i++){
    digitalWrite(CLK, 1);
    delayMicroseconds(5);
    digitalWrite(CLK, 0);
    pixel[i] = analogRead(AO);
  }
}


void loop(){
  trang = 0;
  Linear_cam (pixel);
  // Dem so luong pixel trang ben trai
  for (int i = 0; i < 128; i++){
    if (pixel[i] > 40){
      trang ++;
    }
  }
  if (trang > 40){
    for (int i = 0; i < 50; i++){
      //Lech ben trai
      if (pixel[i] - pixel[i+2] > 20){
        angle = 45;
        break;
      } 
    for (int i = 70; i < 120; i++){
      //Lech ben phai
      if (pixel[i] - pixel[i+3] < -20){
        angle = 115;
        break;}
      }
    }
  }
  if (trang < 10) angle = 75;
  
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  myServo.write(angle);
  Serial.println(angle);
  delay(200);
}