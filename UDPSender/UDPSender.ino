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

/**
 * 初期設定
 */
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
}

void loop(void)
{

    char message[8];
    if (val == 0) {
      message[0] = '0'; 
    } else {
      message[0] = '1';
    }
    Serial.println(val);
    
    wifi.send((const uint8_t*)message, strlen(message));
    if (val == 0) {
      val = 1;
    } else {
      val = 0;
    }
    delay(1000);
 }
