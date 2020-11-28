#include <DS1307.h>
#include <Wire.h>

int pinvalue = 13; //to control all sprinklers/ open solenoid valves

int pinvalue1 = 12; //to control sprinkler/open solenoid valve1
int pinvalue2 = 11;//to control sprinkler/open solenoid valve2
                 

int relay_pinone=8; 
int relay_pintwo=9;
int relay_pinthree=10;

int clock[7];

//counter to keep time
int count = 0;

void setup() 
{

  pinMode(pinvalue,INPUT);
  pinMode(pinvalue1,INPUT);
  pinMode(pinvalue2,INPUT);
  // pinMode(motorpin,OUTPUT)
  pinMode(relay_pinone,OUTPUT);
  pinMode(relay_pintwo,OUTPUT);
  pinMode(relay_pinthree,OUTPUT);

// for(int i=3;i<8;i++){
// pinMode(i,INPUT); 
//}

DS1307.begin();
DS1307.setDate(17,12,22,0,22,33,04);//ano,mes,dia,semana,horas,minutos,segundos

}

void loop()
{
//  char ch;
//  if(Serial.available() > 0) // is there anything to be read from vterminal
//  {
//    ch = Serial.read();
//  }
//    ch = ' ';
//    delay(1000);
   delay(100);

   if(digitalRead(pinvalue))
   {
    digitalWrite(relay_pinone,HIGH);
    digitalWrite(relay_pintwo,HIGH);
    digitalWrite(relay_pinthree,HIGH);
   }

   if(digitalRead(pinvalue1))
   {
    digitalWrite(relay_pinone,HIGH);
    digitalWrite(relay_pintwo,LOW);
    digitalWrite(relay_pinthree,LOW);
   }

    if(digitalRead(pinvalue2))
    {
    digitalWrite(relay_pinone,LOW);
    digitalWrite(relay_pintwo,HIGH);
    digitalWrite(relay_pinthree,LOW);
   }

  
   //TIMER CODES
   DS1307.getDate(clock);

if(digitalRead(7)){
clock[5]++;
if(clock[5]>59) clock[5]=0;
DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
while(digitalRead(7));
 
//Sprinklers / solenoid valves running;
count++;

if(count > 5){
  digitalWrite(relay_pinone,HIGH);
  digitalWrite(relay_pintwo,HIGH);
  digitalWrite(relay_pinthree,HIGH); 
 }

}

if(digitalRead(6)){
 clock[4]++;
 if(clock[4]>23) clock[4]=0;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 while(digitalRead(6));
}

if(digitalRead(5)){//dia
 clock[2]++;
  if(clock[2]>31) clock[2]=1;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 while(digitalRead(5));
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
