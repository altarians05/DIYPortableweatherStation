/* -----------------------------------------------------------------
------------------------- Codigo MultiHardWare ---------------------
----------------------------------------------------------------- */
#if defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  #include <WiFi.h> // incluir libreria que contiene las funciones para la conexion de la ESP como STA.
  #include <WiFiClient.h>
  #include <WiFiMulti.h> // incuir libreria para hacer uso de instrucciones que permiten a la ESP acceder a mas de una Red WiFi.  

  /* Completar Valores utilizando los que se asignan en blynk.cloud */
  #define BLYNK_TEMPLATE_ID     "TMPL2lnqp-f92"
  #define BLYNK_TEMPLATE_NAME   "GreenMetrics DashBoard"
  #define BLYNK_AUTH_TOKEN      "ErR-HdjRN4xTNhd1qktKC4oEhxCDtPWy"
  
  #include <BlynkSimpleEsp32.h> // incluir libreria para hacer uso de las instrucciones que permiten a la ESP comunicarse con los servidores de Blynk.
  
  #define WIFILEDPIN     2  // GPIO 02 - Led Integrado NodeMcu

  WiFiMulti wifiMulti; // Crear objeto para el uso de metodos relacionados con la libreria WiFi Multi.

#elif defined(ESP8266) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  #include <ESP8266WiFi.h> // incluir libreria que contiene las funciones para la conexion de la ESP como STA.
  #include <ESP8266WiFiMulti.h> // incuir libreria para hacer uso de instrucciones que permiten a la ESP acceder a mas de una Red WiFi.  

  /* Completar Valores utilizando los que se asignan en blynk.cloud */
  #define BLYNK_TEMPLATE_ID     "TMPL2lnqp-f92"
  #define BLYNK_TEMPLATE_NAME   "GreenMetrics DashBoard"
  #define BLYNK_AUTH_TOKEN      "ErR-HdjRN4xTNhd1qktKC4oEhxCDtPWy"

  
  #include <BlynkSimpleEsp8266.h> // incluir libreria para hacer uso de las instrucciones que permiten a la ESP comunicarse con los servidores de Blynk.
  
  #define WIFILEDPIN     D4  // GPIO 02 - Led Integrado NodeMcu

  ESP8266WiFiMulti wifiMulti; // Crear objeto para el uso de metodos relacionados con la libreria WiFi Multi.

#else // si se conecta cualquier otro tipo de placa, entonces:
  #pragma message "No es ni ESP32 o ES8266 o AVR, que es?"
  
#endif


/* -----------------------------------------------------------------
-------------------------- Librerias y Objetos ---------------------
----------------------------------------------------------------- */
#include <Ticker.h> // incluir libreria que permite realizar "pausas" sin necesidad de aplicar delays.
#include <WiFiUdp.h> 
#include <ArduinoOTA.h> // incluir libreria para hacer uso de funciones relacionadas con el protocolo OTA.

Ticker WiFiLed; // Crear objeto para el uso de metodos relacionados con la libreria Ticker.
BlynkTimer timer; // Controlar intervalos de tiempo para enviar datos a blynk.cloud.


/* -----------------------------------------------------------------
---------------- Declaracion de Variables y constantes -------------
----------------------------------------------------------------- */
// Definir Credenciales para redes WiFi:
const char* ssid_1     = "HP_LaserJet_3245";
const char* password_1 = "Sena.12345";
const char* ssid_2     = "estudiantes";
const char* password_2 = "ca19532014";
const char* ssid_3     = "Casa Valencia";
const char* password_3 = "1053849072";

const uint32_t TiempoEsperaWifi = 5000; // variable que se utilizara para definir el tiempo de espera entre las diferentes Redes WiFi antes de pasar a la siguiente. por defecto es de 500 mseg.

// Declarar Puertos virtuales para los Gadgets de Blynk.cloud:
#define VPIN_TEMPERATURE   V0
#define VPIN_PRESION       V1
#define VPIN_ALTITUDE      V2


/* -----------------------------------------------------------------
--------------------------- Funciones Propias ----------------------
----------------------------------------------------------------- */
void parpadeoLedWiFi(){ // Funcion propia que se encarga de hacer parpadear un LED. debe estar antes del void Setup ya que se utilizara alli.
  boolean Estado = digitalRead(WIFILEDPIN);
  digitalWrite(WIFILEDPIN, !Estado);
}


void initWiFi(){ // Funcion que se encarga de configurar la conexion WiFi.
  pinMode(WIFILEDPIN, OUTPUT); // Defini Pin de LED como salida.
  
  WiFiLed.attach(0.2, parpadeoLedWiFi); // configurar la repeticion de funcion cada 200 milisegundos utilizando la libreria ticker. 
  
  // Definir las diferentes tipos de redes o Access Points a conectar con sus respectivas credenciales. 
  wifiMulti.addAP(ssid_3, password_3); // Red de la Casa
  wifiMulti.addAP(ssid_2, password_2); // Red de la Universidad
  wifiMulti.addAP(ssid_1, password_1); // Red del Celular

  WiFi.mode(WIFI_STA); // Definir que la ESP trabajara como una estacion, es decir, como dispositivo esclavo.
  Serial.print("Conectando a Wifi ..");
  
  // Generar un bucle que impide que el programa continue hasta que se establezca la conexion a una de las redes definidias previamente. cambia de red cada 5 seg en caso que no conecte la anterior. 
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  
  // si pasa el bucle anterior, quiere decir que se establecio conexion a una de las redes.
  Serial.println("Conectado \n");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID()); // imprimir nombre de la red wifi a la que esta conectada la ESP.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  WiFiLed.detach(); // desactivar repeticion de funcion de parpadeo. 
  digitalWrite(WIFILEDPIN, !LOW);
}


void checkBlynkStatus(){ // Funcion que comprueba el estado de conexion de la ESP:
  bool isconnected = Blynk.connected();
  if (isconnected == false){
    //Serial.println("Blynk NO CONECTADO");
    digitalWrite(WIFILEDPIN, !HIGH);
  }
  if (isconnected == true){
    //Serial.println("Blynk CONECTADO");
    digitalWrite(WIFILEDPIN, !LOW);
  }
}


void sendBlynkData(){
  getEnvironmentalData();
  
  Blynk.virtualWrite(VPIN_TEMPERATURE, round(temp));
  Blynk.virtualWrite(VPIN_PRESION, round(pres));  
  Blynk.virtualWrite(VPIN_ALTITUDE, round(alti));  
}


BLYNK_CONNECTED() { // Funcion que se encarga de sincronizar los datos de la ESP con la nube. 
  Blynk.syncVirtual(VPIN_TEMPERATURE);
  Blynk.syncVirtual(VPIN_PRESION);
  Blynk.syncVirtual(VPIN_ALTITUDE);
}


void initBlynk(){ // funcion para configurar la comunicacion con la plataforma de blynk. 
  Blynk.config(BLYNK_AUTH_TOKEN); // Establece la conexion WiFi y se sincroniza con Blynk.cloud
  
  timer.setInterval(3000L, checkBlynkStatus); // Revisar la conexion con el servidor de blynk cada "samplingInterval" + 1 min.
  timer.setInterval(2000L, sendBlynkData); // tomar mediciones cada "samplingInterval" y enviarlos a blynk
}


void BlynkRun(){
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
