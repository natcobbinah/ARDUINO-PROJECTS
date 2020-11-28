/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define speakerPin 5
#define SPEAKERTONE 7500

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

//MQ3 Gas sensor initialization
const int AOUTpin=A0;//the AOUT pin of the alcohol sensor goes into analog pin A0 of the arduino

int i,alco_high,alco_low,mapped,data[200];

//CAR KEY initalization
int starter_key = 12; // KEY SWITCH

int motorpin1 = 6;
int motorpin2 = 7;

void setup()
{
  //pinMode ( BACKLIGHT_PIN, OUTPUT );
  lcd.begin (16,2); 
  //digitalWrite ( BACKLIGHT_PIN, HIGH );

  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  //WHEELS variable initialization
  pinMode(motorpin1,OUTPUT);
  pinMode(motorpin2,OUTPUT);

  //CAR KEY INITIALIZATION
  bitSet(DDRB, 5); //led pin at output 13
  pinMode(DDRB,3); //led pin at output 11
  pinMode(DDRB,2); //led pin at output 10

  pinMode(speakerPin,OUTPUT);

  //Gas sensor variable initalizations
  Serial.begin(115200);//sets the baud rate
  pinMode(AOUTpin, INPUT);//sets the pin as an input to the arduino
  for(i=2;i<=5;i++)
  {
    pinMode(i,OUTPUT);//sets the pin as an output of the arduino
  }
}

void loop()
{ 
    
         alco_high=0; // initially alcohol level is zero
         alco_low = 1023; // low threshold is 1023

         for(i=200; i>0; i--){
            data[i] = data[i-1]; // decrement of data
        
            if(data[i]>alco_high)
                alco_high=data[i];
            if(data[i]<alco_low)
                alco_low=data[i];
         }

         data[0]= analogRead(AOUTpin);//reads the analaog value from the alcohol sensor's AOUT pin
         mapped=map(data[0],0,1023,0,600);
         Serial.print("Alcohol value: ");
         Serial.println(mapped);//prints the alcohol value
         delay(100);

         //Check if the read is greater than 95% of the span
         double readValue = (alco_high-.95*(alco_high-alco_low));

  
     if(digitalRead(starter_key) == LOW){
           //  clearLCD();
             enginesOff();
             digitalWrite(motorpin1,LOW);
             digitalWrite(motorpin2,LOW);

             digitalWrite(startpin1,LOW);
             digitalWrite(startpin2,LOW);
             digitalWrite(drivingpin,LOW);
     }
  
     if(digitalRead(starter_key) == HIGH){
            //LCD welcome message
            welcomeMsg();
            
           if((alco_high-alco_low)>100){
              if(data[0] > readValue )
                digitalWrite(motorpin1,LOW);
                digitalWrite(motorpin2,LOW);

                digitalWrite(startpin1,HIGH);
                digitalWrite(startpin2,HIGH);
                digitalWrite(drivingpin,LOW);

                digitalWrite(speakerPin,HIGH);
                sendsmsMessageDrunk();
           }else{
                digitalWrite(motorpin1,HIGH);
                digitalWrite(motorpin2,HIGH);

                digitalWrite(startpin1,LOW);
                digitalWrite(startpin2,LOW);
                digitalWrite(drivingpin,HIGH);

                 digitalWrite(speakerPin,LOW);
                sendsmsMessageOK();
           }
     }
}

//PRINT CAR STATE ON LCD SCREEN
void enginesOff()
{
  lcd.setCursor(0,0);
  lcd.print("Engines Offed");
} 

//CLEAR LCD SCREEN METHOD
void clearLCD(){
  lcd.clear();
}

//PRINT WELCOME MESSAGE ON LCD SCREEN
void welcomeMsg(){
  lcd.setCursor(0,0);
  lcd.print("Welcome Driver");
}

//PRINT DRIVERS STATE ON LCD SCREEN
void sendsmsMessageOK()
{
  lcd.setCursor(0,0);
  lcd.print("Driver_State:Alc");
  lcd.setCursor(0,1);
  lcd.print("OK to Drive:");
  lcd.print(mapped);
} 

//PRINT DRIVERS STATE ON LCD SCREEN
void sendsmsMessageDrunk()
{
  lcd.setCursor(0,0);
  lcd.print("Driver_State:Alc");
  lcd.setCursor(0,1);
  lcd.print("Drunk Can't_Drive");
}
       
