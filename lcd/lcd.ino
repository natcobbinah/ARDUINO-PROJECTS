/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27

#define BACKLIGHT_PIN 3

#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7



LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);  // set the LCD address to 0x38

void setup()
{
  //pinMode ( BACKLIGHT_PIN, OUTPUT );
  lcd.begin (16,2); 
  //digitalWrite ( BACKLIGHT_PIN, HIGH );

  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.setCursor(0,0);
  lcd.print("hello");
}

void loop()
{
  
}
