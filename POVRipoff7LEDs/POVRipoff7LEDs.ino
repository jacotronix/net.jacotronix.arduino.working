// 7 LED POV

int leds[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// letter width. since i have 7 LED, then each letter would look like a 7 x 5 matrix
#define WIDTH 5

//library, each letter stored in hex number instead of bit, five hex numbers make a letter; hence each hex number represent a column of a letter.

const byte font [][WIDTH] =
{
 {0x7e, 0x09, 0x09, 0x09, 0x7e}, //A
 {0x7f, 0x49, 0x49, 0x49, 0x36}, //B
 {0x3e, 0x41, 0x41, 0x41, 0x22}, //C
 {0x7f, 0x41, 0x41, 0x22, 0x1c}, //D
 {0x7f, 0x49, 0x49, 0x49, 0x49}, //E
 {0x7f, 0x09, 0x09, 0x09, 0x09}, //F
 {0x7e, 0x41, 0x49, 0x49, 0x38}, //G
 {0x7f, 0x08, 0x08, 0x08, 0x7f}, //H
 {0x00, 0x41, 0x7f, 0x41, 0x00}, //I
 {0x30, 0x40, 0x41, 0x7f, 0x01}, //J
 {0x7f, 0x08, 0x14, 0x22, 0x41}, //K
 {0x7f, 0x40, 0x40, 0x40, 0x40}, //L
 {0x7f, 0x02, 0x04, 0x02, 0x7f}, //M
 {0x7f, 0x02, 0x0c, 0x10, 0x7f}, //N
 {0x3e, 0x41, 0x41, 0x41, 0x3e}, //O
 {0x1e, 0x21, 0x21, 0x21, 0x5e}, //Q
 {0x7f, 0x09, 0x19, 0x29, 0x46}, //R
 {0x26, 0x49, 0x49, 0x49, 0x32}, //S
 {0x01, 0x01, 0x7f, 0x01, 0x01}, //T
 {0x3f, 0x40, 0x40, 0x40, 0x3f}, //U
 {0x07, 0x38, 0x40, 0x38, 0x07}, //V
 {0x3f, 0x40, 0x3f, 0x40, 0x3f}, //W
 {0x63, 0x14, 0x08, 0x14, 0x63}, //X
 {0x07, 0x08, 0x70, 0x08, 0x07}, //Y
 {0x61, 0x51, 0x49, 0x45, 0x43} //Z  
};


//set up pin 0 - 7 as OUTPUT
void setup()
{  
	for (int i = 0; i < 8; i++)
	{
		pinMode(leds[i], OUTPUT);     
	}
}

//method of displaying the letters. displaying each column (one hex number) of the letter one by one through PORTD. then after a letter, it puts a space in between and move onto the next letter. until however long of the String you wish to display.
//each letter is first turned into ASCII integer, then minus 65. It would then be the row of the letter from the library above. (ex. A is 65 in ASCII, but row 0 in my library)
// furthermore, because of the way i made the hardware, it displays each letter starting from the back of the sentence, and each letter from the right most column.

void display (char POVstring[])
{
	byte colpat = 0;
	for (int i=(strlen(POVstring)-1); i>=0; i--)
	{
		for (int j=(WIDTH-1); j>=0; j--)
		{
			//PORTD = font[(int)POVstring-65][j]; delay(1);
			colpat = font[(int)POVstring-65][j]; delay(1);
			short mask=1;
			for (int k=0; k < 7; k++, mask <<= 1)
				digitalWrite(leds[k],(mask & colpat)?HIGH:LOW);
		}
		//PORTD = B00000000; delay(1);
	}
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(leds[i], LOW);
	}
}

// you simply feed a string to display it. this code only allows capital letters. however, if you add characters or lowercases in the library above, it would also be able to display it. (but then it would minus a different number instead of 65 above)

void loop()
{
if ( analogRead(5)==0 )
 { display("HELLO"); }
}
