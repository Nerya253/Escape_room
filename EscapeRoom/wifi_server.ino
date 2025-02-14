#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <DIYables_4Digit7Segment_74HC595.h> 

#define SCLK  D5 
#define RCLK  D6 
#define DIO   D7  

IPAddress apIP(55,55,55,55);

const char* ssid = "Project";  
const char* password = "88888888";  

ESP8266WebServer server(80);

DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO);

unsigned long previousMillis = 0; 

void WiFi_setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  Serial.println("HTTP server started");
  server.begin();
  previousMillis = millis();
  // display.printInt(-13, false);  כתיבה על הלוח
}

void WiFi_loop() {
  display.loop();

  if(millis()- previousMillis >= 10)
  {
    server.hendleClient();
    previousMillis = millis();
  }
}

void handleNotFound() {
  String message = "File Not Found \n \n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

 
void handleRoot() {
  
  String html = R"rowliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Escape Room Code</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #2c3e50;
            color: #ecf0f1;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }

        .form-container {
            background-color: #34495e;
            padding: 20px 30px;
            border-radius: 10px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            text-align: center;
            width: 300px;
        }

        h1 {
            margin-bottom: 20px;
        }

        input[type="text"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 15px;
            border: none;
            border-radius: 5px;
        }

        button {
            background-color: #1abc9c;
            color: #fff;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
        }

        button:hover {
            background-color: #16a085;
        }

        .message {
            margin-top: 15px;
            font-size: 14px;
        }
    </style>
</head>
<body>
    <div class="form-container">
        <h1>Enter Game Code</h1>
        <form id="codeForm">
            <input type="text" id="gameCode" name="gameCode" placeholder="Enter the code" required>
            <button type="submit">Submit</button>
        </form>
        <div id="message" class="message"></div>
    </div>
</body>
</html>
    )rowliteral";

  server.send(200, "text/html", html);
}

