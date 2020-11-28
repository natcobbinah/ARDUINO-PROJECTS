#include <DHT.h>

// Interfacing Arduino with DHT11 humidity and temperature sensor
 
// include LCD library code
#include <LiquidCrystal.h>
// include DHT library code
 
#define DHTPIN 8          // DHT11 data pin is connected to Arduino pin 8

 DHT dht;
// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
char temperature[] = "Temp = 00.0 C  ";
char humidity[]    = "RH   = 00.0 %  ";
void setup() {
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  dht.setup(DHTPIN);
}
 
void loop() {
  delay(1000);           // wait 1s between readings
  // Read humidity
  byte RH = dht.getHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.getTemperature();
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(RH) || isnan(Temp)) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error");
    return;
  }
 
  temperature[7]     = Temp / 10 + 48;
  temperature[8]     = Temp % 10 + 48;
  temperature[11]    = 223;
  humidity[7]        = RH / 10 + 48;
  humidity[8]        = RH % 10 + 48;
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);
}


