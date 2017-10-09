#include <ESP8266WiFiMulti.h>

// ThingSpeak Settings
const int channelID = 343024;
String writeAPIKey = "IIMUPX6LPZ8X0V1I";
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000; // post data every 20 seconds

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

bool BUTTON_state = false;
void button_pressed() {
  BUTTON_state = true;
}

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  WiFiMulti.addAP("Orange-152A", "3EE529C4"); //tantos addAP como queramos, el conecta al mejor RSSI
  WiFiMulti.addAP("marinoAP", "eraseunavez"); //tantos addAP como queramos, el conecta al mejor RSSI

  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
    
  attachInterrupt(D3, button_pressed, FALLING); //CHANGE, RISING, FALLING Lógica inversa

  Serial.println("");

}

void loop() {
  if (BUTTON_state) {
    if (client.connect(server, 80)) {
      Serial.println("conectado al servidor");

      // Construct API request body
      String body = "field1=1";

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(body.length());
      client.print("\n\n");
      client.print(body);
      client.print("\n\n");
    }
    
    if (!client.connected())
      client.stop();
    
    // wait and then post again
    //delay(postingInterval);
  }

  BUTTON_state=false;
  
  while (!BUTTON_state)
    yield();

  Serial.println("botón pulsado");
}

