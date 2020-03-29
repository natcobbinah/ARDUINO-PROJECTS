 #include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

char phone_no1[]="0543548494";                                                                          
//-------------------KEYPAD-------------------------------------
#include <Keypad.h>

int position=0;
char key;

const byte rows=4;
const byte cols=3;

char keys[rows][cols]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows]={5,8,9,10};
byte colPins[cols]={11,12,13};

Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,rows,cols);
//-----------------LCD-------------------------------------------
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F

#define BACKLIGHT_PIN 3

#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);  // set the LCD address to 0x38

//--------------------------------------------------------------

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int pos;
char id;
//char data=0;
//char data2=0;

int motorPin1=6;
int motorPin2=7;
//----------------------------------------------

void setup()  
{
  lcd.begin (16,2); 

  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.setCursor(0,0);
  
  Serial.begin(9600);
  //while (!Serial);  // For Yun/Leo/Micro/Zero/...
 // delay(100);
 // Serial.println("\n\nAdafruit finger detect test");
  lcd.print("Checking Finger");
  lcd.print("Print Sensor");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  lcd.clear();
  
  if (finger.verifyPassword()) {
    //Serial.println("Found fingerprint sensor!");
    lcd.setCursor(0,0);
    lcd.print("FingerPrint Sensor");
    lcd.setCursor(0,1);
    lcd.print("Works");
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FingerPrint Sensor");
    lcd.setCursor(0,1);
    lcd.print("Off :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sensor contains ");
  lcd.setCursor(0,1);
  lcd.print(finger.templateCount);
  lcd.println(" templates");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("Waiting for");
  lcd.setCursor(0,1);
  lcd.println("Valid-finger");

  //-----------------------------------------------
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);


}

void loop() 
{
   //-------verify owners fingerprint---------------
  getFingerprintIDez();
  delay(50);            
  //----------------------------------------------
   key = keypad.getKey();
     //------------------------------------------
      //------------------------------------------

  // Serial.println("\n\nType either (e)or (d) or (s) to enroll,delete and start engine respectively")
   //delay(1000);

//   if(Serial.available() > 0)
//  {
//    data = Serial.read();
//    Serial.println(data);
//  }

//  switch(data)
//  {
//     case 's':

     //reset key
     if(key == '0')
     {
      getFingerprintIDez();
      delay(50);        
     }

      if(key == '1')
      {
      digitalWrite(motorPin1,180);
      digitalWrite(motorPin2,180);
      
     Serial.println("AT+CMGF=1");    
     delay(100);
     Serial.print("AT+CMGS=\"");
     Serial.print(phone_no1); 
     Serial.write(0x22);
     Serial.write(0x0D);  // hex equivalent of Carraige return    
     Serial.write(0x0A);  // hex equivalent of newline
     delay(100);
     Serial.println("CAR HAS BEEN STARTED");111

     
     delay(100);
     Serial.println (char(26));//the ASCII code of the ctrl+z is 26
      }

  //   case 'e':

       if(key == '2')
       {
        lcd.setCursor(0,0);
       lcd.println("Ready to enroll");
       delay(2000);

       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Type ID (from 1 to 127)");
       lcd.print("You want to save finger as...");
       delay(7000);
      // if(Serial.available() > 0)
       //{
       //  char enrollnum = 0;
        int input[2] = {0};
        for(unsigned cursor =0; cursor < 2; ++cursor)
        {
          input[cursor] = keypad.getKey();
        }
        id = input;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(id);
       // char enrollnum = keypad.getKey();
       //}
       if (id == 0) {// ID #0 not allowed, try again!
       return;
       }
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Enrolling ID #");
       lcd.setCursor(0,1);
       lcd.print(id);
  
       getFingerprintEnroll();    
       }


 //    case 'd':
       if(key == '3')
       {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println("Ready to delete a fingerprint");
        lcd.rightToLeft();
        delay(1000);

        lcd.setCursor(0,1);
        lcd.println("Please type in the ID # (from 1 to 127) you want to delete...");
        delay(1000);
      //  if(Serial.available() > 0)
      //  {
         // char deletenum = 0;
          int input[2] = {0};
        for(unsigned cursor =0; cursor < 2; ++cursor)
        {
          input[cursor] = keypad.getKey();
        }
        id = input;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(id);
       //   char deletenum = keypad.getKey();
         // id = deletenum;
     //   }
        if (id == 0) {// ID #0 not allowed, try again!
        return;
        }

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Deleting ID ");
        lcd.setCursor(0,1);
        lcd.println(id);
  
        deleteFingerprint(id);
       }

 //     case 'q':
      
     //    if(getFingerprintIDez() == true) //if fingerprint verification again is true
     //    {
     if(key == '4')
       {
         digitalWrite(motorPin1,0);
         digitalWrite(motorPin2,0);
       }
     //    }
         
 } 


//---------------VERIFY OWNERS FINGERPRINT METHOD-----------------------------------------------------------------
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");  
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Found ID #"); 
  lcd.print(finger.fingerID); 
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);

   //------------------------------------------------------------------
   lcd.setCursor(0,1);
   lcd.println("Access to allfunctions");
   lcd.rightToLeft();

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("[1]start[2]enroll");
   lcd.setCursor(0,1);
   lcd.print("[3]delete[4]stop engine");
   delay(1000);
   //------------------------------------------------------------------
  return finger.fingerID; 
}
//----------------------------------------------------------------------------------------------------------------------




//--------------stop engine using fingerprint-----------------------
int stopEngine(){
   uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
}

//enrolling codes---------------------------------------------------

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  lcd.print("Remove finger");
  delay(500);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  lcd.print("ID "); Serial.println(id);
  p = -1;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ID "); lcd.print(id);

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Stored!");
    //--------------------------------------------
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("[1]start[2]enroll");
   lcd.setCursor(0,1);
   lcd.print("[3]delete[4]stop engine");
   delay(1000);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    //--------------------------------------------
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  } 
}

//------------------deleting codes---------------------------------------
 uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
 }

