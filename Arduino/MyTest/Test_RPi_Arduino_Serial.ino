#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial softSerial(12,13);
int code;
//SoftwareSerialにて  Arduino<-->RPiとのシリアル通信を行い
//Serialにて          Arduino<-->Host PCとのシリアル通信を行う
void setup()
{
  
  softSerial.begin(9600);
  Serial.begin(9600);
  while (!softSerial) {
  }
  while(!Serial){
  }
}

void loop()
{
  if(softSerial.available() > 0){
    delay(100);
    Serial.print("RPi->Arduino  ");
    while(softSerial.available()){
      Serial.print((char)(int)softSerial.read());
    }
  }
  

  if(Serial.available() > 0){
    delay(100);//入力待ち
    Serial.print("Arduino->RPi  ");
    while(Serial.available()){
      code = Serial.read();  
      Serial.write(code);
      softSerial.write(code);
    }
    Serial.print("\n");
  }
}
