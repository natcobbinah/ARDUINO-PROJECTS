int ledpin=13;

char msg='1';

void setup() {
     pinMode(ledpin,OUTPUT);
     
      char ch;
      Serial.begin(9600);
      delay(200);
      
  if(Serial.available() > 0){
    ch = Serial.read();

    if(ch == '1'){
digitalWrite(ledpin,HIGH);
    }
    else if(ch == '0'){
      digitalWrite(ledpin,LOW);
    }
  }
}

void loop() {

 
}
