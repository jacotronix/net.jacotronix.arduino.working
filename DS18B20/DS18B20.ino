#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x3F  // Define I2C Address where the SainSmart LCD is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

unsigned int localPort = 8888;      // local port to listen on
IPAddress ip(192, 168, 2, 48);
IPAddress remoteIP(192, 168, 2, 43);

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// Data wire is plugged into pin 2 on the Arduino (can be any digital I/O pin)
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

int numberOfSensors;
float temp1 = 0;
float temp2 = 0;

char msgBuffer[20];
char floatBuff[6];
int count = 0;
String msgToSend = "BS18B20:";

void setup()
{

  /* add setup code here */
  // start serial port
  Serial.begin(115200);
  Serial.println("1-Wire DS18B20 example code");
 
  // Start up the library
  sensors.begin();
 
  delay(5000);  //important on linux as serial port can lock up otherwise
  numberOfSensors = discoverOneWireDevices();
  Serial.println();

  lcd.begin (20,4);
  
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  // Position cursor and write some text
  lcd.home ();                   // go to the first line, first character
  lcd.print("DS18B20 Temp Monitor");  
  lcd.setCursor ( 0, 1 );        // go to the 2nd line
  lcd.print("Sensors: ");
  lcd.print(numberOfSensors);
  lcd.setCursor ( 0, 2 );        // go to the third line
  lcd.print("");
  lcd.setCursor ( 0, 3 );        // go to the fourth line
  lcd.print("");

  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);

}

void loop()
{
  /* add main program code here */
  //printTemperaturesToSerial();
  sensors.requestTemperatures();
  temp1 = sensors.getTempCByIndex(0);
  lcd.setCursor ( 0, 2 );        // go to the third line
  lcd.print("Sen0: ");
  lcd.print(temp1);
  lcd.print(" Deg C");
  temp2 = sensors.getTempCByIndex(1);
  lcd.setCursor ( 0, 3 );        // go to the third line
  lcd.print("Sen1: ");
  lcd.print(temp2);
  lcd.print(" Deg C");

  Udp.beginPacket(remoteIP, 8888);

  dtostrf(temp1,5,2,floatBuff);
  msgToSend.concat(floatBuff);
  msgToSend += ":";
  dtostrf(temp2,5,2,floatBuff);
  msgToSend.concat(floatBuff);

  msgToSend.toCharArray(msgBuffer, 20);
  Udp.write(msgBuffer);
    Udp.endPacket();
	delay(1000);
  Serial.print(msgBuffer);
  Serial.print('\n');
  msgToSend = "BS18B20:";

  delay(5000); //wait 10 sec
}

void printTemperaturesToSerial(void) {
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
 
  // Read each of our sensors and print the value
  for(int i=0; i < numberOfSensors; i++) {
   Serial.print("Temperature for Device ");
   Serial.print( i );
   Serial.print(" is: ");
   // Why "byIndex"? You can have more than one IC on the same bus. 
   // 0 refers to the first IC on the wire
   Serial.println( sensors.getTempCByIndex(i) );
  }
 
  Serial.println();
}

int discoverOneWireDevices(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  int count = 0;
 
  Serial.println("Looking for 1-Wire devices...");
  while(oneWire.search(addr)) {
    Serial.print("Found \'1-Wire\' device with address: ");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.println("CRC is not valid!");
        return 0;
    }
    Serial.println();
    count++;
  }
  Serial.println("That's it.");
  oneWire.reset_search();
  return count;
}