
int led = 13;
int leds[8] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {                
	for (int i = 0; i < 8; i++)
	{
		pinMode(leds[i], OUTPUT);     
	}
}


void loop() {
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(leds[i], HIGH);
	}
	delay(200);
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(leds[i], LOW);
	}
	delay(200);
}