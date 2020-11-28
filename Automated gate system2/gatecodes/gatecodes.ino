#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);

const int pingPin=3; //trigger alert pin
const int echoPin=2; //receive distance from obstacle approaching
long duration,inches,cm;
int limitCm=400;

const int motorPin1=4;
const int motorPin4=5;
const int motorPin2=6;
const int motorPin3=7;

int INCspeed=A0;
int storeincvalue;
int storeincvalue2;

int callbtn = 15;
int txtbtn = 16;

int openLimitSwitch=17;
int closeLimitSwitch=18;

void setup() 
{
   Serial.begin(9600);
   pinMode(pingPin,OUTPUT);
   pinMode(echoPin,INPUT);

   pinMode(motorPin1,OUTPUT);
   pinMode(motorPin4,OUTPUT);
   pinMode(motorPin2,OUTPUT);
   pinMode(motorPin3,OUTPUT);

   pinMode(callbtn,INPUT);
   pinMode(txtbtn,INPUT);
   
   pinMode(openLimitSwitch,INPUT);
   pinMode(closeLimitSwitch,INPUT);

   lcd.begin(20,2);
}

void loop() 
{

   digitalWrite(pingPin,LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin,LOW);

   duration=pulseIn(echoPin,HIGH);
   inches = microSecondsToInches(duration);
   cm     = microSecondsToCentimeters(duration);
 
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(1000);   


   storeincvalue=analogRead(INCspeed)/10;
   storeincvalue2=storeincvalue/1.01;
   Serial.println("Gate speed is:");
   Serial.println(storeincvalue2);
   lcd.setCursor(0,1);
   lcd.print("Gate Speed");
   lcd.print(storeincvalue2);
   delay(1000);


   if(digitalRead(callbtn) == HIGH)
   {
     digitalWrite(motorPin1,HIGH);
     digitalWrite(motorPin4,HIGH);
     digitalWrite(motorPin2,LOW);
     digitalWrite(motorPin3,LOW);
   }

   if(digitalRead(txtbtn) == HIGH)
   {
     digitalWrite(motorPin1,LOW);
     digitalWrite(motorPin4,LOW);
     digitalWrite(motorPin2,HIGH);
     digitalWrite(motorPin3,HIGH);
   }

    if ((digitalRead(txtbtn) == HIGH) && (digitalRead(closeLimitSwitch) == HIGH))
   {
     digitalWrite(motorPin1,LOW);
     digitalWrite(motorPin4,LOW);
     digitalWrite(motorPin2,LOW);
     digitalWrite(motorPin3,LOW);
   }

   if ((digitalRead(callbtn) == HIGH) && (digitalRead(openLimitSwitch) == HIGH))
   {
     digitalWrite(motorPin1,LOW);
     digitalWrite(motorPin4,LOW);
     digitalWrite(motorPin2,LOW);
     digitalWrite(motorPin3,LOW);
   }

//   else if(digitalRead(txtbtn) == HIGH)
//   {
//     digitalWrite(motorPin1,LOW);
//     digitalWrite(motorPin4,LOW);
//     digitalWrite(motorPin2,HIGH);
//     digitalWrite(motorPin3,HIGH);
//   }

   if ((digitalRead(callbtn) == HIGH) && (digitalRead(openLimitSwitch) == HIGH) && (cm > limitCm))
   {
     digitalWrite(motorPin1,LOW);
     digitalWrite(motorPin4,LOW);
     digitalWrite(motorPin2,HIGH);
     digitalWrite(motorPin3,HIGH);
   }  

    if ((digitalRead(callbtn) == HIGH) && (digitalRead(openLimitSwitch) == HIGH) && (cm > limitCm) && (digitalRead(closeLimitSwitch) == HIGH))
   {
     digitalWrite(motorPin1,LOW);
     digitalWrite(motorPin4,LOW);
     digitalWrite(motorPin2,LOW);
     digitalWrite(motorPin3,LOW);
   }  

   
}



long microSecondsToInches(long microseconds)
{
    return microseconds / 74/2;
}

long microSecondsToCentimeters(long microseconds)
{
   return microseconds /29/2;
}


