#include <DHT.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);

/*This library supports DHT11, DHT22, AM2302 and RHT03 sensors
 * Auto detects sensor model/type
 * Downloaded from Robo India webpage
 */

 DHT dht;

int val = 0; //value for storing dht value
int hum = 0; //value for storing humidity value

int dhtpin = 2; //where dht is connected to mcu


void setup()
{
  Serial.begin(9600);
  pinMode(dhtpin,INPUT);
  digitalWrite(dhtpin,LOW); 
  dht.setup(2);
}

void loop()
{
  Serial.print("Status:");
  Serial.print(readStatus());
  delay(1000);

  Serial.print("Humidity:");
  Serial.print(readHumidity());
  delay(1000);
}

int readHumidity()
{
  digitalWrite(dhtpin,HIGH);

  delay(10);

  hum = dht.getHumidity();

  digitalWrite(dhtpin,LOW);

  return hum;
}

int readStatus()
{
  digitalWrite(dhtpin,HIGH);

  delay(10);

  val = dht.getStatusString();

  digitalWrite(dhtpin,LOW);

  return val;
}

