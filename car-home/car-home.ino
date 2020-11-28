//-------ultrasonic codes-------------
const int triggerpin = 2;//trigger alert pin
const int echopin    = 3;//receive distance from obstacle approaching
long duration,cm;
int limitCm=560;

//----------signal leds--------------xc  
const int leftledred  = 10;
const int rightledred = 11;

const int leftledgrn  = 12;
const int rightledgrn = 13;
//-----------------------------------
char data=0;
void setup() {

//------------ultrasonic codes
pinMode(triggerpin,OUTPUT);
pinMode(echopin,INPUT);
  
//Set pins as outputs
    pinMode(4, OUTPUT);//in3
    pinMode(5, OUTPUT);//in2
    pinMode(6, OUTPUT);//in1
    pinMode(7, OUTPUT);//in4
    pinMode(13,OUTPUT);
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);

////--------signalling leds--------------
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
      digitalWrite(leftledred, HIGH);  //If value is 1 then LED turns ON
      digitalWrite(rightledred, HIGH);
      digitalWrite(leftledgrn, HIGH);  //If value is 1 then LED turns ON
      digitalWrite(rightledgrn, HIGH);
        digitalWrite(13,HIGH);
   }
   
   if(data == '0')       //Checks whether value of data is equal to 0
   {
      digitalWrite(leftledred, LOW);  
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn, LOW); 
      digitalWrite(rightledgrn, LOW);
      digitalWrite(13,LOW);
   }
   
   if(data =='2')
   {
     //backward
     digitalWrite(8, 180);
     digitalWrite(6, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);
     
     delay(1000); 

     digitalWrite(leftledred, HIGH);  
     digitalWrite(rightledred, HIGH);
     digitalWrite(leftledgrn, LOW); 
     digitalWrite(rightledgrn, LOW);
  
   }

   if(data =='3')
   {
     //forward
//       digitalWrite(triggerpin,LOW);
//       delayMicroseconds(2);
//       digitalWrite(triggerpin,HIGH);
//       delayMicroseconds(10);
//       digitalWrite(triggerpin,LOW);
// 
//       duration=pulseIn(echopin,HIGH);
//       cm     = microSecondsToCentimeters(duration);
//
//       Serial.print(cm);
//       Serial.print("cm");
//       Serial.println();
//       checklimit();
//       delay(100);


     digitalWrite(7, 180);
     digitalWrite(9, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);

      digitalWrite(leftledred,  LOW);  
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn,  HIGH); 
      digitalWrite(rightledgrn, HIGH);

   }

     if(data =='4')
   {
     //stop
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     delay(1000); 

      digitalWrite(leftledred,  HIGH);    
      digitalWrite(rightledred, HIGH);
      digitalWrite(leftledgrn,  HIGH);
      digitalWrite(rightledgrn, HIGH);
      delay(100);
      digitalWrite(leftledred,  LOW);    
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn,  LOW);
      digitalWrite(rightledgrn, LOW);
   }

       if(data =='6')
   {
     //left
     digitalWrite(9, 0);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 

      digitalWrite(leftledred,  LOW);  
      digitalWrite(rightledred, HIGH);
      digitalWrite(leftledgrn,  LOW); 
      digitalWrite(rightledgrn, HIGH);
     
   }

        if(data =='5')
   {
     //right
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 

      digitalWrite(leftledred,  HIGH);  
      digitalWrite(rightledred, LOW);
      digitalWrite(leftledgrn,  HIGH); 
      digitalWrite(rightledgrn, LOW);
    
   }
  }

//
//void checklimit()
//{
//  if(cm < limitCm)
//  {
//     digitalWrite(6,LOW);
//     digitalWrite(7,LOW);
//     digitalWrite(8,LOW);
//     digitalWrite(9,LOW);
//  }
//}
//
//long microSecondsToCentimeters(long microseconds)
//{
//   return microseconds /29/2;
//}





