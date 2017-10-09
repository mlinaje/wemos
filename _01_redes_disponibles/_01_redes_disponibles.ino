#include "ESP8266WiFi.h"

char num, caracter;
String password;

void setup() {
  Serial.begin(115200);
  // Poner el módulo WiFi en modo station y desconectar de cualquier red a la que pudiese estar previamente conectado
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
}

void loop() {  
  Serial.println("Escaneando el entorno...");
  int n = WiFi.scanNetworks();
  if (n == 0)
    Serial.println("no hay redes en el rango de alcance");
  else{
    Serial.print(n);
    Serial.println(" redes en el rango del dispositivo");
    for (int i = 0; i < n; ++i)
    {
      //Imprime SSID (nombre) y RSSI (potencia) para cada red encontrada
      Serial.print(i);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
    }
    Serial.print(n);
    Serial.println(": volver a escanear");

    while (!Serial.available()); //esperar hasta que haya algo tecleado en la consola
    //num = Serial.read() - 48; //leer lo que se ha tecleado (un carácter) y convertirlo a número
    num=Serial.readString().toInt();
    
    if (num<n){//Si no se ha escogido la opción de salir

      //Si requiere password preguntar al usuario para que la introduzca
      if (WiFi.encryptionType(num) != ENC_TYPE_NONE){
        Serial.println("introduce el password: ");
        while (!Serial.available()); //esperar hasta que haya algo tecleado en la consola
        password = Serial.readString(); //leer lo que se teclea por COM (string)
      }

      Serial.print("Conectando a ");
      Serial.println(WiFi.SSID(num));
  
      WiFi.begin(WiFi.SSID(num).c_str(), password.c_str()); //Si se conoce el user password bastaría con escribirlo WiFi.begin("user", "pass");        
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
        
      Serial.println("WiFi connected");  
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    
      while(1)
        yield(); //aquí iría el código a ejecutar cuando ya sabemos que estamos conectados a la red!
    }  
  }//fin else
}//fin loop
