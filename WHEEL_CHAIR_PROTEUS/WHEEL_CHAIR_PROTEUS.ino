const int pingPin=2; //trigger alert pin
const int echoPin=3; //receive distance from obstacle approaching
long duration,inches,cm;
int limitCm=560;

//-------------activate controls-------------
int activate_stick = 16;
int activate_phone = 17;
int stop_btn = 18;
//-------------------------------------------

//--------------joystick control-------------
int downJoystick = 10;
int leftJoystick = 11;
int upJoystick = 12;
int rightJoystick = 13;
//------------------------------------------

//--------------phone control----------------
int fwdbtnctrl = 5;
int bckwrdbtnctrl = 4;
int lftbtnctrl = 14;
int rghtbtnctrl = 15;
//-------------------------------------------

void setup() 
{
   Serial.begin(9600);
   pinMode(pingPin,OUTPUT);
   pinMode(echoPin,INPUT);

   //----------------------TYRES-----------------
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
   //--------------------------------------------

   //-----------JOYSTICK MODULE------------------
    pinMode(downJoystick,INPUT);
    pinMode(leftJoystick,INPUT);
    pinMode(upJoystick,INPUT);
    pinMode(rightJoystick,INPUT);
   //--------------------------------------------

   //-----------PHONE CONTROL--------------------
    pinMode(fwdbtnctrl,INPUT);
    pinMode(bckwrdbtnctrl,INPUT);
    pinMode(lftbtnctrl,INPUT);
    pinMode(rghtbtnctrl,INPUT);
   //--------------------------------------------

   //------------ACTIVATE CONTROLS---------------
    pinMode(activate_stick,INPUT);
    pinMode(activate_phone,INPUT);
   //--------------------------------------------
}

void loop()
{

   digitalWrite(pingPin,LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin,LOW);

   duration=pulseIn(echoPin,HIGH);
   cm     = microSecondsToCentimeters(duration);

   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   checklimit();
   delay(100);

  //---------------STOP MOTOR MOVEMENT----------------------------
  if(digitalRead(stop_btn) == HIGH)
  {
     digitalWrite(6,LOW);
     digitalWrite(7,LOW);
     digitalWrite(8,LOW);
     digitalWrite(9,LOW);
  }
  //--------------------------------------------------------------
   
  //----------------PHONE CONTROL---------------------------------
if(digitalRead(activate_phone) == HIGH)
{  
   Serial.println("PHONE CONTROL ACTIVATED");
   if(digitalRead(fwdbtnctrl) == HIGH)
   {
     checklimit();
     digitalWrite(6,HIGH);
     digitalWrite(7,LOW);
     digitalWrite(8,LOW);
     digitalWrite(9,HIGH);
   }

   if(digitalRead(bckwrdbtnctrl) == HIGH)
   {
     digitalWrite(6,LOW);
     digitalWrite(7,HIGH);
     digitalWrite(8,HIGH);
     digitalWrite(9,LOW);
   }

   if(digitalRead(lftbtnctrl) == HIGH)
   {
     digitalWrite(6,HIGH);
     digitalWrite(7,LOW);
     digitalWrite(8,LOW);
     digitalWrite(9,LOW);
   }

   if(digitalRead(rghtbtnctrl) == HIGH)
   {
     digitalWrite(6,LOW);
     digitalWrite(7,LOW);
     digitalWrite(8,LOW);
     digitalWrite(9,HIGH);
   }
}
   //--------------------------------------------------------------

   //------------JOYSTICK CONTROL----------------------------------
if(digitalRead(activate_stick) == HIGH)
{
    Serial.println("JOYSTICK CONTROL ACTIVATED");
    if(digitalRead(downJoystick) == HIGH)
    {
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
    }

     if(digitalRead(leftJoystick) == HIGH)
    {
       digitalWrite(6,HIGH);
       digitalWrite(7,LOW);
       digitalWrite(8,LOW);
       digitalWrite(9,LOW);
    }

     if(digitalRead(upJoystick) == HIGH)
    {
       checklimit();
       digitalWrite(6,HIGH);
       digitalWrite(7,LOW);
       digitalWrite(8,LOW);
       digitalWrite(9,HIGH);
    }

     if(digitalRead(rightJoystick) == HIGH)
    {
       digitalWrite(6,LOW);
       digitalWrite(7,LOW);
       digitalWrite(8,LOW);
       digitalWrite(9,HIGH);
    }
}
   //--------------------------------------------------------------
}

void checklimit()
{
  if(cm < limitCm)
  {
     digitalWrite(6,LOW);
     digitalWrite(7,LOW);
     digitalWrite(8,LOW);
     digitalWrite(9,LOW);
  }
}

long microSecondsToCentimeters(long microseconds)
{
   return microseconds /29/2;
}
