#include "ESP8266.h"

#define SSID "SPWN_N34_5f1166"  //"aterm-9cfae4-g"
#define PASSWORD "10b1a28af519c"  //"7ee8bf365a669"
#define HOST_NAME "192.168.179.6"
#define HOST_PORT 7777

ESP8266 wifi(Serial1);
 
void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");
    
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
      
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
 
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");
        Serial.println(wifi.getLocalIP().c_str());       
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }
    
    Serial.print("setup end\r\n");
}
 
void loop(void)
{
    uint8_t buffer[128] = {0};
    static uint8_t mux_id = 0;
    
    if (wifi.registerUDP(mux_id, HOST_NAME, HOST_PORT)) {
        Serial.print("register udp ");
        Serial.print(mux_id);
        Serial.println(" ok");
    } else {
        Serial.print("register udp ");
        Serial.print(mux_id);
        Serial.println(" err");
    }
    
    char *hello = "Hello, this is client!";
    wifi.send(mux_id, (const uint8_t*)hello, strlen(hello));
    
    uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
    }
    
    if (wifi.unregisterUDP(mux_id)) {
        Serial.print("unregister udp ");
        Serial.print(mux_id);
        Serial.println(" ok");
    } else {
        Serial.print("unregister udp ");
        Serial.print(mux_id);
        Serial.println(" err");
    }
    delay(5000);
    mux_id++;
    if (mux_id >= 5) {
        mux_id = 0;
    }
}
