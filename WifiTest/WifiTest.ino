#include <ESP8266WiFi.h>
 
const char* ssid     = "SPWN_N34_5f1166";
const char* password = "10b1a28af519c";
 
void setup() {
  Serial.begin(115200);
  
  // WIFI_AP, WIFI_STA, WIFI_AP_STA or WIFI_OFF
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFiに接続しました。");  
  Serial.print( "IPアドレス： "); 
  Serial.println( WiFi.localIP());
  Serial.print( "ゲートウェイ： "); 
  Serial.println(WiFi.gatewayIP());
  Serial.print( "サブネットマスク： "); 
  Serial.println(WiFi.subnetMask());
}
 
void loop() {
  // none
}
