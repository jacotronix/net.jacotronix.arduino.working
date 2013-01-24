
int ledPin = 3;
volatile int val = 0;
unsigned long buttonTime = 0;
unsigned long lastButtonTime = 0;

void setup()
{
	pinMode(ledPin, OUTPUT);
	attachInterrupt(0, buttonISR, FALLING);
}

void loop()
{
}

void buttonISR()
{
	buttonTime = millis();
	if (buttonTime - lastButtonTime > 250)
	{
		if (val)
		{
			val = 0;
			digitalWrite(ledPin, LOW);
		} else {
			val = 1;
			digitalWrite(ledPin, HIGH);
		}
		lastButtonTime = buttonTime;
	}
}