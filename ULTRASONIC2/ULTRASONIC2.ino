
const int pingPin=10; //trigger alert pin
const int echoPin=11; //receive distance from obstacle approaching
long duration,inches,cm;
int limitCm=23;

void setup() 
{
   Serial.begin(9600);
   pinMode(pingPin,OUTPUT);
   pinMode(echoPin,INPUT);
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

   Serial.print(inches);
   Serial.print("in,");
   
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   checklimit();
   delay(100);

}

void checklimit()
{
  if(cm <= checklimit)
  {
     Serial.print("stop");
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


