/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Modulo MicroSD:                                     |
 * |    CS   -> PIN D53 (MEGA) - GPIO05 (ESP32)          |
 * |    MOSI -> PIN D51 (MEGA) - GPIO23 (ESP32)          |
 * |    SCK  -> PIN D52 (MEGA) - GPIO18 (ESP32)          |
 * |    MISO -> PIN D50 (MEGA) - GPIO19 (ESP32)          |
 * |    +5v -> 5v ESP32                                  |
 * |    GND -> Ground ESP32                              |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Modulo MicroSD:                                     |
 * | - Libreria: https://n9.cl/z0hjuf                    |
 * | - Guia de Funcionamiento: https://n9.cl/nbez7       |
 * | - Tutorial Simple: https://n9.cl/s88k9              |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#if defined(__AVR_ATmega2560__) // en caso de que se conecte un arduino MEGA, ejecutar las siguientes instrucciones: 
  #include <SD.h> // Libreria necesaria para la comunicacion SPI entre el modulo SD y el arduino.

  #define SSPIN 53 // Pin de Arduino donde va conectado el pin CS del modulo SD.

#elif defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  #include <SD.h> // Libreria necesaria para la comunicacion SPI entre el modulo SD y la ESP.

  #define SSPIN  5 // Pin de ESP32 donde va conectado el pin CS del modulo SD.

#elif defined(ESP8266) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  #include <SD.h> // Libreria necesaria para la comunicacion SPI entre el modulo SD y la ESP.

  #define SSPIN  D8 // Pin de ESP8266 donde va conectado el pin CS del modulo SD.
  
#endif


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
File datos; // Crear objeto Archivo que permite manipular los datos a enviar o leer a la SD.

// Variables y constantes relacionadas con el almacenamiento en la memoria microSD:
const char filename[] = "datalog.csv"; // variable que contiene el nombre del archivo que se guardara en la microSD.
char buffer[40]; // arreglo o espacio de memoria donde se alamcena los String a imprimir con sprintf.


/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void initSD(){ // Funcion que se encarga de inicializar y configurar el modulo microSD:
  Serial.print("Iniciando SD...");
  
  for(int i=0; i<=10; i++){ // Bucle de 10 intentos para comprobar comunicacion con el modulo microSD:
    if(!SD.begin(SSPIN)){
      Serial.print(".");
      delay(1000);
    } else{
      Serial.println(" ¡Modulo SD Encontrado!");
      break;
    }

    if(i==10){
      Serial.println(" Error al inicializar el modulo SD.");
      Serial.println("1. Revisa la Conexion.");
      Serial.println("2. Reinicia el arduino.");
      Serial.println("3. vuelve a intentarlo.");
      while(1){};
    }
  }

  // Conjunto de instrucciones que se encarga de revisar si ya existe un archivo dentro de la microSD para almacenar los datos:
  if(!SD.exists(filename)){
    datos = SD.open(filename, FILE_WRITE);

    if(datos){
      Serial.println("archivo Nuevo Creado, Escribiendo encabezados (Fila 1)...");
      datos.println("Fecha, Hora, Temperatura(°C),Presion(hPa),Altitud(m)");
      datos.close();
    } else{
      Serial.println("Error al crear el nuevo archivo");
    }
  }
}


void logDataSD(){ // Funcion que se encarga de almacenar los datos en la memoria MicroSD:
  datos = SD.open(filename, FILE_WRITE); // Instruccion para abrir el archivo donde se almacenara la informacion recolectada.
  
  if(datos){
    sprintf(buffer, "%2d/%2d/%4d,%2d:%2d:%2d", ahora.day(), ahora.month(), ahora.year(), ahora.hour(), ahora.minute(), ahora.second());
    datos.print(buffer);
    datos.print(",");
    datos.print(temp);
    datos.print(",");
    datos.print(pres);
    datos.print(",");
    datos.println(alti);
  
    datos.close(); // Cerrar el archivo.
  } else{
    Serial.println("Error al abrir el archivo");
  }
}
