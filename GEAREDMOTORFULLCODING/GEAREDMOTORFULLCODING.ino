const int pingPin=10; //trigger alert pin
const int echoPin=11; //receive distance from obstacle approaching
long duration,inches,cm;
int limitCm=100;

//----ledpin indicator
const int redLedPin=12;

//Motor A
const int motorPin1 = 8;
const int motorPin2 = 7;
//Motor B
const int motorPin3 = 6;
const int motorPin4 = 5;

void
setup()
{
   Serial.begin(9600);
   pinMode(pingPin,OUTPUT);
   pinMode(echoPin,INPUT);
   pinMode(redLedPin,OUTPUT);
  
  //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4

    digitalWrite(redLedPin,LOW);
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
   checklimit();
   delay(100);
  
   forwardStep();

}

void forwardStep()
{
    //This code  will turn Motor A clockwise for 2 sec.
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 180);
    analogWrite(motorPin4, 0);
    delay(5000); 

    //This code will turn Motor B clockwise for 2 sec.
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
    analogWrite(motorPin3, 180);
    analogWrite(motorPin4, 0);
    delay(1000); 
}


void BackwardStep()
{
    //This code  will turn Motor A  and B backward.
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);
}

void leftStep()
{
     //This code  will turn Motor A  forward and B backward.
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
    analogWrite(motorPin3, 180);
    analogWrite(motorPin4,  0);
}

void rightStep()
{
     //This code  will turn Motor A  forward and B backward.
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);
}

void stopStep()
{
    //And this code will stop motors
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
}

void checklimit()
{
  if(cm < checklimit)
  {
     Serial.print("stop");
     digitalWrite(redLedPin,HIGH);
  }
  else
  {
      digitalWrite(redLedPin,LOW);
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





