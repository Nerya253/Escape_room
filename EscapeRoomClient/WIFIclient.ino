#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Project";
const char* pswd = "88888888";

WiFiClient client;
int server_port = 80; 

void wifi_Setup() {
  Serial.println("wifiSetup");
  WiFi.begin(ssid);
  //    WiFi.begin(ssid, pswd);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("trying ...");
    delay(100);
  }
  Serial.println("Connected to network");
}

void SendData(int val) {
  HTTPClient http;
  String dataURL = "";
  dataURL += "ACT=SET&DEV=1121&CH=1";
  dataURL += "&VAL=" + String(val);
  http.begin(client, "55.55.55.55/GEN/api.php?" + dataURL);
  int httpCode = http.GET();
  Serial.println(httpCode);
  http.end();
}

int GetData() {
  int ret = -1;
  HTTPClient http;
  String dataURL = "";
  dataURL += "ACT=GET&DEV=177944&CH=55";
  http.begin(client, "http://api.kits4.me/GEN/api.php?" + dataURL);
  int httpCode = http.GET();
  Serial.println(httpCode);
  if (httpCode == HTTP_CODE_OK) {
    Serial.print("HTTP response code ");
    Serial.println(httpCode);
    String Res = http.getString();
    Serial.println(Res);
    ret = Res.toInt();
  }
  http.end();

  return ret;
}