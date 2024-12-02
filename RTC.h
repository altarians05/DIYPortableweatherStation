/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Modulo RTC DS3231:                                  |
 * |    SCL -> PIN 21 (MEGA) - GPIO22 (ESP32)            |
 * |    SDA -> PIN 20 (MEGA) - GPIO21 (ESP32)            |
 * |    Vin -> 5v ESP32                                  |
 * |    GND -> Ground ESP32                              |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Modulo RTC DS3231:                                  |
 * | - Libreria: https://github.com/adafruit/RTClib      |
 * | - Guia de Funcionamiento: https://n9.cl/o9x3j       |
 * | - Tutorial Simple: https://n9.cl/v09a0              |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#if defined(__AVR_ATmega2560__) // en caso de que se conecte un arduino MEGA, ejecutar las siguientes instrucciones: 
  #include <RTClib.h> // Libreria que incluye las instrucciones necesarias para trabajar con el modulo RTC DS3231. 

#elif defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  #include <RTClib.h> // Libreria que incluye las instrucciones necesarias para trabajar con el modulo RTC DS3231. 

#elif defined(ESP8266) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  #include <RTClib.h> // Libreria que incluye las instrucciones necesarias para trabajar con el modulo RTC DS3231. 
  
#endif


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
RTC_DS3231 rtc; // Crear Objeto RTC para utilizar los metodos y las clases de la libreria.
DateTime ahora; // Variable para almacenar la informacion del modulo RTC.


/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void initRTC(){ // Funcion que se encarga de inicializar y configurar el modulo RTC:
  Serial.print("Iniciando Modulo RTC...");
  
  for(int i=0; i<=10; i++){ // Bucle de 10 intentos para comprobar comunicacion con el modulo RTC DS3231:
    if(!rtc.begin()){
      Serial.print(".");
      delay(1000);
    } else{
      Serial.println(" ¡Modulo RTC Encontrado!");
      break;
    }

    if(i==10){
      Serial.println("\nError al inicializar el modulo RTC.");
      Serial.println("1. Revisa la Conexion.");
      Serial.println("2. Reinicia el arduino.");
      Serial.println("3. vuelve a intentarlo.");
      while(1){};
    }
  }

  // Directivas que permiten cargar en el modulo RTC la hora y la fecha actual.
  //rtc.adjust(DateTime(__DATE__, __TIME__)); // comentar despues de sincronizar la hora por primera vez, ya despues el mismo modulo se actualiza con su bateria de reserva.
}


void readRTC(){ // Funcion que permite sensar la fecha y la hora actual.
  ahora = rtc.now(); // variable tipo fecha para almacenar los datos del modulo en tiempo REAL.
}
