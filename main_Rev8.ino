/* |-----------------------------------------------------|
 * |--------- Dispositivo de Monitoreo Ambiental --------|
 * |---------- Environmental Monitoring Device ----------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 16 julio 2024 ---------|
 * |--------- Ultima Modificacion: 10 agosto 2024 -------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | Este código implementa una estación meteorológica   |
 * | portátil y open source para el monitoreo ambiental  |
 * | en tiempo real, diseñada para estudiar los procesos |
 * | de formación en la Tecnoacademia de Manizales. Este |
 * | dispositivo permite registrar y monitorear diversas |
 * | variables ambientales, proporcionando datos         |
 * | precisos y confiables para su posterior uso en      |
 * | estudios de analisis de los procesos de aprendizaje.|
 * |                                                     |
 * | Caracteristicas Principales:                        |
 * |                                                     |
 * | - Variables a medir: Temperatura, Humedad, Presión, |
 * |   Calidad del aire.                                 |
 * |                                                     |
 * | - Sensor BME680 de la marca Bosch: Integra todos    |
 * |   los sensores necesarios en un solo encapsulado.   |
 * |                                                     |
 * | - Almacenamiento de datos: Tarjeta microSD como     |
 * |   dispositivo de almacenamiento principal.          |
 * |                                                     |
 * | - Registro de tiempo real: Módulo RTC DS3231 que    |
 * |   permite registrar la hora de cada medición.       |
 * |                                                     |
 * | - Visualización de datos: Pantalla OLED de 0.96''   |
 * |   con encoder rotativo para una HMI.                |
 * |                                                     |
 * | - Autonomía energética: Sistema de recolección de   |
 * |   energía mediante un panel solar.                  |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#if defined(__AVR_ATmega2560__) // en caso de que se conecte un arduino MEGA, ejecutar las siguientes instrucciones: 
  #include <Wire.h> // Libreria necesaria para la comunicacion I2C entre los disferentes dispositivos y el arduino.
  #include <SPI.h> // Libreria necesaria para la comunicacion SPI entre el modulo Micro SD y el arduino.
  
  #pragma message "Codigo para Arduino basado AVR 2560 (MEGA)!"

#elif defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  #include <Wire.h> // Libreria necesaria para la comunicacion I2C entre los disferentes dispositivos y la ESP.
  #include <SPI.h> // Libreria necesaria para la comunicacion SPI entre el modulo Micro SD y la ESP.
  
  #pragma message "Codigo para NodeMCU ESP32!"

#elif defined(ESP8266) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  #include <Wire.h> // Libreria necesaria para la comunicacion I2C entre los disferentes dispositivos y la ESP.
  #include <SPI.h> // Libreria necesaria para la comunicacion SPI entre el modulo Micro SD y la ESP.
  
  #pragma message "Codigo para NodeMCU ESP8266!"  

#else // si se conecta cualquier otro tipo de placa, entonces:
  #pragma message "No es ni ESP32 o ES8266 o AVR, que es?"
  
#endif

// Incluir librerias PROPIAS que contienen secciones del codigo de cada componentes fisico: 
#include "BMP280.h" // Libreria que contiene las secciones de codigo relacionadas con el sensor BMP280.
#include "RTC.h" // Libreria que contiene las secciones de codigo relacionadas con el sensor RTC DS3231.
#include "MicroSD.h" // Libreria que contiene las secciones de codigo relacionadas con el lector de tarjetas microSD.
#include "Encoder.h" // Libreria que contiene las secciones de codigo relacionadas con el Encoder KY-040.
#include "OLED.h" // Libreria que contiene las secciones de codigo relacionadas con la pantalla OLED 0.96 pulg.
#include "DebugData.h" // Libreria que contiene las secciones de codigo relacionadas con el sensor BMP280.
#include "WiFiConfig.h" // Libreria que contiene las secciones de codigo relacionadas con la conexion Wifi de la ESP.
//#include "OtaSetup.h" // Libreria que contiene las secciones de codigo relacionadas con el protocolo OTA que permite programar la ESP via WIFI.


/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
 void setup() {
  Serial.begin(9600); // Inicializar Comunicacion Serial.
  Wire.begin(); // Inicializar comunicacion I2C.
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  printHeader(); // Funcion que imprime el encabezado de presentacion del codigo.
  initEncoder(); // Funcion que se encarga de inicializar y configurar el Encoder. 
  initBMP280(); // Funcion que se encarga de inicializar y configurar el sensor BMP280.
  initRTC(); // Funcion que se encarga de inicializar y configurar el modulo RTC.
  initOLED(); // Funcion que se encarga de inicializar y configurar la pantalla OLED.
  initSD(); // Funcion que se encarga de inicializar y configurar el modulo microSD.
  initWiFi(); // Funcion que configura la conexion WiFi de la ESP.
  //initOTA(); // Funcion que se encarga de configurar el Protocolo OTA para programacion Inalambrica.
  initBlynk(); // // funcion para configurar la comunicacion con la plataforma de blynk. 
  
  printCustomMessage("Bienvenido"); // Mostrar mensaje de bienvenida.
  delay(2000);
  getEnvironmentalData(); // sensar por primera vez, para tener valores que mostrar en pantalla. 
  oled.clearDisplay(); // Limpar pantalla despues de dos (2) segundos.
}


/* |-----------------------------------------------------|
 * |------------------ Codigo Principal -----------------|
 * |-----------------------------------------------------| */
void loop(){
  BlynkRun(); // llamar a la funcion que se encarga de gestionar la comunicacion, lectura, y envio de datos entre la ESP y la plataforma Blynk. 
  //OtaRun(); // Llamar a la funcion que se encarga de gestionar el protocolo de comunciacion OTA. 
  readEncoder(); // llamar a la funcion que lee el estado del encoder y su posicion. la lectura sera en tiempo real, sin intervalos de interrupcion.
  
  // condicional que se encarga de refrescar la pantalla OLED cada cierto intervalo de tiempo, esto sin el uso de delay: 
  if((millis() - refreshTime) > refreshInterval){
    refreshTime = millis(); // Actualizar Tiempo actual para proximo ciclo.
    
    printMenu(); // Imprimir los diferentes menus y submenus. 
    // printEncoderData(); // Imprimir valores sensados por el Encoder.
  }
  
  if((millis() - samplingTime) > samplingInterval){
    samplingTime = millis(); // Actualizar Tiempo actual para proximo ciclo.
    
    // Registrar las Mediciones desde el sensor BMP y el RTC:
    readRTC();
    getEnvironmentalData(); // llamar a la funcion que se encarga de sensar las variables fisicas.
    logDataSD(); // grabar valores sensados por el sensor BMP280 y el RTC en la memoria microSD.
    printSensorData(); // Imprimir Valores sensados por el BMP280 en el monitor Serial.
  }
}
