#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID "aterm-9cfae4-g"
#define PASSWORD "7ee8bf365a669"
#define HOST_NAME "192.168.10.103"
#define HOST_PORT 7777

int n = 0;

SoftwareSerial mySerial(2, 4);  //RX, TX
ESP8266 wifi(mySerial);

int val = 0;

void setup(void)
{
  Serial.begin(9600);

  if (wifi.setOprToStationSoftAP()) {
    Serial.println("to station ok");
  } else {
    Serial.println("to station error");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.println("connect success");
  } else {
    Serial.println("connect error");
  }

  if (wifi.disableMUX()) {
    Serial.println("disable mux success");
  } else {
    Serial.println("disable mux error");
  }
  if (wifi.registerUDP(HOST_NAME, HOST_PORT)) {
    Serial.print("register udp ok\r\n"); 
  } else {
    Serial.print("register udp err\r\n");
  }

  Serial.println(wifi.getIPStatus());
}

void loop() {
//  Serial.println(wifi.getIPStatus());
  uint8_t buffer[1024] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
    Serial.println("received");
    for (uint32_t i=0; i<len; i++) {
      Serial.println((char)buffer[i]);
    }
  }
}
