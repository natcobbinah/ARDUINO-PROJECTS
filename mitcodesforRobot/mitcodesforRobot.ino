//-------ultrasonic codes-------------
const int triggerpin = 2;//trigger alert pin
const int echopin    = 3;//receive distance from obstacle approaching
long duration,distance_inches,distance_cm;

char data=0;
void setup() {

//------------ultrasonic codes
pinMode(triggerpin,OUTPUT);
pinMode(echopin,INPUT);
  
//Set pins as outputs
    pinMode(8, OUTPUT);//in3
    pinMode(7, OUTPUT);//in2
    pinMode(6, OUTPUT);//in1
    pinMode(9, OUTPUT);//in4
    pinMode(13,OUTPUT);
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
}
void loop() {
//if some date is sent, reads it and saves in state
if(Serial.available() > 0)
{
  data = Serial.read();
  
  Serial.println(data);
}

  //-------------------------------------------------------
   if(data == '1')            //Checks whether value of data is equal to 1 
   {
     digitalWrite(13,HIGH);
   }
   
   if(data == '0')       //Checks whether value of data is equal to 0
   {
     digitalWrite(+13,LOW);
   }
   
   if(data =='2')
   {
     //backward
     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
   }

     if(data =='3')
   {
   digitalWrite(triggerpin,LOW);
   delayMicroseconds(2);
   digitalWrite(triggerpin,HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerpin,LOW);
 
   duration=pulseIn(echopin,HIGH);
   distance_inches = microSecondsToInches(duration);
   distance_cm     = microSecondsToCentimeters(duration);

     //forward
     digitalWrite(8, 180);
     digitalWrite(6, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);

     if(distance_cm <= 23)
     {
      //stop
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     }
 
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
   }

        if(data =='6')
   {
     //right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
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





