
int red = 2;
int yellow = 3;
int green = 4;

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(red, OUTPUT);     
  pinMode(yellow, OUTPUT);     
  pinMode(green, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  delay(1000);
  digitalWrite(red, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  delay(1000); 
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  delay(1000);
}
