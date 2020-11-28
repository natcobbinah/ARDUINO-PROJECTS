const int alarmPin=8;
const int gasPin = 7;

const int valve1Pin=3;
const int valve2Pin=2;

#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,6);

#define TONE_FREQUENCY 280

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

char companyNumber[]="+2333354666";

void setup() {
  Serial.begin(9600);
  pinMode(alarmPin,OUTPUT);
  pinMode(gasPin,INPUT);

  pinMode(valve1Pin,OUTPUT);
  pinMode(valve2Pin,OUTPUT);

  lcd.begin(20,2);
}

void loop() {
    //gpsLocation();
    delay(100);
  
    if(digitalRead(gasPin) == HIGH)
    {
    digitalWrite(alarmPin,HIGH);
    tone(alarmPin,TONE_FREQUENCY);

    digitalWrite(valve1Pin,HIGH);
    digitalWrite(valve2Pin,HIGH);
    sendsmsMessage();
    }


    if(digitalRead(gasPin) == LOW)
    {
       digitalWrite(valve1Pin,LOW);
       digitalWrite(valve2Pin,LOW);
    } 
    Serial.print("");
    //delay(3000);
}

void sendsmsMessage()
{
  lcd.setCursor(0,0);
  lcd.print("Phone No:");
  lcd.setCursor(9,0);
  lcd.print(companyNumber);
  
  lcd.setCursor(0,1);
  lcd.print("gas leakage");
//  Serial.print("AT");
//  Serial.println("AT+CMGF=1");
//  Serial.println("AT+CMGS");
//  Serial.println(companyNumber);
//  Serial.println("There is a gas leakage");
} 
