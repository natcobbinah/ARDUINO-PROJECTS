//Motor A
//const int motorPin1 = 8;
//const int motorPin2 = 7;
//Motor B
//const int motorPin3 = 6;
//const int motorPin4 = 5;

int data;
int flag=0; //makes sure that the serial only prints once the state
int stateStop=0;
void setup() {
//Set pins as outputs
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(13,OUTPUT);
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
}
void loop() {
//if some date is sent, reads it and saves in state
if(Serial.available() > 0){
  data = Serial.read();
  flag=0;

  //-------------------------------------------------------
   if(data == '1')            //Checks whether value of data is equal to 1 
   {
      digitalWrite(13, HIGH);  //If value is 1 then LED turns ON
   }
   
   if(data == '0')       //Checks whether value of data is equal to 0
   {
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF
   }
   
   if(data =='2')
   {
     //forward
     digitalWrite(6, 180);
     digitalWrite(8, 180);
     digitalWrite(7, 0);
     digitalWrite(9, 0);
     delay(1000); 
   }

     if(data =='3')
   {
     //backward
     digitalWrite(9, 180);
     digitalWrite(7, 180);
     digitalWrite(6, 0);
     digitalWrite(8, 0);
     delay(1000); 
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
  }
}





