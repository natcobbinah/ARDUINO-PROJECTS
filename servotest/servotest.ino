#include <Servo.h>

Servo myServo;

void setup() 
{
  Serial.begin(9600);
   myServo.attach(2);
}

void loop()
{
  myServo.write(90);
  delay(2000);

  myServo.write(180);
  delay(2000);
//
//  myServo.write(90);
//  delay(2000);
//
  myServo.write(0);
  delay(2000);
}

