
#include <LiquidCrystal.h>

LiquidCrystal lcd(9,8,7,6,5,4);
// Number of cycles from external counter needed to generate a signal event
#define CYCLES_PER_SIGNAL 5000

#define vtransformer  A0
#define itransformer  A1

#define powerfactorchange1 7
#define powerfactorchange2 6
#define powerfactorchange3 5
#define powerfactorchange4 4

const int  RELAY_PIN1 = 13;
const int RELAY_PIN2  = 12;
const int RELAY_PIN3  = 11;
const int RELAY_PIN4  = 10;

double theta;
double powerfactor;

double powerfactor1;
double powerfactor2;
double powerfactor3;
double powerfactor4;

unsigned long lastSignalTime = 0;
unsigned long signalTimeDelta = 0;

boolean firstSignal = true;
unsigned long storedTimeDelta = 0;

// This signal is called whenever OCR1A reaches 0
// (Note: OCR1A is decremented on every external clock cycle)
SIGNAL(TIMER1_COMPA_vect)
{
  unsigned long currentTime = micros();
  signalTimeDelta =  currentTime - lastSignalTime;
  lastSignalTime = currentTime;

  if (firstSignal)
  {
    firstSignal = false;
  }
  else if (storedTimeDelta == 0)
  {
    storedTimeDelta = signalTimeDelta;
  }

  // Reset OCR1A
  OCR1A += CYCLES_PER_SIGNAL;
}

void setup() 
{
  
   lcd.begin(20,2);
// Set WGM(Waveform Generation Mode) to 0 (Normal)
  TCCR1A = 0b00000000;
  
//  // Set CSS(Clock Speed Selection) to 0b111 (External clock source on T0 pin
//  // (ie, pin 5 on UNO). Clock on rising edge.)
   TCCR1B = 0b00000111;
   
//  // Enable timer compare interrupt A (ie, SIGNAL(TIMER1_COMPA_VECT))
   TIMSK1 |= (1 << OCIE1A);

//  // Set OCR1A (timer A counter) to 1 to trigger interrupt on next cycle
   OCR1A = 1;
     
  Serial.begin(9600);

  pinMode(RELAY_PIN1,OUTPUT);
  pinMode(RELAY_PIN2,OUTPUT);
  pinMode(RELAY_PIN3,OUTPUT);
  pinMode(RELAY_PIN4,OUTPUT);
  pinMode(vtransformer,INPUT);
  pinMode(itransformer,INPUT);

  pinMode(powerfactorchange1,INPUT);
  pinMode(powerfactorchange2,INPUT);
  pinMode(powerfactorchange3,INPUT);
  pinMode(powerfactorchange4,INPUT);

   phaseDifference();
}


void loop() 
{
  if(digitalRead(powerfactorchange1))
  {
    powerfactor1 = 0.57;
    Serial.print("Now powerfactor is 0.98");
    Serial.println();

    
    lcd.setCursor(0,1);
    lcd.print("Powerfactor: ");
    lcd.print(powerfactor1);
  
   if(powerfactor1 == 0.57)
   {
    digitalWrite(RELAY_PIN1,HIGH);
    digitalWrite(RELAY_PIN2,HIGH);
    digitalWrite(RELAY_PIN3,HIGH); 
    digitalWrite(RELAY_PIN4,HIGH);
  }
  while(digitalRead(powerfactorchange1));
}

delay(1000);

if(digitalRead(powerfactorchange2))
{
    powerfactor2 = 0.68;
    Serial.print("Now powerfactor is 0.98");
    Serial.println();

    
    lcd.setCursor(0,1);
    lcd.print("Powerfactor: ");
    lcd.print(powerfactor2);
    
   if(powerfactor2 ==  0.68)
   {
    digitalWrite(RELAY_PIN1,HIGH);
    digitalWrite(RELAY_PIN2,HIGH);
    digitalWrite(RELAY_PIN3,HIGH); 
    digitalWrite(RELAY_PIN4,LOW);
   }
   while(digitalRead(powerfactorchange2));
}

delay(1000);


if(digitalRead(powerfactorchange3))
{
    powerfactor3 = 0.74;
     Serial.print("Now powerfactor is 0.98");
    Serial.println();

    lcd.setCursor(0,1);
    lcd.print("Powerfactor: ");
    lcd.print(powerfactor3);
     
    if(powerfactor3 == 0.74)
    {
    digitalWrite(RELAY_PIN1,HIGH);
    digitalWrite(RELAY_PIN2,HIGH);
    digitalWrite(RELAY_PIN3,LOW); 
    digitalWrite(RELAY_PIN4,LOW);
    }
    while(digitalRead(powerfactorchange3));
}

delay(1000);


if(digitalRead(powerfactorchange4))
{
    powerfactor4 = 0.83;
    Serial.print("Now powerfactor is 0.98");
    Serial.println();

    
    lcd.setCursor(0,1);
    lcd.print("Powerfactor: ");
    lcd.print(powerfactor4);
    
    if(powerfactor4 == 0.83)
    {
    digitalWrite(RELAY_PIN1,HIGH);
    digitalWrite(RELAY_PIN2,LOW);
    digitalWrite(RELAY_PIN3,LOW); 
    digitalWrite(RELAY_PIN4,LOW);
    }
    while(digitalRead(powerfactorchange4));
}

delay(1000);


if(powerfactor > 0.98)
  {
    
    lcd.setCursor(0,1);
    lcd.print("Powerfactor: ");
    lcd.print(powerfactor);
    
    digitalWrite(RELAY_PIN2,LOW);
    digitalWrite(RELAY_PIN1,LOW);
    digitalWrite(RELAY_PIN3,LOW); 
    digitalWrite(RELAY_PIN4,LOW);
  }
}

void phaseDifference()
{
  int voltransformervalue = mapFloat(analogRead(vtransformer), 0, 1023, 0.5, 10.0);

  int itransformervalue = mapFloat(analogRead(itransformer), 0, 1023, 0.5, 10.0);

  theta = (240) / 2*3.142;
  powerfactor =cos(theta);


  Serial.print("Powerfactor=");
  Serial.print(powerfactor);
  Serial.println();

  lcd.setCursor(0,1);
  lcd.print("Powerfactor: ");
  lcd.print(powerfactor);
}

float mapFloat(int input, int inMin, int inMax, float outMin, float outMax)
{
  float scale = (float)(input - inMin) / (inMax - inMin);
  return ((outMax - outMin) * scale) + outMin;
}


