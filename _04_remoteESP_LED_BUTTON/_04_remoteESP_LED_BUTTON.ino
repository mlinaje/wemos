#include <ESP8266WiFiMulti.h>

const char* server = "192.168.43.235";
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

      client.print("POST /LED/TOGGLE HTTP/1.1\n");
      client.print("Host: 192.168.43.235\n");
      client.print("Connection: close\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("\n\n");
    }
    
    if (!client.connected())
      client.stop();    
  }

  BUTTON_state=false;
  
  while (!BUTTON_state)
    yield();

  Serial.println("botón pulsado");
}

