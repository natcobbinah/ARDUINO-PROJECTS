const int led=13;

void setup() 
{
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() 
{
  char ch;
  if(Serial.available() > 0) // is there anything to be read from vterminal
  {
    ch = Serial.read();

    if(ch == 'H')
    {
      digitalWrite(led,HIGH);
    }
    else if (ch == 'L')
    {
      digitalWrite(led,LOW);
    }
  }
    ch = ' ';
    delay(1000);
  
}
