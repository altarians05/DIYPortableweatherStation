/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Sensor BMP280:                                      |
 * |    SCL -> PIN 21 (MEGA) - GPIO22 (ESP32)            |
 * |    SDA -> PIN 20 (MEGA) - GPIO21 (ESP32)            |
 * |    Vin -> 5v ESP                                    |
 * |    GND -> Ground ESP                                |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Sensor BMP280:                                      |
 * | - Libreria: https://n9.cl/2wgdx                     |
 * | - Guia de Funcionamiento: https://n9.cl/31472       |
 * | - Tutorial Simple: https://n9.cl/s88k9              |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#if defined(__AVR_ATmega2560__) // en caso de que se conecte un arduino MEGA, ejecutar las siguientes instrucciones: 
  #include <Adafruit_Sensor.h> // Libreria requerida para la programacion de todos los sensores de marca Adafruit.
  #include <Adafruit_BMP280.h> // Libreria que contiene las instrucciones especificas para el sensor BMP280.

  #define SEALEVELPRESSURE_HPA 1013.25 // Constante utilizada para determinar la presion a nivel del mar (Cartagena) que es 760 mmHg = 1013.25 hPa.   

#elif defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  #include <Adafruit_Sensor.h> // Libreria requerida para la programacion de todos los sensores de marca Adafruit.
  #include <Adafruit_BMP280.h> // Libreria que contiene las instrucciones especificas para el sensor BMP280.

  #define SEALEVELPRESSURE_HPA 1013.25 // Constante utilizada para determinar la presion a nivel del mar (Cartagena) que es 760 mmHg = 1013.25 hPa.   

#elif defined(ESP8266) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  #include <Adafruit_Sensor.h> // Libreria requerida para la programacion de todos los sensores de marca Adafruit.
  #include <Adafruit_BMP280.h> // Libreria que contiene las instrucciones especificas para el sensor BMP280.

  #define SEALEVELPRESSURE_HPA 1013.25 // Constante utilizada para determinar la presion a nivel del mar (Cartagena) que es 760 mmHg = 1013.25 hPa.   
 
#endif


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
Adafruit_BMP280 BMP; // Crear objeto BMP para usar los metodos y clases del sensor respectivo.

// variables para almacenar los valores relacionados con el sensor:
float temp, pres, alti; // Variables Fisicas.
int freq = 1; // frecuencia de lectura de los sensores.
unsigned long baseTime = 3000; // base de tiempo para calcular la cantidad de muestras a tomar (5 min = 300000 mseg). 

// Variables y constantes Utilizadas para reemplazar el delay con la funcion millis():
unsigned long samplingTime = 0;
unsigned long samplingInterval = 0;

/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void initBMP280(){ // Funcion que se encarga de inicializar y configurar el sensor BMP280:
  Serial.print("Iniciando Sensor BMP280...");
  
  for(int i=0; i<=10; i++){ // Bucle de 10 intentos para comprobar comunicacion con el sensor BMP280:
    if(!BMP.begin()){
      Serial.print(".");
      delay(1000);
    } else{
      Serial.print(" ¡Sensor BMP280 Encontrado!\n");
      break;
    }

    if(i==10){
      Serial.println(" Error al inicializar el Sensor BMP280.");
      Serial.println("1. Revisa la Conexion.");
      Serial.println("2. Reinicia el arduino.");
      Serial.println("3. vuelve a intentarlo.");
      while(1){};
    }
  }
}


void getEnvironmentalData(){ // funcion que recolecta los datos desde los sensores: 
  samplingInterval = baseTime/freq; // calcular el tiempo de muestreo basado en la frecuencia. 
  
  temp = BMP.readTemperature(); // Funcion para leer la temperatura. 
  pres = BMP.readPressure()/100; // Funcion para leer la Presion. Se divide en 100 porque el sensor lee en Pascales, y se necesitan hPa.
  alti = BMP.readAltitude(SEALEVELPRESSURE_HPA); // se pasa como parametro la presion atmosferica a nivel del mar en colombia.    
}
