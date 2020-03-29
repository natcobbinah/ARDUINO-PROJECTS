#include <LiquidCrystal.h>

LiquidCrystal lcd(8,7,6,5,4,3);

String docsNo="+233244520044";

int pulseRead = 2;

int pulseReadled=12;

int sendMsgled = 11;

int startPulseReadSystem=10;

int resetPulseReadSystem=9;

int count=0,i=0,k=0,rate=0;

unsigned long timer2_time,timer1_time;

unsigned long time;

byte heart[8]=
{
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() 
{
 Serial.begin(9600);

 lcd.createChar(1,heart);
 lcd.begin(16,2);
 lcd.write(1);
 lcd.setCursor(0,1);
 lcd.print("TAKE PULSE READING");

 pinMode(pulseReadled,OUTPUT);
 pinMode(sendMsgled,OUTPUT); 
 pinMode(pulseRead,INPUT);
 pinMode(startPulseReadSystem,INPUT);
 pinMode(resetPulseReadSystem,INPUT);

 digitalWrite(resetPulseReadSystem,HIGH);
 digitalWrite(startPulseReadSystem,HIGH);

 digitalWrite(pulseReadled, LOW);
 digitalWrite(sendMsgled,LOW);
 
 delay(1000);
}

void loop()
{
 if(!(digitalRead(startPulseReadSystem)))
 {
  k=0;
  lcd.clear();
  lcd.print("Please wait...........");

  while(k < 5)
  {
    if(digitalRead(pulseRead))
    {
      if(k == 0)
      {
        timer1_time=millis();
        k++;
        while(digitalRead(pulseRead));

        digitalWrite(sendMsgled,LOW);
      }
    }

    timer2_time = millis();
   
    lcd.clear();

    lcd.print("Heart Beat Rate");
    lcd.setCursor(0,1);
    showRateLevel();
    lcd.print(" ");
    lcd.write(1);
    delay(1000);

    k = 0;
    rate = 0;
  }

  if(digitalRead(resetPulseReadSystem))
  {
    rate = 0;
    lcd.clear();
    lcd.print("Heart Beat Rate");
    lcd.setCursor(0,1);
    lcd.write(1);
    showRateLevel();
    k = 0;
  }
 }
}

void showRateLevel()
{
   rate = timer2_time - timer1_time;

   rate = rate/5;
   rate = 60000/rate;

   if(rate > 60 && rate < 100)
    {
       lcd.print(rate);
       lcd.print("BPM-Normal");
       digitalWrite(pulseReadled, HIGH);
       digitalWrite(sendMsgled, LOW);
    }
   else
   {
       lcd.print(rate);
       lcd.print("BPM-Abnormal");
       digitalWrite(pulseReadled, LOW);
       //SENDING MESSAGE TO THE DOCTOR
       digitalWrite(sendMsgled, HIGH);
       Serial.println("AT+CMGF=1");    
       delay(2);
       Serial.print("AT+CMGS=\"");
       Serial.print(docsNo); 
       Serial.write(0x22);
       Serial.write(0x0D);  // hex equivalent of Carraige return    
       Serial.write(0x0A);  // hex equivalent of newline
       delay(2);
       Serial.print("hello");
       delay(2);
       Serial.println (char(26));//the ASCII code of the ctrl+z is 26
   }
}

void pulseReadledFlasher()
{
  digitalWrite(pulseReadled, HIGH);
  delay(10);
  digitalWrite(pulseReadled, HIGH);
}

void sendMsgledFlash()
{
  digitalWrite(sendMsgled, HIGH);
  delay(2);
  digitalWrite(sendMsgled, HIGH);
}

