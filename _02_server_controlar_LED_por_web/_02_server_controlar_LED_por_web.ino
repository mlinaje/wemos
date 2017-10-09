#include <ESP8266WiFi.h>
#define LED_Pin D2
bool LED_Estado=0;

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED_Pin, NEO_GRB + NEO_KHZ800);

//const char* ssid = "Orange-152A";
//const char* password = "3EE529C4";
const char* ssid = "marinoAP";
const char* password = "eraseunavez";

WiFiServer server(80); //objeto servidor que inicializaremos en el puerto 80
 
void setup() {
  Serial.begin(115200);

  pixels.begin();
  
  // Poner el módulo WiFi en modo station y desconectar de cualquier red a la que pudiese estar previamente conectado
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);

  pinMode(LED_Pin, OUTPUT);
  
  //Conectar a la red WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado, la IP del dispositivo es: ");
  Serial.println(WiFi.localIP());

  for(int i = 3; i>0; i--){
    pixels.setPixelColor(0, pixels.Color(0,150,0));
    pixels.show(); 
    delay(500);
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show(); 
    delay(500);    
  }

  //Iniciar server
  server.begin();
  Serial.println("Servidor iniciado");
}
 
void loop() {
  //chequeamos si se ha conectado un cliente, en caso contrario terminar (se reiniciaría)
  WiFiClient client = server.available();
  if (!client)
    return;
 
  //Esperar hasta que el cliente envíe algún dato
  while(!client.available())
    yield();
 
  //Lee la request del cliente
  String request = client.readStringUntil('\r');
  client.flush(); //vacía por seguridad

  //Request en un objeto String que contiene la URL compelta, incluyendo parámetros. Buscamos si contien la cadena "/RELE=ON"
  if (request.indexOf("/LED/ON") != -1){
    pixels.setPixelColor(0, pixels.Color(150,0,150));
    //debería ser HIGH, pero funciona en modo inverso en algunas placas, includo la nodemcu
    pixels.show();
    LED_Estado=1;
    Serial.println("Encendido");
  }
  else
    if (request.indexOf("/LED/OFF") != -1){
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.show();
      LED_Estado=0;
      Serial.println("Apagado");
    }
    else
      if (request.indexOf("/LED/TOGGLE") != -1){
        if (LED_Estado==0)
          pixels.setPixelColor(0, pixels.Color(150,0,150));
        else
          pixels.setPixelColor(0, pixels.Color(0,0,0));
        pixels.show();
        LED_Estado=!LED_Estado;
        Serial.println("Conmutado");
      }
      
  //Parte "response" del servidor hacia el cliente, una página Web
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //requerido
  client.println("<!DOCTYPE HTML>");
  client.println("<meta name='viewport' content='width=device-width, user-scalable=no'>");
  client.println("<html>");
 
  client.print("<p>LED ");
  if(LED_Estado)
    client.print("encendido</p><br>");
  else
    client.print("apagado</p><br>");

  client.println("<a href=\"/LED/ON\"><button style='width:100%;height:50px;background:#6C0;'>Encender</button></a>");
  client.println("<a href=\"/LED/OFF\"><button style='width:100%;height:50px;background:#C00;'>Apagar</button></a><br />");
  client.println("<a href=\"/LED/TOGGLE\"><button style='width:100%;height:50px;background:#09F;'>Conmutar</button></a><br />");
  client.println("</html>");
 
  delay(1);
  Serial.println("Cliente desconectado");
  Serial.println(""); 
}
