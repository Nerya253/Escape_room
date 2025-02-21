#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "project";
const char* pswd = "88888888";

WiFiClient client;
int server_port = 80; 

unsigned long previousMillis = 0;


void wifi_Setup() {
  Serial.println("wifiSetup");
     WiFi.begin(ssid, pswd);
     previousMillis = millis();

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("trying ...");
    if(millis() - previousMillis >= 100){
      previousMillis = millis();
    }
   
  }
  Serial.println("Connected to network");

  SendData();
}


void SendData(int digit) {
  HTTPClient http;
  http.begin(client, "http://55.55.55.55/addDigit?digit=" + digit);
  int httpCode = http.GET();
  Serial.println(httpCode);
  http.end();
}




