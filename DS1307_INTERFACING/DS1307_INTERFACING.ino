#include <LiquidCrystal.h>
#include <DS1307.h>
#include <Wire.h>

LiquidCrystal lcd(13,12,11,10,9,8);

int clock[7];

void setup(){
for(int i=3;i<8;i++){
 pinMode(i,INPUT); 
}

lcd.begin(20,2);
DS1307.begin();
DS1307.setDate(17,12,22,0,22,33,04);//ano,mes,dia,semana,horas,minutos,segundos

}

void loop(){
DS1307.getDate(clock);

lcd.setCursor(0,1);
lcd.print("Time: ");
Print(clock[4]);
lcd.print(":");
Print(clock[5]);
lcd.print(":");
Print(clock[6]);
lcd.setCursor(0,0);
lcd.print("Date: ");
Print(clock[1]);
lcd.print("/");
Print(clock[2]);
lcd.print("/");
lcd.print("20");
Print(clock[0]);

if(digitalRead(7)){
 clock[5]++;
 if(clock[5]>59) clock[5]=0;
 DS1307.setDate(clock[0],clock[1],clock[2],0,clock[4],clock[5],clock[6]);
 while(digitalRead(7));
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

//Funcao para ajustar os digitos para 00,01,02,...
void Print(int number){
lcd.print(number/10);//imprime o digito mais significativo
lcd.print(number%10);//imprime o digito menos significativo
}
