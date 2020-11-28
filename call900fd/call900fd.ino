char accept_no[]="0558506118";

void setup() 
{
  Serial.begin(9600);
  Serial.println("AT");
  Serial.println("ATA\n");
  Serial.println(accept_no);
  Serial.println("ATH");
}

void loop() 
{
  
}
