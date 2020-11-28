//----light indicators-----------------------
const int slgfpin =3;
const int llfpin  =4;
const int llgfpin =5;
const int llgpin  =6;

//-----fault line isolator relays------------
const int isolateRelay1 = 8;
const int isolateRelay2 = 9;
const int isolateRelay3 = 10;

//-----fault trigger pins---------------------
const int triggerFault1 = 2;
const int triggerFault2 = 7;
const int triggerFault3 = 11;
const int triggerFault4 = 12;

//------gps----------------------------------
#include <TinyGPS.h>

TinyGPS gps;

String gpsLocation()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  
  for(unsigned long start = millis(); millis() - start < 1000;);
  {
    while(Serial.available())
   {
     char c = Serial.read();
     if(gps.encode(c))
     newData = true;
   } 
  }
  
  if(newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon,&age);
    Serial.print("Latitude = ");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print("Longitude = ");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  }
  Serial.println("failed");
}

//-----DECLARATION OF VARIABLES END HERE------

char AdminsPhoneno[]="+233435345435";

void setup() 
{
  Serial.begin(9600);
    
  pinMode(slgfpin,OUTPUT);
  pinMode(llfpin,OUTPUT);
  pinMode(llgfpin,OUTPUT);
  pinMode(llgpin,OUTPUT);

  pinMode(triggerFault1,INPUT);
  pinMode(triggerFault2,INPUT);
  pinMode(triggerFault3,INPUT);
  pinMode(triggerFault4,INPUT);

  pinMode(isolateRelay1,OUTPUT);
  pinMode(isolateRelay2,OUTPUT);
  pinMode(isolateRelay3,OUTPUT);

  digitalWrite(isolateRelay1,HIGH);
  digitalWrite(isolateRelay2,HIGH);
  digitalWrite(isolateRelay3,HIGH);
}

void loop() 
{
     
   if(digitalRead(triggerFault1))
   {
     digitalWrite(isolateRelay1,LOW);
     digitalWrite(isolateRelay2,HIGH);
     digitalWrite(isolateRelay3,HIGH);
     digitalWrite(llfpin,HIGH);
     digitalWrite(slgfpin,LOW);
     digitalWrite(llgfpin,LOW);
     digitalWrite(llgpin,LOW);

     Serial.println("It's a Line-line fault problem");
     Serial.println("AT");
     Serial.println("AT+CMGF=1");
     Serial.println("AT+CMGS");
     Serial.println(AdminsPhoneno);
     Serial.println("MessageSent successfully :)");
     Serial.println();
     
     while(digitalRead(triggerFault1));
   }
   delay(500);

   if(digitalRead(triggerFault2))
   {
     digitalWrite(isolateRelay2,LOW);
     digitalWrite(isolateRelay1,HIGH);
     digitalWrite(isolateRelay3,HIGH);
     digitalWrite(llgfpin,HIGH);
     digitalWrite(llfpin,LOW);
     digitalWrite(slgfpin,LOW);
     digitalWrite(llgpin,LOW);

     Serial.println("It's a Line-line ground fault problem");
     Serial.println("AT");
     Serial.println("AT+CMGF=1");
     Serial.println("AT+CMGS");
     Serial.println(AdminsPhoneno);
     Serial.println("MessageSent successfully :)");
     Serial.println();
     
     while(digitalRead(triggerFault2));
   }
   delay(500);

   if(digitalRead(triggerFault3))
   {
     digitalWrite(isolateRelay1,HIGH);
     digitalWrite(isolateRelay2,HIGH);
     digitalWrite(isolateRelay3,LOW);
     digitalWrite(slgfpin,HIGH);
     digitalWrite(llgfpin,LOW);
     digitalWrite(llfpin,LOW);
     digitalWrite(llgpin,LOW);

     Serial.println("It's a Single-line ground fault problem");
     Serial.println("AT");
     Serial.println("AT+CMGF=1");
     Serial.println("AT+CMGS");
     Serial.println(AdminsPhoneno);
     Serial.println("MessageSent successfully :)");
     Serial.println();
     
     while(digitalRead(triggerFault3));
   }
   delay(500);

    if(digitalRead(triggerFault4))
   {
     digitalWrite(isolateRelay1,LOW);
     digitalWrite(isolateRelay2,LOW);
     digitalWrite(isolateRelay3,LOW);
     digitalWrite(slgfpin,LOW);
     digitalWrite(llgfpin,LOW);
     digitalWrite(llfpin,LOW);
     digitalWrite(llgpin,HIGH);

     Serial.println("It's a Line-line ground problem");
     Serial.println("AT");
     Serial.println("AT+CMGF=1");
     Serial.println("AT+CMGS");
     Serial.println(AdminsPhoneno);
     Serial.println("MessageSent successfully :)");
     Serial.println();
     
     while(digitalRead(triggerFault3));
   }
   delay(500);
}
