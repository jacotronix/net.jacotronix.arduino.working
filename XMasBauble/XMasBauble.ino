
int ledA = 1;
int ledB = 2;
int ledC = 3;
int ledD = 4;
int i=0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as an output.
  pinMode(ledA, OUTPUT);     
  pinMode(ledB, OUTPUT);     
  pinMode(ledC, OUTPUT);     
  pinMode(ledD, OUTPUT);     
}

void allBlink()
{
  for (int i = 0; i < 20 ; i++)
  {
    digitalWrite(ledA, HIGH);
    digitalWrite(ledB, HIGH);
    digitalWrite(ledC, HIGH);
    digitalWrite(ledD, HIGH);
    delay(100);
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, LOW);
    delay(100);
  }
}

void redGreenAlt()
{
  for (int i = 0; i < 20 ; i++)
  {
    digitalWrite(ledA, HIGH);
    digitalWrite(ledB, LOW);
    digitalWrite(ledC, HIGH);
    digitalWrite(ledD, LOW);
    delay(100);
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, HIGH);
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, HIGH);
    delay(100);
  }
}

void gapChase(boolean cw, boolean chaseHole)
{
  boolean defaultLevel = chaseHole;
  boolean positionLevel = !chaseHole;
  if (cw == true)
  {
    for (int i = 0; i < 20 ; i++)
    {
      for (int pos = 1; pos < 5; pos++)
      {
        digitalWrite(ledA, defaultLevel);
        digitalWrite(ledB, defaultLevel);
        digitalWrite(ledC, defaultLevel);
        digitalWrite(ledD, defaultLevel);
        digitalWrite(pos, positionLevel);
        delay(100);
      }
    }
  } else {
    for (int i = 0; i < 20 ; i++)
    {
      for (int pos = 4; pos > 0; pos--)
      {
        digitalWrite(ledA, defaultLevel);
        digitalWrite(ledB, defaultLevel);
        digitalWrite(ledC, defaultLevel);
        digitalWrite(ledD, defaultLevel);
        digitalWrite(pos, positionLevel);
        delay(100);
      }
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {
  allBlink();
  gapChase(true, false);
  gapChase(true, true);
  redGreenAlt();
  gapChase(false, false);
  gapChase(false, true);
}
