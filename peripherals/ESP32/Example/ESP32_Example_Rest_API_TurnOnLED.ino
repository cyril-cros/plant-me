
// Based on
// https://techtutorialsx.com/2017/10/12/esp32-getting-started-with-the-arest-library/
// https://randomnerdtutorials.com/esp32-web-server-arduino-ide/

// To Test call the GET HTTP request
// http://#yourIp#/test
// http://#yourIp#/turnOn26
// http://#yourIp#/turnOff26

#include "WiFi.h"
#include "aREST.h"
 
aREST rest = aREST();
 
WiFiServer server(80);
 
const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPassword";


// Auxiliar variables to store the current output state
String output26State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;

 
int testFunction(String command) {
  Serial.println("Received rest request");
}

int turnOnLedFunction(String command) {
  Serial.println("Received rest request: turnOnLedFunction");
              output26State = "on";
              digitalWrite(output26, HIGH);
}

int turnOffLedFunction(String command) {
  Serial.println("Received rest request: turnOffLedFunction");
              output26State = "off";
              digitalWrite(output26, LOW);
}
 
void setup()
{
 
  Serial.begin(115200);
   // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
 
  // Set outputs to LOW
  digitalWrite(output26, LOW);

  
  rest.function("test",testFunction);
  rest.function("turnOn26",turnOnLedFunction);
  rest.function("turnOff26",turnOffLedFunction);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
  server.begin();
 
}
 
void loop() {
 
  WiFiClient client = server.available();
  if (client) {
 
    while(!client.available()){
      delay(5);
    }
    rest.handle(client);
  }
}
