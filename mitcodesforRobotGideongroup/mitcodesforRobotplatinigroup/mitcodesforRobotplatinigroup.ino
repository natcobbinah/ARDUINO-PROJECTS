//-------ultrasonic codes-------------
const int triggerpin = 18;//trigger alert pin
const int echopin    = 17;//receive distance from obstacle approaching
long duration,distance_inches,distance_cm;

//----------signal leds--------------
const int leftledwh  = 2;
const int rightledwh = 13;

const int leftledred  = 3;
const int rightledred = 10;

const int leftledgrn  = 4;
const int rightledgrn = 5;
//-----------------------------------
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

//--------signalling leds--------------
pinMode(leftledwh,OUTPUT);
pinMode(rightledwh,OUTPUT);
pinMode(leftledred,OUTPUT);
pinMode(rightledred,OUTPUT);
pinMode(leftledgrn,OUTPUT);
pinMode(rightledgrn,OUTPUT);

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
      digitalWrite(leftledwh, HIGH);  //If value is 1 then LED turns ON
      digitalWrite(rightledwh, HIGH);
      digitalWrite(leftledred, HIGH);  //If value is 1 then LED turns ON
      digitalWrite(rightledred, HIGH);
      digitalWrite(leftledgrn, HIGH);  //If value is 1 then LED turns ON
      digitalWrite(rightledgrn, HIGH);
   }
   
   if(data == '0')       //Checks whether value of data is equal to 0
   {
      digitalWrite(leftledwh, LOW);  
      digitalWrite(rightledwh, LOW);
      digitalWrite(leftledred, LOW);  
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn, LOW); 
      digitalWrite(rightledgrn, LOW);
   }
   
   if(data =='2')
   {
     //backward
     digitalWrite(8, 180);
     digitalWrite(6, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);
     delay(1000); 

      digitalWrite(leftledwh, LOW);  
      digitalWrite(rightledwh, LOW);
      digitalWrite(leftledred, HIGH);  
      digitalWrite(rightledred, HIGH);
      digitalWrite(leftledgrn, LOW); 
      digitalWrite(rightledgrn, LOW);
  
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
     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

     
      digitalWrite(leftledwh, LOW);  
      digitalWrite(rightledwh, LOW);
      digitalWrite(leftledred,  LOW);  
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn,  HIGH); 
      digitalWrite(rightledgrn, HIGH);


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

      digitalWrite(leftledwh, HIGH);  
      delay(100);
      digitalWrite(leftledwh, LOW);  
      delay(100);
      digitalWrite(rightledwh, HIGH);
      delay(100);
      digitalWrite(rightledwh, LOW);
      delay(100);
      digitalWrite(leftledred,  HIGH);  
      delay(100);
      digitalWrite(leftledred,  LOW);  
      delay(100);
      digitalWrite(rightledred, HIGH);
      delay(100);
      digitalWrite(rightledred, LOW);
      delay(100);
      digitalWrite(leftledgrn,  HIGH);
      delay(100); 
      digitalWrite(leftledgrn,  LOW);
      delay(100); 
      digitalWrite(rightledgrn, HIGH);
      delay(100);
      digitalWrite(rightledgrn, LOW);
   }

       if(data =='5')
   {
     //left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 

      digitalWrite(leftledwh, LOW);  
      digitalWrite(rightledwh, LOW);
      digitalWrite(leftledred,  LOW);  
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn,  HIGH); 
      digitalWrite(rightledgrn, LOW);
     
   }

        if(data =='6')
   {
     //right
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 

      digitalWrite(leftledwh, LOW);  
      digitalWrite(rightledwh, LOW);
      digitalWrite(leftledred,  LOW);  
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn,  LOW); 
      digitalWrite(rightledgrn, HIGH);
    
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





