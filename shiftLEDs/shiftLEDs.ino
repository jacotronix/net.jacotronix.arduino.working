int clockPin = 4;
int latchPin = 3;
int dataPin = 2;
int count = 0;

void setup()
{
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
}

void loop()
{
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, count++);
	digitalWrite(latchPin, HIGH);
	delay(500);
	if (count == 256) count = 0;
}
