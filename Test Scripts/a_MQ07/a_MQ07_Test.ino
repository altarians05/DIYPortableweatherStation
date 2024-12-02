/* |-----------------------------------------------------|
 * |------- Calibracion y prueba de funcionamiento ------|
 * |--------------------- Sensor MQ07 -------------------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 30 Junio 2024 ---------|
 * |--------- Ultima Modificacion: 30 Junio 2024 --------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | El presente codigo muestra la implementacion        | 
 * | (calibracion y lectura)del sensor MQ07 para tomar   | 
 * | muestras precisas de la cantidad particulas por     |
 * | millon (PPM) de monoxido de carbono presente en el  | 
 * | ambiente.                                           |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Sensor MQ07:                                        |
 * |    Analog Out -> Pin A02                            |      
 * |    Vin -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Libreria: https://github.com/fjebaker/MQ7           |
 * | Guia de calibracion: https://n9.cl/d2vvh            |
 * | Tutorial Simple: https://n9.cl/cedsa_sensoresgas    |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#include "MQ7.h" // libreria que contiene las instrucciones especificas para calibrar y tomar lecturas del sensor MQ07.


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
#define MQ7_PIN 2 // Numero del Pin analogico donde se conectara el sensor MQ07.
#define VOLTAGE 5 // Valor de alimentacion del sensor para Calibracion.

MQ7 mq7(MQ7_PIN, VOLTAGE); // Crear objeto MQ7 para Inicializar el sensor respectivo.

float R0Value; // variable para almacenar el valor de R0 Calculado despues de la calibracion.

/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
void setup() {
  Serial.begin(9600);
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  Serial.println("¡Canal Serial Abierto!");
  Serial.println("");

  // Iniciar calibracion de sensor MQ07. Tarde alredor de 15 segundos.
  // RECOMENDACION: antes de calibrar, se debe dejar el sensor en reposo durante algunas horas en el lugar en el que se va a calibrar.
  Serial.println("Calibrando Sensor MQ07");
  mq7.calibrate(); // Calcular el valor R0 asumiendo aire fresco (10 ppm de Co)
  Serial.println("¡Calibracion Terminada!");
  
  R0Value = mq7.getR0(); // Despues de la calibracion, Obtener el Valor de R0.
  Serial.print("R0= ");
  Serial.println(R0Value);
  Serial.println("Reemplaze el valor de R0 obtenido aqui, en el archivo MQ7.h descomentando la linea #define _R0");
  Serial.println("Posteriormente, ya no sera necesario calibrar nuevamente el sensor.");
}


/* |-----------------------------------------------------|
 * |------------------ Codigo Principal -----------------|
 * |-----------------------------------------------------| */
void loop() {
  Serial.print("PPM = "); 
  Serial.println(mq7.readPpm());

  delay(1000);
}
