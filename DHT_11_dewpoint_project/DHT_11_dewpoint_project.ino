#include <DHT.h>

/*This library supports DHT11, DHT22, AM2302 and RHT03 sensors
 * Auto detects sensor model/type
 * Downloaded from Robo India webpage
 */

 DHT dht;

 void setup()
 {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\t\tHumidity (%)\t Temperature (C)\t (F) \t Dewpoint");

  dht.setup(2); //data pin 2;
 }

 void loop()
 {
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();

  float temperature = dht.getTemperature();

  float dewpoint = calculateDewpoint(temperature,humidity);

  Serial.print(dht.getStatusString());
  Serial.print("\t\t\t");
  Serial.print(humidity,1);
  Serial.print("\t\t");
  Serial.print(temperature,1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature),1);
  Serial.print("\t");
  Serial.println(dewpoint);

 }

 float calculateDewpoint(float T, float RH)
 {
  //approximate dew point using the formula from wikipedia's article on dewpoint
  float dp =0.0;

  float gTRH = 0.0;

  float a = 17.271;
  float b = 237.7;

  gTRH = ((a*T)/(b+T)) + log(RH/100);
  dp = (b*gTRH)/(a-gTRH);

  return dp;
 }

