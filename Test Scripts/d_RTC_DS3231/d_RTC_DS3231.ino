/* |-----------------------------------------------------|
 * |------------- prueba de funcionamiento --------------|
 * |----------------- Modulo RTC DS3231 -----------------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 07 Julio 2024 ---------|
 * |--------- Ultima Modificacion: 13 Julio 2024 --------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | El presente codigo muestra la implementacion        | 
 * | del modulo de reloj DS3231 que permite obtener la   | 
 * | fecha y la hora de forma muy precisa, con la        |
 * | intencion de registrar en tiempo real en que        |
 * | momento se toman los datos desde los sensores.      |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Modulo RTC DS3231:                                 |
 * |    SCL -> Pin A05                                   |      
 * |    SDA -> Pin A04                                   | 
 * |    Vin -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/


/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Libreria: https://github.com/adafruit/RTClib        |
 * | Guia de Funcionamiento: https://n9.cl/o9x3j         |
 * | Tutorial Simple: https://n9.cl/v09a0                |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#include <Wire.h> // Libreria necesaria para la comunicacion I2C entre el sensor y el arduino.
#include <RTClib.h> // Libreria que incluye las instrucciones necesarias para trabajar con el modulo RTC DS3231.


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
RTC_DS3231 rtc; // Crear Objeto RTC para utilizar los metodos y las clases de la libreria.

/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
void setup() {
  Serial.begin(9600);
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  Serial.println("¡Canal Serial Abierto!");
  Serial.println("");

  Serial.print("Iniciando Modulo RTC...");

  for(int i=0; i<=10; i++){
    if(!rtc.begin()){
      Serial.print(".");
      delay(1000);
    } else{
      Serial.println(" ¡Modulo RTC Encontrado!\n");
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
  rtc.adjust(DateTime(__DATE__, __TIME__)); // comentar despues de sincronizar la hora por primera vez, ya despues el mismo modulo se actualiza con su bateria de reserva.
  delay(2000);
}


/* |-----------------------------------------------------|
 * |------------------ Codigo Principal -----------------|
 * |-----------------------------------------------------| */
void loop(){
  DateTime ahora = rtc.now(); // Declarar y definir una variable tipo fecha para almacenar los datos del modulo en tiempo REAL.

  printDate(ahora); // llamar a la funcion que imprime los datos de la fecha en tiempor Real.
  
  delay(1000);
}


/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void printDate(DateTime fecha){ // Imprimir y organizar los datos de la fecha y hora respectivamente. 
  Serial.print(fecha.day(), DEC);
  Serial.print("/");
  Serial.print(fecha.month(), DEC);
  Serial.print("/");
  Serial.print(fecha.year(), DEC);
  Serial.print(" - ");
  Serial.print(fecha.hour(), DEC);
  Serial.print(":");
  Serial.print(fecha.minute(), DEC);
  Serial.print(":");
  Serial.println(fecha.second(), DEC);
}
