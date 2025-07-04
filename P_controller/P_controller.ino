#include <Servo.h>

Servo myServo;

// Khai bao cac chan cua Linear TSL1401
const int AO = A8;
const int SI = 7;
const int CLK = 6;
const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;

int pixel[128];
int angle;
int trang_L, trang_R;
int VT_L_MAX, VT_R_MAX, VT_MID;
int MAX_L, MAX_R;
int Do_rong;
int err;
int x;


void setup(){
  // Thiet Lap cac chan cua Linear TSL1401
  pinMode(AO, INPUT);
  pinMode(CLK, OUTPUT);
  pinMode(SI, OUTPUT);

  // Thiet lap chan cua servo
  myServo.attach(13); 

  // Thiet lap chan cua H brid 
  pinMode(ENA, OUTPUT); //ENA
  pinMode(IN1, OUTPUT); //IN1
  pinMode(IN2, OUTPUT); //IN2

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
  trang_L = 0;
  trang_R = 0;
  VT_L_MAX = 0;
  VT_R_MAX = 0;
  MAX_L = 175;
  MAX_R = 175;
  Linear_cam (pixel);
  // Dem so luong pixel trang ben trai
  for (int i = 1; i < 63; i++){
    if (pixel[i] > 220){
      trang_L ++;
    }
  }
  for (int i = 65; i < 128; i++){
    if (pixel[i] > 190){
      trang_R ++;
    }
  }

  if (trang_L > 5){
    for (int i = 1; i < 64; i++){
      if (MAX_L < pixel[i]) {
        MAX_L = pixel[i];
        VT_L_MAX = i;
        }
      else{ 
        VT_L_MAX = VT_L_MAX;
        MAX_L = MAX_L;
        }
    }
  }
  if (trang_R > 5){
    for (int i = 65; i < 128; i++){
      if (MAX_R < pixel[i]) {
        MAX_R = pixel[i];
        VT_R_MAX = i;
        }
      else{ 
        VT_R_MAX = VT_R_MAX;
        MAX_R = MAX_R;
        }
    }
  }
  if ((VT_L_MAX < 21 && VT_L_MAX > 99) || (VT_L_MAX > 21 && VT_L_MAX < 99) || (VT_L_MAX != 0 && VT_R_MAX == 0)){
    if (VT_L_MAX > 21 && VT_L_MAX != x){
      x = VT_L_MAX;
      VT_L_MAX = VT_L_MAX;
    }
    else VT_L_MAX = x;
    VT_R_MAX = 127;
    }
  if (VT_R_MAX == 0) VT_R_MAX = 127;
  x = VT_L_MAX;
  
  Do_rong = VT_R_MAX - VT_L_MAX;
  VT_MID = VT_L_MAX + (Do_rong / 2);
  err = VT_MID - 64;

  //can lane phai
  if (err < -2){
    angle = -1.56 * err + 90;
  }
  //can lane trai
  if (err > 2){
    angle = - 2.73 * err + 90;
  }
  //giua lane
  if (err < 2 && err > -2) angle = 90;

  if (angle > 120) angle = 120;
  if (angle < 60) angle = 60;
    

  for (int i = 0; i < 128; i++){
    if (i == 64) Serial.println(50);
    Serial.println(pixel[i]);
    delay(200);
  }
  analogWrite(ENA, 230);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  myServo.write(angle);
  delay(50);
  
}