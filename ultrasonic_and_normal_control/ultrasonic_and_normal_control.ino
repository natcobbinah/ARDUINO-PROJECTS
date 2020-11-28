#include <Servo.h>
Servo myServo;

const int pingPin=2; //trigger alert pin
const int echoPin=3; //receive distance from obstacle approaching
long duration,distance_inches,distance_cm;

char data = 0;

void setup() 
{
   Serial.begin(9600);
   pinMode(pingPin,OUTPUT);
   pinMode(echoPin,INPUT);
   myServo.attach(4);
   myServo.write(90);

   //Set pins as outputs
    pinMode(8, OUTPUT);//in3
    pinMode(7, OUTPUT);//in2
    pinMode(6, OUTPUT);//in1
    pinMode(9, OUTPUT);//in4
    pinMode(13,OUTPUT);
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
// initialize serial communication at 9600 bits per second:
}

void loop() 
{
  //if some date is sent, reads it and saves in state
  if(Serial.available() > 0)
  {
     data = Serial.read();
     
     Serial.println(data);
  }
   //-------------------------led section---------------------------------------------------------
   if(data == '1')            //Checks whether value of data is equal to 1 
   {
      digitalWrite(13, HIGH);  //If value is 1 then LED turns ON
   }
   
   if(data == '0')       //Checks whether value of data is equal to 0
   {
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF
   }
   //---------------------------------------------------------------------------------------------

//-------------------------------------obstacle avoidance section-------------------------------
   if(data == '7')
   {
   digitalWrite(pingPin,LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin,LOW);
 
   duration=pulseIn(echoPin,HIGH);
   distance_inches = microSecondsToInches(duration);
   distance_cm     = microSecondsToCentimeters(duration);

   Serial.println("moving in the forward direction"); //forward
   digitalWrite(7, 180);
   digitalWrite(9, 180);
   digitalWrite(6, 0);
   digitalWrite(8, 0);
   delay(1);
   digitalWrite(9, 180);
   digitalWrite(7, 180);
   digitalWrite(6, 0);
   digitalWrite(8, 0);
   //--------------------------------------------------------

   Serial.print(distance_inches);
   Serial.print("in,");
   
   Serial.print(distance_cm);
   Serial.print("cm");
   delay(2000);
   Serial.println();

  
   if(distance_cm <= 150)
   {
     Serial.println("stop");
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     delay(1000);
     //--------------------------------------------------------

     myServo.write(180); //turn left
     digitalWrite(pingPin,LOW);
     delayMicroseconds(2);
     digitalWrite(pingPin,HIGH);
     delayMicroseconds(10);
     digitalWrite(pingPin,LOW);
     int durationAtLeft = pulseIn(echoPin,HIGH);
     int distanceAtLeft = microSecondsToCentimeters(durationAtLeft);
     Serial.println("Object availability at left side");
     Serial.println(distanceAtLeft);
     delay(3000);

     myServo.write(0); //turn right
     digitalWrite(pingPin,LOW);
     delayMicroseconds(2);
     digitalWrite(pingPin,HIGH);
     delayMicroseconds(10);
     digitalWrite(pingPin,LOW);
     int durationAtRight = pulseIn(echoPin,HIGH);
     int distanceAtRight = microSecondsToCentimeters(durationAtRight);
     Serial.println("Object availability at right side");
     Serial.println(distanceAtRight);
     delay(3000);

     //now compare values, the one with the longest range to hit an object is moved in its direction
     if(distanceAtLeft > distanceAtRight)
     {
      Serial.println("Move in the left direction");
      //left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 
      myServo.write(90);
     }

     if(distanceAtLeft < distanceAtRight)
     {
      Serial.println("Move in the right direction");
      //right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 
      myServo.write(90);
     }
   }
  }

 //----------------normal control section---------------------------------------------
 if(data =='2')
   {
     //backward
     digitalWrite(8, 180);
     digitalWrite(6, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);
     delay(1000); 
   }

     if(data =='3')
   {
     //forward
     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1);
     digitalWrite(9, 180);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
      
   }

     if(data =='4')
   {
     //stop
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     delay(1000); 
   }

       if(data =='5')
   {
     //left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 
   }

        if(data =='6')
   {
     //right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 
   }
 //--------------------------------------------------------------------------------------------------------------------------
  
}


long microSecondsToInches(long microseconds)
{
    return microseconds / 74/2;
}

long microSecondsToCentimeters(long microseconds)
{
   return microseconds /29/2;
}

