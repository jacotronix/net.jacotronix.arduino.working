int clockPin = 4;
int latchPin = 3;
int dataPin = 2;
int index = 0;

// A = 5
// B = 4
// C = 2
// D = 0
// E = 1
// F = 6
// G = 7
// . = 3

//     7 6 5 4 3 2 1 0
//     G F A B . C E D
//
// 0 - 0 1 1 1 0 1 1 1 = 0x77
// 1 - 0 0 0 1 0 1 0 0 = 0x14
// 2 - 1 0 1 1 0 0 1 1 = 0xB3
// 3 - 1 0 1 1 0 1 0 1 = 0xB5
// 4 - 1 1 0 1 0 1 0 0 = 0xD4
// 5 - 1 1 1 0 0 1 0 1 = 0xE5
// 6 - 1 1 1 0 0 1 1 1 = 0xE7
// 7 - 0 0 1 1 0 1 0 0 = 0x34
// 8 - 1 1 1 1 0 1 1 1 = 0xF7
// 9 - 1 1 1 1 0 1 0 1 = 0xF5

int numbers[] = {0x77, 0x14, 0xB3, 0xB5, 0xD4, 0xE5, 0xE7, 0x34, 0xF7, 0xF5};
void setup()
{
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
}

void loop()
{
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, numbers[index++]);
	digitalWrite(latchPin, HIGH);
	delay(500);
	if (index == 10) index = 0;
}
