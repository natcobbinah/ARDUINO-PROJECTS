#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 2

LiquidCrystal lcd(7,6,5,4,3,2);

DHT dht;

void setup()
{
  lcd.begin(16,2);
  dht.setup(8);
   Serial.begin(9600);
  Serial.println();
  Serial.println("Status\t\tHumidity (%)\t Temperature (C)\t (F) \t Dewpoint");
}

void loop() 
{
 delay(1000);

 float humidity = dht.getHumidity();

 float temperature = dht.getTemperature();

 float dewpoint = calculateDewpoint(temperature,humidity);

 Serial.print(dht.getStatusString());
  Serial.print("\t\t\t");
  Serial.print(humidity,1);
  Serial.print("\t\t");
  Serial.print(temperature,1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature),1);
  Serial.print("\t");
  Serial.print(dewpoint);

 if(isnan(humidity) || isnan(temperature)){
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Error");
  return;
 }

 lcd.setCursor(0,0);
 lcd.print(temperature);
 lcd.setCursor(0,1);
 lcd.print(humidity);
}

float calculateDewpoint(float T, float RH)
 {
  //approximate dew point using the formula from wikipedia's article on dewpoint
  float dp =0.0;

  float gTRH = 0.0;

  float a = 17.271;
  float b = 237.7;

  gTRH = ((a*T)/(b+T)) + log(RH/100);
  dp = (b*gTRH)/(a-gTRH);

  return dp;
 }
