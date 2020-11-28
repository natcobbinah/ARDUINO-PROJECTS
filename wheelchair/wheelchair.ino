#include <JoystickLib.h>

//--------signal leds-----------------------------------------------------
const int leftledred   = 10;
const int leftledblue  = 11;
const int rightledgreen = 12;
const int rightledorange  = 13;
//------------------------------------------------------------------------

//-----------joystick module---------------------------------------------
Joystick stick(A0, A1);
const int SWPIN = 5;

void printPosition() {
  Serial.print(F("X: "));
  Serial.println(stick.getX());
  Serial.print(F("Y: "));
  Serial.println(stick.getY());
  Serial.println();
}

void onUpHandler() {
  Serial.println(F("Direction: Up"));
  printPosition();

     //move geared motors in the forward direction
     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,HIGH);
     digitalWrite(rightledorange,LOW);
}

void onRightUpHandler() {
  Serial.println(F("Direction: Right-Up"));
  printPosition();

     //move geared motors in the forward direction
     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,HIGH);
     digitalWrite(rightledorange,LOW);
}

void onRightHandler() {
  Serial.println(F("Direction: Right"));
  printPosition();

     //-------move geared motor direction to the right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,LOW);
     digitalWrite(rightledgreen,HIGH);
     digitalWrite(rightledorange,HIGH);
}

void onRightDownHandler() {
  Serial.println(F("Direction: Right-Down"));
  printPosition();

     //-------move geared motor direction to the right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,LOW);
     digitalWrite(rightledgreen,HIGH);
     digitalWrite(rightledorange,HIGH);
}

void onDownHandler() {
  Serial.println(F("Direction: Down"));
  printPosition();

     //move geared motors in backward direction
     digitalWrite(8, 180);
     digitalWrite(6, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);

     //--------light indicator-----------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,LOW);
     digitalWrite(rightledorange,LOW);
}

void onLeftDownHandler() {
  Serial.println(F("Direction: Left-Down"));
  printPosition();

     //-----move geared motor direction to the left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,HIGH);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,LOW);
     digitalWrite(rightledorange,LOW);
}

void onLeftHandler() {
  Serial.println(F("Direction: Left"));
  printPosition();

     //-----move geared motor direction to the left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,HIGH);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,LOW);
     digitalWrite(rightledorange,LOW);
}

void onLeftUpHandler() {
  Serial.println(F("Direction: Left-Up"));
  printPosition();

    //-----move geared motor direction to the left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,HIGH);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,LOW);
     digitalWrite(rightledorange,LOW);
}

//-------ultrasonic sensor pins------------------------------------------
const int triggerPin = 2; //trigger alert pin
const int echoPin    = 3; //receive distance from obstacle approaching
long duration, distance_inches,distance_cm;

//-----------------------------------------------------------------------
char data = 0;

void setup() 
{

   //-------for motor controls---------------
  pinMode(6,OUTPUT); //IN1
  pinMode(7,OUTPUT); //IN2
  pinMode(8,OUTPUT); //IN3
  pinMode(9,OUTPUT); //IN4
  
  //-------for joystick module--------------
  pinMode(SWPIN,INPUT);
  digitalWrite(SWPIN,HIGH);
  // Calibrate and print out position.
  Serial.println();
  Serial.print(F("Calibrating.... "));
  stick.calibrate();
  Serial.println(F("Done."));
  Serial.println(F("Calibrated zero position: "));
  printPosition();

  // Wire up event handlers.
  stick.onUp(onUpHandler);
  stick.onRightUp(onRightUpHandler);
  stick.onRight(onRightHandler);
  stick.onRightDown(onRightDownHandler);
  stick.onDown(onDownHandler);
  stick.onLeftDown(onLeftDownHandler);
  stick.onLeft(onLeftHandler);
  stick.onLeftUp(onLeftUpHandler);
  
  //-------for ultrasonic sensors------------
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);

  //--Initiallize serial communication at 9600 bits per second-------
  Serial.begin(9600);

  //----Signalling leds----------------------
  pinMode(leftledred,OUTPUT);
  pinMode(leftledblue,OUTPUT);
  pinMode(rightledgreen,OUTPUT);
  pinMode(rightledorange,OUTPUT);
}

void loop() 
{
  //-----------JOYSTICK MODULE------------------------
  // Read joystick and process events every 300ms.
  stick.loop();
  delay(300);
  
  //If some data is sent, reads it  and saves in state
  if(Serial.available() > 0)
  {
    data = Serial.read();
    Serial.println(data);
  }

  if(data == '1')
  {
    digitalWrite(leftledred,HIGH);
    digitalWrite(leftledblue,HIGH);
    digitalWrite(rightledgreen,HIGH);
    digitalWrite(rightledorange,HIGH);
  }

  if(data == '0')
  {
    digitalWrite(leftledred,LOW);
    digitalWrite(leftledblue,LOW);
    digitalWrite(rightledgreen,LOW);
    digitalWrite(rightledorange,LOW);
  }

  if(data == '2')
  {
     //move geared motors in backward direction
     digitalWrite(8, 180);
     digitalWrite(6, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);

     //--------light indicator-----------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,LOW);
     digitalWrite(rightledorange,LOW);
  }

  if(data == '3')
  {
     //start checking the probability of an obstacle while moving bot
     digitalWrite(triggerPin,LOW);
     delayMicroseconds(2);
     digitalWrite(triggerPin,HIGH);
     delayMicroseconds(10);
     digitalWrite(triggerPin,LOW);

     duration        = pulseIn(echoPin,HIGH);
    //, distance_inches = microSecondsToInches(duration);
     distance_cm     = microSecondsToCentimeters(duration);

     //move geared motors in the forward direction
     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,HIGH);
     digitalWrite(rightledorange,LOW);

     //-----stop moving if an obstacle is within this distance
       if(distance_cm < 50)
     {
      //----stop movement of geared motors
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     }
  }

   if(data == '4')
   {
     //--stop movement of geared motors
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,HIGH);
     digitalWrite(leftledblue,LOW);
     digitalWrite(rightledgreen,LOW);
     digitalWrite(rightledorange,HIGH);
   }

   if(data == '5')
   {
    //-----move geared motor direction to the left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,HIGH);
     digitalWrite(leftledblue,HIGH);
     digitalWrite(rightledgreen,LOW);
     digitalWrite(rightledorange,LOW);
   }

   if(data == '6')
   {
     //-------move geared motor direction to the right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     //-------light indicator---------------------------------
     digitalWrite(leftledred,LOW);
     digitalWrite(leftledblue,LOW);
     digitalWrite(rightledgreen,HIGH);
     digitalWrite(rightledorange,HIGH);
   }
}

//----function for converting ultrasonic values to inces and centimeters respectively
//long microSecondsToInches(long microseconds)
//{
//    return microseconds / 74/2;
//}

long microSecondsToCentimeters(long microseconds)
{
   return microseconds /29/2;
}

