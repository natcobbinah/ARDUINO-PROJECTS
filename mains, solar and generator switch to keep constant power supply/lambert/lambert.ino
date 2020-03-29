#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);
int mains=A0;
int generator=A1;
int solar=A2;
int Main=7;
int Generator=6;
int Solar=5;

void setup() {
  pinMode(mains,INPUT);
  pinMode(generator, INPUT);
  pinMode(solar, INPUT);
  pinMode(Main,OUTPUT);
  pinMode(Generator,OUTPUT);
  pinMode(Solar,OUTPUT);
  lcd.begin(20,2);
  lcd.setCursor(0,0);
  lcd.print("welcome");
}

void loop() {

//-----------------------------------------------MAINS--------------------------------------------------------//
if( (digitalRead(mains)==HIGH) && ((digitalRead(generator)==HIGH)&& (digitalRead(solar)==HIGH) ))
{
  digitalWrite(Main,HIGH);
  digitalWrite(Generator,LOW);
  digitalWrite(Solar,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MAINS ON");
}

else if((digitalRead(mains)==HIGH) && ((digitalRead(generator)==HIGH) || (digitalRead(solar)==HIGH) ))
{
  digitalWrite(Main,HIGH);
  digitalWrite(Generator,LOW);
  digitalWrite(Solar,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MAINS ON");
}

else if( (digitalRead(mains)==HIGH) && ((digitalRead(generator)== LOW)|| (digitalRead(solar)==HIGH) ))
{
  digitalWrite(Main,HIGH);
  digitalWrite(Generator,LOW);
  digitalWrite(Solar,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MAINS ON");
}

else if( (digitalRead(mains)==HIGH) && ((digitalRead(generator)== HIGH)|| (digitalRead(solar)==LOW) ))
{
  digitalWrite(Main,HIGH);
  digitalWrite(Generator,LOW);
  digitalWrite(Solar,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MAINS ON");
}
//------------------------------SOLAR ------------------------------------------------------------------------------

else if( (digitalRead(mains)== LOW) && ((digitalRead(generator)== HIGH)&& (digitalRead(solar)==HIGH) ))
{
  digitalWrite(Main,LOW);
  digitalWrite(Generator,LOW);
  digitalWrite(Solar,HIGH);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SOLAR ON");
}

//---------------------------------GENERATOR---------------------------------------------------------------------------

else if( (digitalRead(mains)== LOW) && (digitalRead(generator)== HIGH) && (digitalRead(solar)== LOW))
{
  digitalWrite(Main,LOW);
  digitalWrite(Generator,HIGH);
  digitalWrite(Solar,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GENERATOR ON");
}
}
