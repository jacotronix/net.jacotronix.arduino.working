#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

unsigned int localPort = 8888;      // local port to listen on
IPAddress ip(192, 168, 2, 48);
IPAddress remoteIP(192, 168, 2, 43);

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

char buffer[20];
char floatBuff[6];
int count = 0;
String msgToSend = "Packet: ";
float f1 = 23.45;
float f2 = 12.34;

void setup() {

  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
}


void loop() {

  Udp.beginPacket(remoteIP, 8888);


  //dtostrf(f1,5,2,floatBuff);
  //msgToSend.concat(floatBuff);
  //msgToSend += ":";
  //dtostrf(f2,5,2,floatBuff);
  //msgToSend.concat(floatBuff);

  msgToSend.toCharArray(buffer, 20);
  Udp.write(buffer);
    Udp.endPacket();
	delay(1000);
  msgToSend = "Packet: ";
}