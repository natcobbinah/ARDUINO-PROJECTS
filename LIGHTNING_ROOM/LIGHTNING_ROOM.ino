const int relaypin=2;
char data = 0;

void setup() 
{
 Serial.begin(9600);
 pinMode(relaypin,OUTPUT);
}

void loop() 
{
   if(Serial.available() > 0)
   {
     data = Serial.read();
   }

   if(data == '1')
   {
     digitalWrite(relaypin,HIGH);
   }

   if(data == '0')
   {
     digitalWrite(relaypin,LOW);
   }
}
