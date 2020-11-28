#include <LiquidCrystal.h>
#include <DHT.h>

//-----------------------GPS LOCATION OF IRRIGATION SYSTEM-----------------//
#include <TinyGPS.h>

TinyGPS gps;  //Creates a new instance of the TinyGPS object
//------------------------------------------------------------------------//

LiquidCrystal lcd(62,63,64,65,66,67);

//Initializing pins where HUMIDITY  & TEMP SENSORS ARE CONNECTED
#define DHTPIN2 2
#define DHTPIN3 3
#define DHTPIN4 4
#define DHTPIN5 5
#define DHTPIN6 6
#define DHTPIN7 7

//initializing pins where SOIL MOISTURE SENSORS are connected
#define soilPin1  A0
#define soilPin2  A1
#define soilPin3  A2
#define soilPin4  A3
#define soilPin5  A4
#define soilPin6  A5

//initializing flame pins
#define FLAMEPIN1 22
#define FLAMEPIN2 23
#define FLAMEPIN3 24
#define FLAMEPIN4 25

//value for storing SOIL MOISTURE sensor values
int soilval_one  = 0;
int soilval_one_value =0;

int soilval_two  = 0;
int soilval_two_value =0;

int soilval_three= 0;
int soilval_three_value =0;

int soilval_four = 0;
int soilval_four_value =0;

int soilval_five = 0;
int soilval_five_value =0;

int soilval_six  = 0;
int soilval_six_value =0;


DHT dht1;
DHT dht2;
DHT dht3;
DHT dht4;
DHT dht5;
DHT dht6;

void setup() 
{
 dht1.setup(DHTPIN2);
 dht2.setup(DHTPIN3);
 dht3.setup(DHTPIN4);
 dht4.setup(DHTPIN5);
 dht5.setup(DHTPIN6);
 dht6.setup(DHTPIN7);

 //Setting flame  pins
 pinMode(FLAMEPIN1,INPUT);
 pinMode(FLAMEPIN2,INPUT);
 pinMode(FLAMEPIN3,INPUT);
 pinMode(FLAMEPIN4,INPUT);

 Serial.begin(9600);
 Serial.println();
 Serial.println("Status\t\tHumidity (%)\t Temperature (C)\t (F) \t Dewpoint \t Soil Mosture (%)");

 lcd.begin(16,4);
}

String gpsLocation()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }

  if (newData)      //If newData is true
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);   
    Serial.print("Latitude = ");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" Longitude = ");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);

  }
 
  Serial.println(failed);
 // if (chars == 0)
   // Serial.println("** No characters received from GPS: check wiring **");
}

//function for calculating dewpoint
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

long microSecondsToInches(long microseconds)
{
    return microseconds / 74/2;
}

//FUNCTIONS FOR EACH SENSOR NODE IN THE FIELD DEPENDING ON THE SENSOR FUNCTION
void humidity_temp_nodeone()
{
  float humidity1    = dht1.getHumidity();
  float temperature1 = dht1.getTemperature();
  float dewpoint1    = calculateDewpoint(temperature1,humidity1);

  soilval_one  = analogRead(soilPin1)/10; //read the value from the sensor
  soilval_one_value   = soilval_one / 1.01;

  Serial.print(dht1.getStatusString());
  Serial.print("\t\t\t( NODE_1 )\t");
  Serial.print(humidity1,1);
  Serial.print("\t\t");
  Serial.print(temperature1,1);
  Serial.print("\t\t");
  Serial.print(dht1.toFahrenheit(temperature1),1);
  Serial.print("\t");
  Serial.print(dewpoint1);
  Serial.print("\t");
  Serial.println(soilval_one_value);
  Serial.println();

  if(isnan(humidity1) || isnan(temperature1)){
  lcd.clear();
  return;
 }
 lcd.setCursor(0,0);
 lcd.print("[NODE1]TEMP=");
 lcd.setCursor(12,0);
 lcd.print(temperature1);
 
 lcd.setCursor(0,1);
 lcd.print("HUMIDITY=");
 lcd.setCursor(9,1);
 lcd.print(humidity1);
 
 lcd.setCursor(0,2);
 lcd.print("DEWPOINT=");
 lcd.setCursor(9,2);
 lcd.print(dewpoint1);

 //soil mositure sensor1 value called here
 lcd.setCursor(0,3);
 lcd.print("SoilMoist=");
 lcd.setCursor(10,3);
 lcd.print(soilval_one_value);
}

void humidity_temp_nodetwo()
{
  float humidity2    = dht2.getHumidity();
  float temperature2 = dht2.getTemperature();
  float dewpoint2    = calculateDewpoint(temperature2,humidity2);

   soilval_two  = analogRead(soilPin2)/10; //read the value from the sensor
   soilval_two_value   =  soilval_two / 1.01;

  Serial.print(dht2.getStatusString());
  Serial.print("\t\t\t( NODE_2 )");
  Serial.print(humidity2,1);
  Serial.print("\t\t");
  Serial.print(temperature2,1);
  Serial.print("\t\t");
  Serial.print(dht2.toFahrenheit(temperature2),1);
  Serial.print("\t");
  Serial.print(dewpoint2);
  Serial.print("\t");
  Serial.println(soilval_two_value);
  Serial.println();

  if(isnan(humidity2) || isnan(temperature2)){
  lcd.clear();
  return;
 }
 
 lcd.setCursor(0,0);
 lcd.print("[NODE2]TEMP=");
 lcd.setCursor(12,0);
 lcd.print(temperature2);
 
 lcd.setCursor(0,1);
 lcd.print("HUMIDITY=");
 lcd.setCursor(9,1);
 lcd.print(humidity2);
 
 lcd.setCursor(0,2);
 lcd.print("DEWPOINT=");
 lcd.setCursor(9,2);
 lcd.print(dewpoint2); 

 //soil mositure sensor2 value called here
 lcd.setCursor(0,3);
 lcd.print("SoilMoist=");
 lcd.setCursor(10,3);
 lcd.print(soilval_two_value);
}

void humidity_temp_nodethree()
{
  float humidity3    = dht3.getHumidity();
  float temperature3 = dht3.getTemperature();
  float dewpoint3    = calculateDewpoint(temperature3,humidity3);

  soilval_three=analogRead(soilPin3)/10; 
  soilval_three_value = soilval_three / 1.01;
 
  Serial.print(dht3.getStatusString());
  Serial.print("\t\t\t( NODE_3 )");
  Serial.print(humidity3,1);
  Serial.print("\t\t");
  Serial.print(temperature3,1);
  Serial.print("\t\t");
  Serial.print(dht3.toFahrenheit(temperature3),1);
  Serial.print("\t");
  Serial.print(dewpoint3);
  Serial.print("\t");
  Serial.println(soilval_three_value);
  Serial.println();

  if(isnan(humidity3) || isnan(temperature3)){
  lcd.clear();
  return;
 }

 lcd.setCursor(0,0);
 lcd.print("[NODE3]TEMP=");
 lcd.setCursor(12,0);
 lcd.print(temperature3);
 
 lcd.setCursor(0,1);
 lcd.print("HUMIDITY=");
 lcd.setCursor(9,1);
 lcd.print(humidity3);
 
 lcd.setCursor(0,2);
 lcd.print("DEWPOINT=");
 lcd.setCursor(9,2);
 lcd.print(dewpoint3);

 //soil mositure sensor3 value called here
 lcd.setCursor(0,3);
 lcd.print("SoilMoist=");
 lcd.setCursor(10,3);
 lcd.print(soilval_three_value);
}

void humidity_temp_nodefour()
{
  float humidity4    = dht4.getHumidity();
  float temperature4 = dht4.getTemperature();
  float dewpoint4    = calculateDewpoint(temperature4,humidity4);

  soilval_four = analogRead(soilPin4)/10; 
  soilval_four_value  = soilval_four/1.01;
 
  Serial.print(dht4.getStatusString());
  Serial.print("\t\t\t( NODE_4 )");
  Serial.print(humidity4,1);
  Serial.print("\t\t");
  Serial.print(temperature4,1);
  Serial.print("\t\t");
  Serial.print(dht4.toFahrenheit(temperature4),1);
  Serial.print("\t");
  Serial.print(dewpoint4);
  Serial.print("\t");
  Serial.println(soilval_four_value);
  Serial.println();

  if(isnan(humidity4) || isnan(temperature4)){
  lcd.clear();
 }

 lcd.setCursor(0,0);
 lcd.print("[NODE4]TEMP=");
 lcd.setCursor(12,0);
 lcd.print(temperature4);
 
 lcd.setCursor(0,1);
 lcd.print("HUMIDITY=");
 lcd.setCursor(9,1);
 lcd.print(humidity4);
 
 lcd.setCursor(0,2);
 lcd.print("DEWPOINT=");
 lcd.setCursor(9,2);
 lcd.print(dewpoint4);

 //soil mositure sensor4 value called here
 lcd.setCursor(0,3);
 lcd.print("SoilMoist=");
 lcd.setCursor(10,3);
 lcd.print(soilval_four_value);
}

void humidity_temp_nodefive()
{
  float humidity5    = dht5.getHumidity();
  float temperature5 = dht5.getTemperature();
  float dewpoint5    = calculateDewpoint(temperature5,humidity5);

  soilval_five = analogRead(soilPin5)/10;
  soilval_five_value  = soilval_five/1.01;

  Serial.print(dht5.getStatusString());
  Serial.print("\t\t\t( NODE_5 )");
  Serial.print(humidity5,1);
  Serial.print("\t\t");
  Serial.print(temperature5,1);
  Serial.print("\t\t");
  Serial.print(dht5.toFahrenheit(temperature5),1);
  Serial.print("\t");
  Serial.print(dewpoint5);
  Serial.print("\t");
  Serial.println(soilval_five_value);
  Serial.println();


  if(isnan(humidity5) || isnan(temperature5)){
  lcd.clear();
  return;
 }

 lcd.setCursor(0,0);
 lcd.print("[NODE5]TEMP=");
 lcd.setCursor(12,0);
 lcd.print(temperature5);
 
 lcd.setCursor(0,1);
 lcd.print("HUMIDITY=");
 lcd.setCursor(9,1);
 lcd.print(humidity5);
 
 lcd.setCursor(0,2);
 lcd.print("DEWPOINT=");
 lcd.setCursor(9,2);
 lcd.print(dewpoint5);

 //soil mositure sensor5 value called here
 lcd.setCursor(0,3);
 lcd.print("SoilMoist=");
 lcd.setCursor(10,3);
 lcd.print(soilval_five_value);
}

void humidity_temp_nodesix()
{
  float humidity6    = dht6.getHumidity();
  float temperature6 = dht6.getTemperature();
  float dewpoint6    = calculateDewpoint(temperature6,humidity6);

  soilval_six  =analogRead(soilPin6)/10;
  soilval_six_value   = soilval_six/1.01;

  Serial.print(dht6.getStatusString());
  Serial.print("\t\t\t( NODE_6 )");
  Serial.print(humidity6,1);
  Serial.print("\t\t");
  Serial.print(temperature6,1);
  Serial.print("\t\t");
  Serial.print(dht6.toFahrenheit(temperature6),1);
  Serial.print("\t");
  Serial.print(dewpoint6);
  Serial.print("\t");
  Serial.println(soilval_six_value);
  Serial.println();

  if(isnan(humidity6) || isnan(temperature6)){
  lcd.clear();
  return;
 }
 
 lcd.setCursor(0,0);
 lcd.print("[NODE6]TEMP=");
 lcd.setCursor(12,0);
 lcd.print(temperature6);
 
 lcd.setCursor(0,1);
 lcd.print("HUMIDITY=");
 lcd.setCursor(9,1);
 lcd.print(humidity6);
 
 lcd.setCursor(0,2);
 lcd.print("DEWPOINT=");
 lcd.setCursor(9,2);
 lcd.print(dewpoint6);

 //soil mositure sensor6 value called here
 lcd.setCursor(0,3);
 lcd.print("SoilMoist=");
 lcd.setCursor(10,3);
 lcd.print(soilval_six_value);
}

int flameEvent1()
{
  Serial.print("\t\t\t( FIREOUTBREAK AT NODE 1= )");
  Serial.print("\t\t");
  Serial.println();
  
  if(digitalRead(FLAMEPIN1))
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK]=");
    lcd.setCursor(13,0);
    lcd.print("YES");
    Serial.print("YES");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK1]=");
    lcd.setCursor(13,0);
    lcd.print("NO");
     Serial.print("NO");
  }
}

int flameEvent2()
{
  Serial.print("\t\t\t( FIREOUTBREAK AT NODE 2= )");
  Serial.print("\t\t");
  Serial.println();
  
  if(digitalRead(FLAMEPIN2))
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK]=");
    lcd.setCursor(13,0);
    lcd.print("YES");
    Serial.print("YES");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK2]=");
    lcd.setCursor(13,0);
    lcd.print("NO");
    Serial.print("NO");
  }
}

int flameEvent3()
{
   Serial.print("\t\t\t( FIREOUTBREAK AT NODE 3= )");
   Serial.print("\t\t");
   Serial.println();
  
  if(digitalRead(FLAMEPIN3))
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK]=");
    lcd.setCursor(13,0);
    lcd.print("YES");
    Serial.print("YES");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK3]=");
    lcd.setCursor(13,0);
    lcd.print("NO");
    Serial.print("NO");
  }
}

int flameEvent4()
{
   Serial.print("\t\t\t( FIREOUTBREAK AT NODE 4= )");
   Serial.print("\t\t");
   Serial.println();
   
  if(digitalRead(FLAMEPIN4))
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK]=");
    lcd.setCursor(13,0);
    lcd.print("YES");
    Serial.print("YES");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("[FIREOUTBRK4]=");
    lcd.setCursor(13,0);
    lcd.print("NO");
    Serial.print("NO");
  }
}

void loop() 
{
  delay(1000);
 //show gps location of irrigation system
 gpsLocation();
  
 //wireless sensor nodes at each node
 //humidty,temperature and soil moisture functions called, represent each node
  //NODE_1
  delay(500);
  humidity_temp_nodeone();
  Serial.println();
 
 //NODE_2
  delay(500);
  humidity_temp_nodetwo();
  Serial.println();


 //NODE_3
  delay(500);
  humidity_temp_nodethree();

 
  //NODE_4
  delay(500);
  humidity_temp_nodefour();

  //NODE_5
  delay(500);
  humidity_temp_nodefive();
  
  //NODE_6
  delay(500);
  humidity_temp_nodesix();

  lcd.clear();
  //FLAME SENSOR NODES
  //FLAME SENSOR NODE 1
  delay(500);
  flameEvent1();

  //FLAME SENSOR NODE 2
  delay(500);
  flameEvent2();

  //FLAME SENSOR NODE 3
  delay(500);
  flameEvent3();

  //FLAME SENSOR NODE 4
  delay(500);
  flameEvent4(); 
}

