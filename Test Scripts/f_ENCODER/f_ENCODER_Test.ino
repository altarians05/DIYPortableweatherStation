/* |-----------------------------------------------------|
 * |------------- prueba de funcionamiento --------------|
 * |----------------- Encoder Rotativo ------------------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 19 Julio 2024 ---------|
 * |--------- Ultima Modificacion: 19 Julio 2024 --------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | El presente codigo muestra la implementacion        | 
 * | de un encoder Rotativo de tipo incremental el cual  |
 * | se caracteriza por su sencillo funcionamiento. la   |
 * | intencion principal de este dispositivo es poderlo  | 
 * | Utilizar como parte de una interfaz Humano Maquina  |
 * | (HMI) en un menu a traves de la pantalla OLED.      |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Pantalla OLED 0.96'' 128x64:                        |
 * |    DT  -> Pin D02                                   |     
 * |    CLK -> Pin D03                                   |
 * |    SW  -> Pin D04                                   | 
 * |    Vin -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Libreria: No es necesario.                          |
 * | Guias: https://n9.cl/tbt4g - https://n9.cl/v2f8     |
 * | Tutorial: https://n9.cl/rmjnv - https://n9.cl/bn3d6 |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/


/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
// Pines de conexion del Encoder con el Arduino.
#define CHANNELPINA  2 // DT
#define CHANNELPINB  3 // CLK
#define SWPIN 4        // Boton


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
// variables para guardar el estado de cada canal del encoder.
unsigned char stateChannelA;
unsigned char stateChannelB;
unsigned char prevStateChannelB = 0;

const int maxSteps = 255; // maxima cantidad de pasos o conteos del encoder para darle un limite al menu.
int steps = 0; // Variable para contar los pulsos al girar el encoder.
String currentDir = ""; // Variable para almacenar la direccion actual del Encoder

// Variables necesarias para crear un antirrebote por codigo sin usar delay:
unsigned long lastButtonPress = 0; // Variable para almacenar el ultimo estado del boton del encoder.
int btnState; // Variable para almacenar el estado actual del boton del encoder.


/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
void setup() {
  // ajusta los pines del encoder como entradas
  pinMode(CHANNELPINA,INPUT);
  pinMode(CHANNELPINB,INPUT);
  pinMode(SWPIN, INPUT_PULLUP);
  
  Serial.begin(9600); // Inicializar Comunicacion Serial.
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  Serial.println("¡Canal Serial Abierto!");
  Serial.println("");

  prevStateChannelB = digitalRead(CHANNELPINB);
  
  delay(2000);
}


/* |-----------------------------------------------------|
 * |------------------ Codigo Principal -----------------|
 * |-----------------------------------------------------| */
void loop() {
  stateChannelB = digitalRead(CHANNELPINB); // CLK

  if(stateChannelB != prevStateChannelB){
    stateChannelA = digitalRead(CHANNELPINA); // DT
    
    if(stateChannelA != stateChannelB){
      currentDir = "CW";

      if(steps + 1 <= maxSteps){
        steps++;
        Serial.println(steps);
        Serial.println(currentDir);
        Serial.println();
      }
     } else{
      currentDir = "CCW";
      if(steps - 1 >= 0){
        steps--;
        Serial.println(steps);
        Serial.println(currentDir);
        Serial.println();
      }  
    }
    prevStateChannelB = stateChannelB;  // Guardar valores para siguiente
  }
  
  btnState = digitalRead(SWPIN); // // lee el estado del boton.
  if (btnState == LOW) { // si se presiona el pulsador del encoder, entonces:
    if ((millis() - lastButtonPress) > 50){ // si han pasado 50ms desde que se presiono y solto el pulsador, entonces:
      Serial.println("Button pressed!"); // Boton Presionado. 
    }
    lastButtonPress = millis(); // actualiza el tiempo para un proximo pulso.
  }
}
