#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const char* ssid = "Network SSID Name";
const char* password = "Network Password";

// Variables to be exposed to the API
// Auxiliar variables to store the current output state
String output26State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;

AsyncWebServer server(80);


int turnOnLedFunction(String command) {
  Serial.println("Received rest request: turnOnLedFunction");
              output26State = "on";
              digitalWrite(output26, HIGH);
  return 1;
}

int turnOffLedFunction(String command) {
  Serial.println("Received rest request: turnOffLedFunction");
              output26State = "off";
              digitalWrite(output26, LOW);
          return 1;
}
 
void setup(){
  Serial.begin(115200);
 
    // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
 
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  
  WiFi.begin(ssid, password);


 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");
  });

  server.on("/turnOn26", HTTP_GET, [](AsyncWebServerRequest *request){
    turnOnLedFunction("");
        request-> send(200, "text/plain", "26 Turned ON");
  });

  server.on("/turnOff26", HTTP_GET, [](AsyncWebServerRequest *request){
    turnOffLedFunction("");
        request-> send(200, "text/plain", "26 Turned OFF");
  });
 
  server.begin();
}
 
void loop(){}
