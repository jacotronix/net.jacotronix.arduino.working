int red = 11;
int blue = 10;
int green = 9;

int i = 0; // for loops
int j = 0;
void setup()
{
  pinMode(red, OUTPUT); // tell Arduino LED is an output
  pinMode(blue, OUTPUT); // tell Arduino LED is an output
  pinMode(green, OUTPUT); // tell Arduino LED is an output
}

void loop()
{
  for (i = 0; i < 255; i++)
  { // loop from 0 to 254 (fade in)
    analogWrite(red, i);      // set the LED brightness
    delay(20); // Wait 10ms because analogWrite isn't instant
  }
  analogWrite(red,0); 
  
  for (i = 0; i < 255; i++)
  { // loop from 0 to 254 (fade in)
    analogWrite(blue, i);      // set the LED brightness
    delay(20); // Wait 10ms because analogWrite isn't instant
  }
  analogWrite(blue,0); 
  
  for (i = 0; i < 255; i++)
  { // loop from 0 to 254 (fade in)
    analogWrite(green, i);      // set the LED brightness
    delay(20); // Wait 10ms because analogWrite isn't instant
  }
  analogWrite(green,0);

  for (j = 1; j < 10000; j++)
  {
    analogWrite(red,random(255)); // set red at random brightness between 0 and 254
    delay (random(10,31));           // wait for a random duration between 10 and 30 milliseconds
    analogWrite(green,random(255));
    delay (random(10,31));
    analogWrite(blue,random(255));
    delay (random(10,31));
  }
}
