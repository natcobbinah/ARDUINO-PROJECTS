#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd(13,12,11,10,9,8);

//-------------THERMISTOR DECLARATION AND FUNCTIONS-------------------------------------------------------------------
float A=1.009249522e-03, B=2.378405444e-04,C=2.019202697e-07;
float logRt,R2,T,Tc,Tf;

float thermistor(int Vo)
{
   logRt = log(10000.0 * ((1024.0/Vo- 1)));

   T = (1.0/ (A + B*logRt + C*logRt*logRt*logRt)); //We get the temperature in Kelvin from this stein-Hart equation

   Tc = T - 273.15; //Convert Kelvin to Celcius

   Tf = (Tc *1.8) + 32.0; //Convert Kelvin to Fahrenheit

   return T;
}
//---------------------------------------------------------------------------------------------------------------------


//-------------PUMP ACTUATORS--------------------------
int motorPin1=7;
int motorPin2=6;
int motorPin3=5;
int motorPin4=4;
//-----------------------------------------------------


//------------FLOW RATE  SENSORS-----------------------
int val;
int senseFLowRatePin = A1;
//-----------------------------------------------------

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();

  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorPin3,OUTPUT);
  pinMode(motorPin4,OUTPUT);
}

void loop() 
{
    lcd.setCursor(0,0);
    lcd.print("Temp");
    Serial.print("Temp");
    lcd.print(thermistor(analogRead(A0)));
    Serial.print(thermistor(analogRead(A0)));
    lcd.print("k");
    Serial.print("k");

    lcd.setCursor(0,1);
    lcd.print(Tc);
    Serial.println(Tc);
    lcd.print("C");
    Serial.print("C");

    lcd.setCursor(9,1);
    lcd.print(Tf);
    Serial.print(Tf);
    lcd.print("F");
    Serial.print("F");

    //--------------------FLOW RATE SENSOR--------------
     val = analogRead(senseFLowRatePin);
     float mv= (val/1024.0)*5000;
     float Tcel = mv/10;
     float Tfarht= (Tcel*9)/5 + 32;

     Serial.println("SensorRate");
     Serial.print(Tcel);
     delay(800);
    //--------------------------------------------------

    if(Tc > 95.00)
    {
      digitalWrite(motorPin1,HIGH);
      digitalWrite(motorPin4,HIGH);
    }

    if((Tc > 95.00) && (Tcel >= 21))
    {
      digitalWrite(motorPin1,LOW);
      digitalWrite(motorPin4,LOW);
      Serial.println("Volume of Water required is ok");
    }
}
