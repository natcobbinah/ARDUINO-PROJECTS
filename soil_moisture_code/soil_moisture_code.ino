int val = 0; //value for storing moisture value

int soilPin = A0; //declare a variable for the soil moisture sensor

int soilPower= 7; //variable for soil moisture power

//Rather than powering the sensor though the 3.3v or 5v pins
//we'll use a digital pin to power the sensor. This will 
//prevent corrosion of the sensor as it sits in the soil

void setup()
{
  Serial.begin(9600); 

  pinMode(soilPower,OUTPUT); //set D7 as an OUTPUT

  digitalWrite(soilPower,LOW); //set to LOW as not power is flowing through the sensor
 
}

void loop()
{
  Serial.print("Soil Moisture = ");
  //get soil moisture value from the function below and print it
  Serial.print(readSoil());
  Serial.print("%");
  Serial.println();

  delay(1000);
}

int readSoil()
{
  digitalWrite(soilPower,HIGH); //turn D7 on

  delay(10); //wait 10 milliseconds

  val = analogRead(soilPin); //read the signal value from the sensor

  //map it to the range of analog out:
  val = map(val,0,1023,0,100);

  digitalWrite(soilPower,LOW); //turn D7 off

  return val;
}

