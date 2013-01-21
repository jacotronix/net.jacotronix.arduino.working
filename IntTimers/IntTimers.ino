/*
Example of Clear Timer on Compare Match (CTC Mode) using the hardware Timer1

The Math:

	(timer speed (Hz)) = (Arduino Clock Speed (16MHz)) / pre-scaler
	interrup freq (Hz) = (Arduino Clock Speed (16MHz)) / (pre-scaler * (compare match register + 1))
	compare match register = (16,000,000Hz / (prescaler * derived interrupt freq)) - 1
	pre-scalars can be 1, 8, 64, 256, 1024 set in CS12, CS11 and CS10

	CS12	CS11	CS10
	0		0		0		No clock source (Timer/Counter stopped)
	0		0		1		clk/1 - No pre-scaler
	0		1		0		clk/8
	0		1		1		clk/64
	1		0		0		clk/256
	1		0		1		clk/1024
	1		1		0		external clock source on T1 pin. Clock on falling edge
	1		1		1		external clock source on T1 pin. Clock on rising edge
*/

int led = 13;
boolean toggle1 = 0;

void setup()
{
  pinMode(led, OUTPUT);     
  cli(); // stop interrupts

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

// define Interrupt Service Routine.  Generates output pulses of 1Hz/2 = 0.5Hz.
ISR(TIMER1_COMPA_vect)
{
	if (toggle1)
	{
		digitalWrite(led, HIGH);
		toggle1 = 0;
	} else {
		digitalWrite(led, LOW);
		toggle1 = 1;
	}
}

void loop()
{

  /* add main program code here */

}
