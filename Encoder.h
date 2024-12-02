/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Encoder Rotativo KY-040:                            |
 * |    DT  -> Pin D02 (MEGA) - GPIO25 (ESP32)           |
 * |    CLK -> Pin D03 (MEGA) - GPIO26 (ESP32)           |
 * |    SW  -> Pin D04 (MEGA) - GPIO33 (ESP32)           |
 * |    Vin -> 5v ESP                                    |
 * |    GND -> Ground ESP                                |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Encoder Rotativo KY-040:                            |
 * | Libreria: No es necesario.                          |
 * | Guias: https://n9.cl/tbt4g - https://n9.cl/v2f8     |
 * | Tutorial: https://n9.cl/rmjnv - https://n9.cl/bn3d6 |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#if defined(__AVR_ATmega2560__) // en caso de que se conecte un arduino MEGA, ejecutar las siguientes instrucciones: 
  // Pines de conexion del Encoder con el Arduino.
  #define CHANNELPINA  2 // DT
  #define CHANNELPINB  3 // CLK
  #define SWPIN 4        // Boton

#elif defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  // Pines de conexion del Encoder con la ESP.
  #define CHANNELPINA  25 // DT
  #define CHANNELPINB  26 // CLK
  #define SWPIN        33 // Boton
  
#elif defined(ESP8266) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  // Pines de conexion del Encoder con la ESP.
  #define CHANNELPINA  16 // DT
  #define CHANNELPINB   4 // CLK
  #define SWPIN        17 // Boton
  
#endif


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
// Variables y constantes relacionadas con el encoder:
byte minSteps = 0; // Minima cantidad de pasos o conteos del encoder para darle un limite inferior al menu.
byte maxSteps = 4; // maxima cantidad de pasos o conteos del encoder para darle un limite superior al menu.
byte steps = 0; // Variable para contar los pulsos al girar el encoder.
bool currentDir; // Variable para almacenar la direccion actual del Encoder.
byte cursorOffset = 0; // cantidad de pixeles a desplazar para imprimir el recuadro al rededor del item actual en el menu principal.
byte itemIndex = 0; // contador para seleccionar el item desde el arreglo principal.
byte menuSelector = 0; // Varibale utilizada para seleccionar el menu a mostrar en pantalla.

// variables para guardar el estado de cada canal del encoder:
unsigned char stateChannelA;
unsigned char stateChannelB;
unsigned char prevStateChannelB = 0;

// Variables necesarias para crear un antirrebote por codigo sin usar delay:
unsigned long lastButtonPress = 0; // Variable para almacenar el ultimo estado del boton del encoder.
int btnState; // Variable para almacenar el estado actual del boton del encoder.


/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void initEncoder(){ // Funcion que se encarga de inicializar y configurar el Encoder:
  // Configura los pines del encoder como entradas.
  pinMode(CHANNELPINA,INPUT);
  pinMode(CHANNELPINB,INPUT);
  pinMode(SWPIN, INPUT_PULLUP);

  prevStateChannelB = digitalRead(CHANNELPINB); // Toma el dato del encoder como base inicial.
}


void readBtnEncoder(){ // funcion que lee el estado del boton del encoder:
  btnState = digitalRead(SWPIN); // // lee el estado del boton.
  
  if (btnState == LOW) { // si se presiona el pulsador del encoder, entonces:
    if ((millis() - lastButtonPress) > 50){ // si han pasado 50ms desde que se presiono y solto el pulsador, entonces:
      steps = 0; // reiniciar el contador de pasos del encoder para que no inicie en un valor anterior de otro menu. 

      // conjunto de condicionales para seleccionar el SubMenu al que se accede desde el menu principal al presionar el pulsador del encoder: 
      if(menuSelector == 0 && itemIndex == 0){
        menuSelector = 1; // SubMenu Variables
      } else if(menuSelector == 0 && itemIndex == 1){
        menuSelector = 2; // SubMenu Frecuencia
      } else if(menuSelector == 0 && itemIndex == 2){
        menuSelector = 3; // Submenu Info
      } else if(menuSelector == 1 || menuSelector == 2 || menuSelector == 3){
        menuSelector = 0; // Volver al menu Principal desde el primer item seleccionado.
        steps = 0;
        cursorOffset = 0;
        itemIndex = 0;
      }
    }
    
    lastButtonPress = millis(); // actualiza el tiempo para un proximo pulso.
  }
}


byte readEncoder(){ // Funcion que se encarga de leer el valor desde el encoder segun la cantidad de pulsos:
  stateChannelB = digitalRead(CHANNELPINB); // CLK

  if(stateChannelB != prevStateChannelB){
    stateChannelA = digitalRead(CHANNELPINA); // DT
    
    if(stateChannelA != stateChannelB){
      currentDir = 1;

      if(steps + 1 <= maxSteps){
        steps++; // si gira a la derecha, aumentar los pasos en 1. 
      }
     } else{
      currentDir = 0;
      
      if(steps - 1 >= minSteps){
        steps--; // si gira a la izquierda, disminuir los pasos en 1.
      }  
    }

    // Conjunto de condicionales para establecer el desplazamiento del selector (cuadrado) en el menu principal, segun la cantidad de pulsos y direccion: 
    if((steps % 2) == 0 && currentDir == 1){
      if(steps == maxSteps){
        cursorOffset = 30;
        itemIndex = 2;
      } else{
        cursorOffset += 15;
        itemIndex += 1;
      }
    } else if((steps % 2) == 0 && currentDir == 0){
      if(steps == minSteps){
        cursorOffset = 0;
        itemIndex = 0;
      } else{
        cursorOffset -= 15;
        itemIndex -= 1;
      }
    }
   
    prevStateChannelB = stateChannelB;  // Guardar valores para siguiente.
  }

  readBtnEncoder(); // llamar a la funcion que se encarga de revisar el estado del boton del encoder. 
  return steps; // devolver la cantidad de pasos para ser utilizados en otro lugar del programa. 
}
