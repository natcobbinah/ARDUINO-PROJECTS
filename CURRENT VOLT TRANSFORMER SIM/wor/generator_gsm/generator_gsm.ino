#include <LiquidCrystal.h>
#include <DS1307.h>
#include <Wire.h>

#define speakerPin 2
#define SPEAKERTONE 7500

char company_no[] = "+233278782432";

LiquidCrystal lcd(13,12,11,10,9,8);

int clock[7];

void setup(){
for(int i=3;i<8;i++){
 pinMode(i,INPUT); 

 Serial.begin(9600);
 pinMode(speakerPin,OUTPUT);
}

lcd.begin(20,2);
DS1307.begin();
DS1307.setDate(16,4,29,0,17,50,04);//ano,mes,dia,semana,horas,minutos,segundos
}

void loop(){
DS1307.getDate(clock);

if(digitalRead(7)){
 clock[5]++;
 if(clock[5]>59) clock[5]=0;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 while(digitalRead(7));
 //-first 250 hours--------------------------------------------//
 lcd.setCursor(0,1);
 lcd.print("Maintenance time is up");
  //------------gsm---------------------------------------------------------
 Serial.println("AT+CMGF=1");    
 delay(2000);
 Serial.print("AT+CMGS=\"");
 Serial.print(company_no); 
 Serial.write(0x22);
 Serial.write(0x0D);  // hex equivalent of Carraige return    
 Serial.write(0x0A);  // hex equivalent of newline
 delay(2000);
 Serial.print("Mantrac Ghana Limited,Machine service time is due");
 delay(500);
 Serial.println (char(26));//the ASCII code of the ctrl+z is 26
 //-------------------------------------------------------------------------
 digitalWrite(speakerPin,HIGH);
 tone(speakerPin,SPEAKERTONE+200);
 delay(1000);
  tone(speakerPin,0);
}

if(digitalRead(6)){
 clock[4]++;
 if(clock[4]>23) clock[4]=0;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 //------------gsm---------------------------------------------------------
 Serial.println("AT+CMGF=1");    
 delay(2000);
 Serial.print("AT+CMGS=\"");
 Serial.print(company_no); 
 Serial.write(0x22);
 Serial.write(0x0D);  // hex equivalent of Carraige return    
 Serial.write(0x0A);  // hex equivalent of newline
 delay(2000);
 Serial.print("Mantrac Ghana Limited,Machine service time is passed 5 hours");
 delay(500);
 Serial.println (char(26));//the ASCII code of the ctrl+z is 26
 //-------------------------------------------------------------------------
 //-first 255 hours--------------------------------------------//
 lcd.setCursor(0,2);
 lcd.print("Maintenance time is passed 5hours");
 //-------------------------------------------------------------------------
 digitalWrite(speakerPin,HIGH);
 tone(speakerPin,SPEAKERTONE+200);
 delay(1000);
 tone(speakerPin,0);
 
 while(digitalRead(6));
}

if(digitalRead(5)){//dia
 clock[2]++;
  if(clock[2]>31) clock[2]=1;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 while(digitalRead(5));
  //-first 260 hours--------------------------------------------//
 lcd.setCursor(0,3);
 lcd.print("Maintenance time is passed 10hours");
  //------------gsm---------------------------------------------------------
 Serial.println("AT+CMGF=1");    
 delay(2000);
 Serial.print("AT+CMGS=\"");
 Serial.print(company_no); 
 Serial.write(0x22);
 Serial.write(0x0D);  // hex equivalent of Carraige return    
 Serial.write(0x0A);  // hex equivalent of newline
 delay(2000);
 Serial.print("Mantrac Ghana Limited,Machine service time is passed 10 hours");
 delay(500);
 Serial.println (char(26));//the ASCII code of the ctrl+z is 26
 //-------------------------------------------------------------------------
 digitalWrite(speakerPin,HIGH);
 tone(speakerPin,SPEAKERTONE+200);
 delay(1000);
 tone(speakerPin,0);
}

if(digitalRead(4)){//mes
 clock[1]++;
 if(clock[1]>12) clock[1]=1;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 while(digitalRead(4));
}

if(digitalRead(3)){//ano
 clock[0]++;
 if(clock[0]>99) clock[0]=0;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 while(digitalRead(3));
}


delay(100);
}

