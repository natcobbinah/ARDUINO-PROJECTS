int forward = 12;
int backward = 11;
int Speed = 9;
int Open = 7;
int Close = 6;
int openLS = 5;
int closeLS = 4;
int pot = A0;
int potState;
int oLState;
int cLState;
boolean openState = LOW;
boolean closeState = LOW;


void setup() {
  // put your setup code here, to run once:
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(Speed, OUTPUT);
  pinMode(Open, INPUT);
  pinMode(Close, INPUT);
  pinMode(openLS, INPUT);
  pinMode(closeLS, INPUT);
  pinMode(pot, INPUT);
}

void openGate(){
  potState = analogRead(pot);
  digitalWrite(forward, HIGH);
  digitalWrite(backward, LOW);
  analogWrite(Speed, potState);
  }

void closeGate(){
  potState = analogRead(pot);
  digitalWrite(forward, LOW);
  digitalWrite(backward, HIGH);
  analogWrite(Speed, potState);
  }


void loop() {
  // put your main code here, to run repeatedly:
  openState = digitalRead(Open);
  closeState = digitalRead(Close);

  if(openState == HIGH){
    openState = HIGH;
    openGate();
    
    }
}
