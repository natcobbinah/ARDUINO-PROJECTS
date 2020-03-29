char phone_no1[]="0247675938";

int zipperValue=0;
int zipperPin=A0;

const int buttonPin=8;
int buttonstate =0;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin,INPUT);
   pinMode(13,OUTPUT);
}

void loop() 
{
  
  buttonstate = digitalRead(buttonPin);
  
  zipperValue=analogRead(zipperPin);
  Serial.println(zipperValue);
  delay(1000);

  if(zipperValue >1020)
  {
    Serial.println("Bag Closed");
  }

   if((zipperValue > 1020) && (buttonstate == LOW))
  {
     Serial.println("Bag CLOSED");
  }

   if((zipperValue > 1020) && (buttonstate == HIGH))
  {
     Serial.println("Bag TAMPERED WITH");
      digitalWrite(13,HIGH);
     Serial.println("AT+CMGF=1");    
     delay(100);
     Serial.print("AT+CMGS=\"");
     Serial.print(phone_no1); 
     Serial.write(0x22);
     Serial.write(0x0D);  // hex equivalent of Carraige return    
     Serial.write(0x0A);  // hex equivalent of newline
     delay(100);
     Serial.println("Bag has been tampered with");
     delay(100);
     Serial.println (char(26));//the ASCII code of the ctrl+z is 26
  }

  if((zipperValue < 10))
  {
    Serial.println("bag CAN opened by user");
  }

    if((zipperValue < 10) && (buttonstate == LOW))
  {
     Serial.println("SECURITY DISABLED");
  }
//  if((zipperValue < 300) && (buttonstate == LOW))
//  {
//      Serial.println("Bag opened by user");
//    digitalWrite(13,LOW);
//  }
 
}
