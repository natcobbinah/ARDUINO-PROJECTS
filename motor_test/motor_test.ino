#include <AFMotor.h>

AF_DCMotor Motor_Left(1,MOTOR12_1KHZ);// MOTOR 1
AF_DCMotor Motor_Right(2,MOTOR12_1KHZ); //MOTOR 2

int pwm;

const int LED_PIN = 13;
const int speed = 60; //percent of maximum speed

void setup() {
 Serial.begin(9600);
 blinkNumber(8);

 //scale percent into pwm range(0-255)
 pwm = map(speed, 0,100,0,255);
 Motor_Left.setSpeed(pwm);
 Motor_Right.setSpeed(pwm);
}

void loop() {
 Serial.println("rotate cw");
 Motor_Left.run(FORWARD);
 Motor_Right.run(BACKWARD);
 delay(5000);  //run for 5 seconds
 Serial.println("rotate ccw");
 Motor_Left.run(RELEASE); // stop thhe motors
 Motor_Right.run(RELEASE);
 delay(5000); //stop for 5 seconds
}

void blinkNumber(byte Number){
  pinMode(LED_PIN,OUTPUT);
  while(Number--){
    digitalWrite(LED_PIN,HIGH); //delay 100
    digitalWrite(LED_PIN,LOW); //delay(400);
  }
}

