unsigned char Check,T_byte1,T_byte2,RH_byte1,RH_byte2,Ch;

unsigned Temp,RH, sum;

int dhtpin = 2;

void setup()
{
 pinMode(dhtpin,INPUT);
}

void loop()
{
  checkResponse();

  if(Check == 1)
  {
    RH_byte1= readData();
    RH_byte2= readData();
    T_byte1 = readData();
    T_byte2 = readData();
    sum     = readData();

    if(sum == ((RH_byte1 + RH_byte2 + T_byte1 + T_byte2) & 0X0FF)){
      Temp = T_byte1;
      Temp = (Temp <<   8) | T_byte2;
      RH   = RH_byte1;
      RH   = (RH << 8) | RH_byte2;
      Serial.print("Temp & Humidity");

      if(Temp > 0X8000){
        Serial.print("");
      }
      Serial.print((Temp/ 100) % 10);
      Serial.print((Temp /10) % 10);
      Serial.print(Temp % 10);

      Serial.print((RH /100) % 10);
      Serial.print((RH / 10) % 10);
      Serial.print(RH % 10);
    }
    else{
      Serial.print("No response");
      delay(1000);
    }
  }
}


void checkResponse()
{
  Check = 0;
  delay(30);

  if(digitalRead(dhtpin) == LOW)
  {
    delay(10);
    if(digitalRead(dhtpin) == HIGH)
    Check = 1;
    delay(20);
  }
}


char readData()
{
  char i,j;
  for(j=0; j < 8; j++)
  {
    while(digitalRead(dhtpin) == LOW)
    delay(30);

    if(digitalRead(dhtpin) == LOW)
      i&= ~(1 <<(7-j)); // clear bit
    else{
      i |= (1 << (7-j));
    }
    while(digitalRead(dhtpin) == HIGH);
  }
  return i;
}


