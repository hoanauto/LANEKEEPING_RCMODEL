#include <SoftwareSerial.h>

int RX_Pin = 8;
int TX_Pin = 9;

SoftwareSerial bluetooth(RX_Pin, TX_Pin);

void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop(){
  if (bluetooth.available()){
    char receivedChar = bluetooth.read();
    Serial.print(1);
  }
}
