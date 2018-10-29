#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic :-)

WiFiManager wifiManager;


#include <IFTTTWebhook.h>
#include <WiFiClientSecure.h>
#define IFTTT_API_KEY "your API key here"
#define IFTTT_EVENT_NAME "button_pressed"
#define IFTTT_FINGERPRINT "AA:75:CB:41:2E:D5:F9:97:FF:5D:A0:8B:7D:AC:12:21:08:4B:00:8C"   //Actualizar en https://www.grc.com/fingerprints.htm

WiFiClientSecure client;
IFTTTWebhook webhook(IFTTT_API_KEY, IFTTT_EVENT_NAME, IFTTT_FINGERPRINT);


volatile bool BUTTON_state = false;

void button_pressed() {
  noInterrupts();
  BUTTON_state = true;
  interrupts();
}

void setup() {
  wifiManager.autoConnect("MARINO_ESP", "1234");

  attachInterrupt(D3, button_pressed, FALLING); //CHANGE, RISING, FALLING Lógica inversa

  Serial.begin(115200);

  Serial.println(WiFi.localIP());
}

void loop() {
  while (!BUTTON_state)
    yield();

  webhook.trigger();
 
  Serial.println("botón pulsado");  
  BUTTON_state = false;
}
