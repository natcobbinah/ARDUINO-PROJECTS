#include <Servo.h>
Servo myServo;

//---------light indicators---------------------------------------------
unsigned int blueleft=19;
unsigned int redleft=18;

unsigned int yellowleft=17;
unsigned int yellowright=16;

unsigned int whiteright=13;
unsigned int whiteright2=12;

//--------------ultrasonic sensor---------------------------------------

unsigned int pingPin=10; //trigger alert pin
unsigned int echoPin=11; //receive distance from obstacle approaching
long duration,distance_inches,distance_cm;
//-----------------------------------------------------------------------

char data = 0; // variable to store serial input

//--------------photodiode declarations----------------------------------
unsigned int left_infrared  =14;
unsigned int right_infrared =15;

//unsigned int storeleft_infraredvalue;
//unsigned int storeright_infraredvalue;
//-----------------------------------------------------------------------

void setup() 
{
   Serial.begin(9600);
   pinMode(pingPin,OUTPUT);
   pinMode(echoPin,INPUT);
   myServo.attach(2);
   myServo.write(90);

   //Set pins as outputs
    pinMode(8, OUTPUT);//in3
    pinMode(7, OUTPUT);//in2
    pinMode(6, OUTPUT);//in1
    pinMode(9, OUTPUT);//in4
    pinMode(13,OUTPUT);

    pinMode(blueleft,OUTPUT);
    pinMode(redleft,OUTPUT);
    pinMode(yellowleft,OUTPUT);
    pinMode(yellowright,OUTPUT);
    pinMode(whiteright,OUTPUT);
    pinMode(whiteright2,OUTPUT);
    //----------------------------------------------------------------------------
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
    // initialize serial communication at 9600 bits per second:

    //--------ir sensors initialization
    pinMode(left_infrared,INPUT);
    pinMode(right_infrared,INPUT);
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
    digitalWrite(blueleft,HIGH);
    digitalWrite(redleft,HIGH);
    digitalWrite(yellowleft,HIGH);
    digitalWrite(yellowright,HIGH);
    digitalWrite(whiteright,HIGH);
    digitalWrite(whiteright2,HIGH);
   }
   
   if(data == '0')       //Checks whether value of data is equal to 0
   {
    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright2,LOW);
   }
   //---------------------------------------------------------------------------------------------

    //----------------normal control section---------------------------------------------
   if(data =='2')
   {
     //backward
     digitalWrite(8, 180);
     digitalWrite(6, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,HIGH);
    digitalWrite(yellowright,HIGH);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright2,LOW);
    }

    if(data =='3')
    {
     //forward
     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,HIGH);
    digitalWrite(whiteright,HIGH);
   }

   if(data =='4')
   {
     //stop
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     
    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
    }

   if(data =='5')
   {
     //left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

    digitalWrite(blueleft,HIGH);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
   }

   if(data =='6')
   {
     //right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,HIGH);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
   }
 //--------------------------------------------------------------------------------------------------------------------------
 

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

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,HIGH);
    digitalWrite(yellowright,HIGH);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright2,LOW);
   //--------------------------------------------------------

   Serial.print(distance_inches);
   Serial.print("in,");
   
   Serial.print(distance_cm);
   Serial.print("cm");
   delay(2000);
   Serial.println();

  
   if(distance_cm < 50)
   {
     Serial.println("stop");
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     delay(1000);

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
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

    digitalWrite(blueleft,HIGH);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
    
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

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,HIGH);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);     
     
     delay(1); 
      myServo.write(90);
     }
   }
  }


 //-----------line following--------------------------------------------------------
   if(data =='8')
   {
     if(digitalRead(left_infrared) && digitalRead(right_infrared))  //move forward
     {
         //forward
         digitalWrite(7, 180);
         digitalWrite(9, 180);
         digitalWrite(6, 0);
         digitalWrite(8, 0);

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,HIGH);
    digitalWrite(whiteright,HIGH);
     }


     if(!(digitalRead(left_infrared)) && digitalRead(right_infrared)) //move right
     {
         //right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,HIGH);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
     }


     if(digitalRead(left_infrared) && !(digitalRead(right_infrared))) //move left
     {
        //left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

    digitalWrite(blueleft,HIGH);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
     }


     if(!(digitalRead(left_infrared)) && !(digitalRead(right_infrared))) //stop
     {
        //stop
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     
    digitalWrite(blueleft,LOW);
    digitalWrite(redleft,LOW);
    digitalWrite(yellowleft,LOW);
    digitalWrite(yellowright,LOW);
    digitalWrite(whiteright,LOW);
    digitalWrite(whiteright,LOW);
     }
     
   }
}

//------------------------------------------------------------------------------------------

long microSecondsToInches(long microseconds)
{
    return microseconds / 74/2;
}

long microSecondsToCentimeters(long microseconds)
{
   return microseconds /29/2;
}

