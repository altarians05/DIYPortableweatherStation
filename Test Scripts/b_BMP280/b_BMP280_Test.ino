/* |-----------------------------------------------------|
 * |------- Calibracion y prueba de funcionamiento ------|
 * |------------------- Sensor BMP280 -------------------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 01 Julio 2024 ---------|
 * |--------- Ultima Modificacion: 13 Julio 2024 --------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | El presente codigo muestra la implementacion        | 
 * | (calibracion y lectura) del sensor BMP280 para      | 
 * | tomar muestras precisas de Temperatura, y Presion   |
 * | Atmosferica (°C y hPa) presente en el ambiente.     |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Sensor BMP280:                                      |
 * |    SCL -> Pin A05                                   |      
 * |    SDA -> Pin A04                                   | 
 * |    Vin -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Libreria: https://n9.cl/2wgdx                       |
 * | Guia de Funcionamiento: https://n9.cl/31472         |
 * | Tutorial Simple: https://n9.cl/s88k9                |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#include <Wire.h> // Libreria necesaria para la comunicacion I2C entre el sensor y el arduino.
#include <Adafruit_Sensor.h> // Libreria requerida para la programacion de todos los sensores de marca Adafruit.
#include <Adafruit_BMP280.h> // Libreria que contiene las instrucciones especificas para el sensor BMP280.

#define SEALEVELPRESSURE_HPA 1013.25

/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
Adafruit_BMP280 BMP; // Crear objeto BMP para usar los metodos y clases del sensor respectivo.

float temp, pres, alti, humi; // variables para almacenar los valores medidos por el sensor. .

/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
void setup() {
  Serial.begin(9600);
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  Serial.println("¡Canal Serial Abierto!");
  Serial.println("");

  Serial.print("Iniciando Sensor BMP280...");

  for(int i=0; i<=10; i++){
    if(!BMP.begin()){
      Serial.print(".");
      delay(1000);
    } else{
      Serial.print(" ¡Sensor BMP280 Encontrado!\n");
      break;
    }

    if(i==10){
      Serial.println(" Error al inicializar el Sensor BME280.");
      Serial.println("1. Revisa la Conexion.");
      Serial.println("2. Reinicia el arduino.");
      Serial.println("3. vuelve a intentarlo.");
      while(1){};
    }
  }  

  delay(2000);
}


/* |-----------------------------------------------------|
 * |------------------ Codigo Principal -----------------|
 * |-----------------------------------------------------| */
void loop(){
  temp = BMP.readTemperature(); // Funcion para leer la temperatura. 
  pres = BMP.readPressure()/100; // Funcion para leer la Presion. Se divide en 100 porque el sensor lee en Pascales, y se necesitan hPa.
  alti = BMP.readAltitude(SEALEVELPRESSURE_HPA); // se pasa como parametro la presion atmosferica a nivel del mar en colombia (cartagena de indias) que es 760 mmHg = 1013.25 hPa.   
  
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C       Presion: ");
  Serial.print(pres);
  Serial.print(" hPa      Altitud: ");
  Serial.print(alti);
  Serial.println("m"); // Metros

  delay(1000);
}
