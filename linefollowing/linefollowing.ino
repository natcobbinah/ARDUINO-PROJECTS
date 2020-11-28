int left_infrared  =14;
int right_infrared =15;

int storeleft_infraredvalue;
int storeright_infraredvalue;

char data=0;

void setup() 
{
    //Set pins as outputs
    pinMode(8, OUTPUT);//in3
    pinMode(7, OUTPUT);//in2
    pinMode(6, OUTPUT);//in1
    pinMode(9, OUTPUT);//in4
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    pinMode(left_infrared,INPUT);
    pinMode(right_infrared,INPUT);

    digitalWrite(left_infrared,HIGH);
    digitalWrite(right_infrared,HIGH);
}

void loop() 
{
  //if some date is sent, reads it and saves in state
  if(Serial.available() > 0)
  {
    data = Serial.read();
    Serial.println(data);
  }
  

   if(data =='8')
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

     //--------------CHECKING INFRARED RESPONSE---------------------
     while(true)
     {
       storeleft_infraredvalue   = digitalRead(left_infrared);
       storeright_infraredvalue  = digitalRead(right_infrared);

       if((storeleft_infraredvalue == 0) && (storeright_infraredvalue == 1) == true)
       {
        //turn left
        turnLeft();
       }

       else if((storeright_infraredvalue == 0) && (storeleft_infraredvalue == 1) == true)
       {
        //turn right
        turnRight();
       }
     }
   }
}

   void turnLeft()
   {
    //left
     digitalWrite(9, 180);
     digitalWrite(7, 0);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 

     while(storeleft_infraredvalue == 0)
     {
        storeleft_infraredvalue   = digitalRead(left_infrared);
        storeright_infraredvalue  = digitalRead(right_infrared);

        if(storeright_infraredvalue == 0)
        {
          int leftprevious  = storeleft_infraredvalue;
          int rightprevious = storeright_infraredvalue;

          //stop
          stopMovement();
          
          while((leftprevious == storeleft_infraredvalue) && (rightprevious == storeright_infraredvalue) == true)
          {
             storeleft_infraredvalue   = digitalRead(left_infrared);
             storeright_infraredvalue  = digitalRead(right_infrared);
          }
        }
           //forward
          digitalWrite(7, 180);
          digitalWrite(9, 180);
          digitalWrite(6, 0);
          digitalWrite(8, 0);
          delay(1);
     }        
   }

   void turnRight()
   {
      //right
      digitalWrite(9, 0);
      digitalWrite(7, 180);
      digitalWrite(6, 0);
      digitalWrite(8, 0);
      delay(1000); 

      while(storeright_infraredvalue == 0)
      {
         storeleft_infraredvalue   = digitalRead(left_infrared);
         storeright_infraredvalue  = digitalRead(right_infrared);

         if(storeleft_infraredvalue == 0)
         {
            int leftprevious  = storeleft_infraredvalue;
            int rightprevious = storeright_infraredvalue;

            //stop
            stopMovement();
            
            while((leftprevious == storeleft_infraredvalue) && (rightprevious == storeright_infraredvalue) && true)
            {
                storeleft_infraredvalue   = digitalRead(left_infrared);
                storeright_infraredvalue  = digitalRead(right_infrared);
            }
         }
          //forward
          digitalWrite(7, 180);
          digitalWrite(9, 180);
          digitalWrite(6, 0);
          digitalWrite(8, 0);
          delay(1);
      }
   }


   void stopMovement()
   {
      //stop
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     digitalWrite(9, 0);
     digitalWrite(7, 0);
     delay(1); 
   }

