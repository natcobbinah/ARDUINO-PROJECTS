
// Motor A
int in1 = 4;
int in2 = 5;

// Motor B
int in3 = 6;
int in4 = 7;

void setup()

{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void demoOne()
{


  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
 
  // Turn on motor B

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(2000);

//  // Now change motor directions
//
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, HIGH);  
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH); 
//
//  delay(2000);
//
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);  
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);

}

void demoTwo()

{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH); 




  // Now turn off motors

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  

}

void loop()

{

  demoOne();

  delay(1000);

//  demoTwo();
//
//  delay(1000);

}
