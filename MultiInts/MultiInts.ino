int led1 = 4;
int led2 = 5;
boolean toggle1 = 0;

int led3 = 3;
volatile int val = 0;
unsigned long buttonTime = 0;
unsigned long lastButtonTime = 0;

void setup()
{
	pinMode(led1, OUTPUT);     
	pinMode(led2, OUTPUT);     
	cli(); // stop interrupts
	pinMode(led3, OUTPUT);
	attachInterrupt(0, buttonISR, FALLING);

	// set timer1 at 1Hz
	TCCR1A = 0;  // Set Timer 1's A control register to 0
	TCCR1B = 0;  // same for B
	// set compare match registers for 1Hz intervals
	OCR1A = 15624; // = (16*10^6)/(1*1024) -1 (must be < 65535)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// set CS12 and CS10 bits for 1024 prescalar
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	sei(); // allow interrupts

}

void loop()
{
	digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(500);               // wait for a second
	digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
	delay(500);               // wait for a second
}

void buttonISR()
{
	buttonTime = millis();
	if (buttonTime - lastButtonTime > 250)
	{
		if (val)
		{
			val = 0;
			digitalWrite(led3, LOW);
		} else {
			val = 1;
			digitalWrite(led3, HIGH);
		}
		lastButtonTime = buttonTime;
	}
}

// define Interrupt Service Routine.  Generates output pulses of 1Hz/2 = 0.5Hz.
ISR(TIMER1_COMPA_vect)
{
	if (toggle1)
	{
		digitalWrite(led1, HIGH);
		toggle1 = 0;
	} else {
		digitalWrite(led1, LOW);
		toggle1 = 1;
	}
}
