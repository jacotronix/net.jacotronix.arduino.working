#include <SPI.h>
#include <NewPing.h>

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
// set pin 12 as the reset pin for the 555 timer
const int timerEnablePin = 12;

// Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN  3
// Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN     2
// Maximum distance we want to ping for (in centimeters). Check device datasheet.
#define MAX_DISTANCE 4000

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int level = 0;
int distance = 0;

void setup()
{
	// set the slaveSelectPin as an output:
	pinMode (slaveSelectPin, OUTPUT);
	// set the 555 timer enable pin to output
	pinMode (timerEnablePin, OUTPUT);
	// disable the 555 timer
	digitalWrite(timerEnablePin, LOW);

	// initialize SPI:
	SPI.begin();

	// Open serial monitor at 115200 baud to see ping results.
	Serial.begin(115200);
}

void loop()
{
	// Send ping, get ping time in microseconds (uS).
	unsigned int uS = sonar.ping();
	// Convert ping time to distance
	distance = uS / US_ROUNDTRIP_CM; 

	// Print distance to serial console
	Serial.print("Ping: ");
	Serial.print(uS / US_ROUNDTRIP_CM);
	Serial.println("cm");

	if (distance < 11)
	{
		// too close - disable the 555 timer
		digitalWrite(timerEnablePin, LOW);
	} 
	else if (distance > 52)
	{
		// too far - disable the 555 timer
		digitalWrite(timerEnablePin, LOW);
	} 
	else
	{
		// set potentiometer level to a value proportional to distance
		level = int ((distance - 10) * 3) + 1;
		digitalPotWrite(level);
		// enable the 555 timer
		digitalWrite(timerEnablePin, HIGH);
	}
	delay(100);
}


// SPI transation to set the value of the digital pot
int digitalPotWrite(int value)
{
  //take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //send in the address and value via SPI:
  SPI.transfer(0);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH); 
}