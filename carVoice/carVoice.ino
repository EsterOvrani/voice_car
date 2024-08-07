#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

//***************************************************
VR myVR(2,3);
 
uint8_t records[7]; // save record
uint8_t buf[64];

int led = 13;

#define forwardRecord   (0)
#define backRecord      (1) 
#define leftRecord      (2) 
#define rightRecord     (3) 
#define stopRecord      (4) 
#define fastRecord      (5) 
#define slowRecord      (6) 

//***************************************************
//L289N
#define ENA 5
#define ENB 6
//output (DC)
#define IN1 7 // Front left wheel
#define IN2 8 // Back left wheel
#define IN3 9 // Front right wheel
#define IN4 11 // Back right wheel

//***************************************************

#define CAR_SPEED 100
typedef unsigned char u8;  //Change .the name of unsigned char to u8
u8 change_speed = 0;
//***************************************************

void forward(u8 car_speed)
{
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void back(u8 car_speed)
{
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void left(u8 car_speed)
{

  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right(u8 car_speed)
{
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void _stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void fast()
{
  if(change_speed < 200)
  {
     change_speed + 10;
  }
}

void slow()
{
  if(change_speed > 10)
  {
     change_speed - 10;
  }
}

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  Serial.begin(115200);
  myVR.begin(9600);

}
//***************************************************

void loop() {
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case forwardRecord:
        /**drive forward*/
        forward(CAR_SPEED + change_speed);
        Serial.print("קדימה");
        break;
      case backRecord:
        /**drive back*/
        back(CAR_SPEED + + change_speed);
        Serial.print("אחורה");
        break;
      case leftRecord:
        /**drive left*/
        left(CAR_SPEED + change_speed);
        Serial.print("ימינה");
        break;
      case rightRecord:
        /**drive right*/
        right(CAR_SPEED + change_speed);
        Serial.print("שמאולה");
        break;
      case stopRecord:
        /**drive stop*/
        _stop();
        Serial.print("עצור");
        break;
      case fastRecord:
        /**drive faster*/
        fast();
        break;
      case slowRecord:
        /**drive slower*/
        slow();
        break;
    }
  }

}
