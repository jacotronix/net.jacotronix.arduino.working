#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

unsigned int localPort = 8888;      // local port to listen on
unsigned int remotePort = 8888;
IPAddress ip(192, 168, 2, 48);
IPAddress remoteIP(192, 168, 2, 43);

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {

  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
}

void loop() {

  Udp.beginPacket(remoteIP, remotePort);
    Udp.write("hello");
    Udp.endPacket();

  delay(1000);
}