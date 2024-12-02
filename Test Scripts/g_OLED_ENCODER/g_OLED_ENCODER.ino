/* |-----------------------------------------------------|
 * |--------- Dispositivo de Monitoreo Ambiental --------|
 * |---------- Environmental Monitoring Device ----------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 22 julio 2024 ---------|
 * |--------- Ultima Modificacion: 29 Julio 2024 --------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | Este código muestra la implementacion de una HMI    |
 * | (interfaz Humano Maquina), utilizando una pantalla  |
 * | OLED de 0.96 pulg y un Encoder Rotativo KY-040.     |
 * | Se desarrolla un menu principal para acceder a las  |
 * | diferentes configuraciones del sistema.             |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Pantalla OLED 0.96'' 128x64:                        |
 * |    SCL -> Pin A05 (NANO) - PIN 21 (MEGA)            |
 * |    SDA -> Pin A04 (NANO) - PIN 20 (MEGA)            |
 * |    Vin -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |                                                     |
 * | Encoder Rotativo KY-040:                            |
 * |    DT  -> Pin D02 (NANO)                            |
 * |    CLK -> Pin D03 (NANO)                            |
 * |    SW  -> Pin D04 (NANO)                            |
 * |    Vin -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Pantalla OLED 0.96'' 128x64:                        |
 * | - Libraria: www.n9.cl/xlc9w - www.n9.cl/xv1dp       |
 * | - Guia de Funcionamiento: https://n9.cl/l03ufr      |
 * | - Tutorial: www.n9.cl/jzy5xj - www.n9.cl/f29yyf     |
 * |                                                     |
 * | Encoder Rotativo KY-040:                            |
 * | Libreria: No es necesario.                          |
 * | Guias: https://n9.cl/tbt4g - https://n9.cl/v2f8     |
 * | Tutorial: https://n9.cl/rmjnv - https://n9.cl/bn3d6 |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#if defined(__AVR_ATmega2560__) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  #include <Wire.h> // Libreria necesaria para la comunicacion I2C entre los disferentes dispositivos y el arduino.
  #include <Adafruit_GFX.h> // Libreria que incluye las instrucciones necesarias para trabajar con pantallas Genericas que requieren de graficos a traves de pixeles. 
  #include <Adafruit_SSD1306.h> // Libreria para las pantallas OLED basadas en el Driver SSD1306. Permite comunicacion I2C o SPI.
  
  #define ANCHO 128 // Constante que contiene el tamaño Horizontal en pixeles de la pantalla OLED.
  #define ALTO 64 // Constante que contiene el tamaño Vertical en pixeles de la pantalla OLED.
  #define OLED_RESET 4 // Pin de Reset de la pantalla OLED conectada al Arduino, aunque no se utiliza con pantallas genericas, es necesario declararlo para que se pueda crear el objeto.

  // Pines de conexion del Encoder con el Arduino.
  #define CHANNELPINA  2 // DT
  #define CHANNELPINB  3 // CLK
  #define SWPIN 4        // Boton

  #pragma message "Codigo para Arduino basado AVR 2560 (MEGA)!"

#elif defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  #pragma message "Codigo para Arduino ESP32!"

#else // si se conecta cualquier otro tipo de placa, entonces:
  #pragma message "No es ni ESP32 o ES8266 o AVR, que es?"
  
#endif


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET); // Crear Objeto OLED-SSD1306 segun algunos parametros como el tamaño de pantalla, tipo de comunicacion, y Pin de Reset.

// variables y constantes relacionadas con la generacion de los Menus:
String itemsMenuPrincipal[] = {"1. Ver Variables", "2. Frec. Muestro", "3. Info"}; // Items Menu Principal
byte menuSelector = 0; // Varibale utilizada para seleccionar el menu a mostrar en pantalla.
byte dataSensorSelector = 1; // Variable utilizada para seleccionar el mensaje a mostrar en la pantalla OLED.
byte itemIndex = 0; // contador para seleccionar el item desde el arreglo principal.
byte itemGap = 15; // Espaciado entre los items del menu a la hora de imprimir el menu principal.
byte xPos = 5; // posicion en X del cursor en la pantalla OLED para el menu principal.
byte yPos = 5; // posicion en Y del cursor en la pantalla OLED para el menu principal.
byte cursorOffset = 0; // cantidad de pixeles a desplazar para imprimir el recuadro al rededor del item actual en el menu principal.
byte displayPage = 0; // numero de pagina a mostrar en el menu info segun el encoder.

// Variables y constantes relacionadas con el encoder:
const char minSteps = 0; // Minima cantidad de pasos o conteos del encoder para darle un limite inferior al menu.
const char maxSteps = 10; // maxima cantidad de pasos o conteos del encoder para darle un limite superior al menu.
byte steps = 0; // Variable para contar los pulsos al girar el encoder.
bool currentDir; // Variable para almacenar la direccion actual del Encoder.

// variables para guardar el estado de cada canal del encoder:
unsigned char stateChannelA;
unsigned char stateChannelB;
unsigned char prevStateChannelB = 0;

// Variables necesarias para crear un antirrebote por codigo sin usar delay:
unsigned long lastButtonPress = 0; // Variable para almacenar el ultimo estado del boton del encoder.
int btnState; // Variable para almacenar el estado actual del boton del encoder.

// Variables y constantes Utilizadas para reemplazar el delay con la funcion millis():
unsigned long currentTime = 0;
const int refreshInterval = 500;

// variables para almacenar los valores relacionados con el sensor:
float temp, pres, alti; // Variables Fisicas.
byte freq = 0; // frecuencia de lectura de los sensores

/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
void setup(){
  // Configura los pines del encoder como entradas.
  pinMode(CHANNELPINA,INPUT);
  pinMode(CHANNELPINB,INPUT);
  pinMode(SWPIN, INPUT_PULLUP);
  
  Serial.begin(9600); // Inicializar Comunicacion Serial.
  Wire.begin(); // Inicializar comunicacion I2C.
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  // Bucle de 10 intentos para comprobar comunicacion con la pantalla OLED:
  Serial.print("Iniciando pantalla OLED...");
  for(int i=0; i<=10; i++){
    if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
      Serial.print(".");
      delay(1000);
    } else{
      oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializar comunicacion con la pantalla con algunos parametros como la alimentacion base, y la direccion I2C del dispositivo.
      Serial.println(" ¡Pantalla OLED Encontrada!\n");
      break;
    }

    if(i==10){
      Serial.println("\nError al inicializar la pantalla OLED.");
      Serial.println("1. Revisa la Conexion.");
      Serial.println("2. Reinicia el arduino.");
      Serial.println("3. vuelve a intentarlo.");
      while(1){};
    }
  } 

  oled.display(); // mostrar una pantalla de inicio por defecto de adafruit.
  randomSeed(analogRead(A0)); // Establecer semilla para secuencia de numeros aleatorios diferentes a apatir del ruido del pin analogico.
  
  delay(2000);
  
  oled.clearDisplay(); // Limpar pantalla despues de dos (2) segundos.
  prevStateChannelB = digitalRead(CHANNELPINB); // Toma el dato del encoder como base inicial.
}


/* |-----------------------------------------------------|
 * |----------------- Codigo Principal ------------------|
 * |-----------------------------------------------------| */
void loop() {
  getEnvironmentalData(); // llamar a la funcion que se encarga de sensar las variables fisicas.
  readEncoder(); // llamar a la funcion que lee el estado del encoder y su posicion.

  // condicional que se encarga de refrescar la pantalla OLED cada cierto intervalo de tiempo, esto sin el uso de delay: 
  if((millis() - currentTime) > refreshInterval){ 
    currentTime = millis();
    printMenu(); // llamar a la funcion que imprime los diferentes menus y submenus. 
  }
}


/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void getEnvironmentalData(){ // funcion que recolecta los datos desde los sensores: 
  temp = random(23,35) + (random(0,9)/100); // Generar valor aleatorio para temperatura. 
  pres = random(1,100) + (random(0,9)/100); // Generar valor aleatorio para presion.
  alti = random(1,100) + (random(0,9)/100); // Generar valor aleatorio para altitud.
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
      
      if(steps - 1 >= 0){
        steps--; // si gira a la izquierda, disminuir los pasos en 1.
      }  
    }

    // Conjunto de condicionales para establecer el desplazamiento del selector (cuadrado) en el menu principal, segun la cantidad de pulsos y direccion: 
    if((steps % 5) == 0 && currentDir == 1){
      if(steps == maxSteps){
        cursorOffset = 30;
        itemIndex = 2;
      } else{
        cursorOffset += 15;
        itemIndex += 1;
      }
    } else if((steps % 5) == 0 && currentDir == 0){
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

void printMenu(){ // Funcion que se encarga de imprimir un menu en pantalla segun el selector de menu que se activa con el boton del encoder: 
  oled.clearDisplay(); // Limpiar Pantalla OLED.
  oled.setTextColor(WHITE); // Establecer el color de los pixeles a encender en color BLANCO.

  if(menuSelector == 0){ // Imprimir menu Principal:
    mainMenu(); 
    drawBox(); // funcion que muestra el recuadro al rededor del item seleccionado. 
  } else if(menuSelector == 1){ // Mostrar Variables:
    variablesMenu();
  } else if(menuSelector == 2){ // mostrar menu para cambiar frecuencia:
    frecMenu();
  } else if(menuSelector == 3){ // mostrar menu de informacion:
    infoMenu();
  }

  oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
}

void mainMenu(){ // funcion que contiene la estructura del menu principal, para imprimirlo en pantalla: 
  int sizeMenuPrincipal = sizeof(itemsMenuPrincipal)/sizeof(itemsMenuPrincipal[0]);
  
  for(int i=0; i<= (sizeMenuPrincipal-1); i++){ // bucle finito para imprimir el menu principal segun la cantidad de items a mostrar: 
    oled.setTextSize(1); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.setCursor(xPos, yPos); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.print(itemsMenuPrincipal[i]); // imprimir el item correspondiente al contador i del bucle For.
    yPos += itemGap; // actualizar la posicion de Y para imprimir el siguiente item en un lugar apartado del anterior. 

    if(yPos >= (sizeMenuPrincipal*itemGap)){ // si la posicion del curso en Y es superior a la cantidad de items que se pueden imprimir en pantalla, reiniciar la posicion en Y.
      yPos = 5;
    }
  }
}

void variablesMenu(){ // funcion que contiene la estructura del menu de variables, para imprimirlo en pantalla: 
  if(dataSensorSelector == 1){ // mostrar temperatura:
    oled.setCursor(40, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.print("Temp"); // Escribir texto en pantalla.
    oled.setCursor(33, 38); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.print(temp);
    oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
  }

  if(dataSensorSelector == 2){ // mostrar presion:
    oled.setCursor(22, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.print("Presion"); // Escribir texto en pantalla.
    oled.setCursor(27, 38); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.print(pres);
    oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
  }

  if(dataSensorSelector == 3){ // Mostrar Altitud: 
    oled.setCursor(22, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.print("Altitud"); // Escribir texto en pantalla.
    oled.setCursor(21, 38); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.print(alti);
    oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
    dataSensorSelector = 0; // Reiniciar contador de variable para que muestre nuevamente la primera. 
  }

  dataSensorSelector++; // aumentar contador para que en el proximo ciclo muestre la siguiente variable.
} 

void frecMenu(){ // funcion que contiene la estructura del menu de frecuencia, para imprimirlo en pantalla: 
  oled.setCursor(5, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
  oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
  oled.print("Frecuencia"); // Escribir texto en pantalla.
  oled.setCursor((ANCHO/2)-7, 38); // Mover el cursor a la posicion especificada, en este caso, la mitad de la pantalla, para iniciar la escritura.
  
  freq = readEncoder(); // leer la posicion del encoder para tomarlo como el valor de la frecuencia y almacenarlo. 
  oled.print(freq); // imprimir el valor de la frecuencia en pantalla. 
  oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
}

void infoMenu(){ // funcion que contiene la estructura del menu de informacion, para imprimirlo en pantalla: 
  displayPage = readEncoder(); // leer la posicion del encoder para tomarlo como el valor de la pantalla de informacion a mostrar. 

  if(displayPage == 0){ // si el encoder esta en la posicion cero, mostrar la primera pantalla de informacion: 
    oled.setCursor(5, 10); // Mover el cursor a la posicion indicada, para iniciar la escritura en pantalla.
    oled.setTextSize(1); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.print("Codificado por: "); // Escribir texto en pantalla.
    oled.setCursor(5, 20);
    oled.print("Sergio P. Valencia");
    oled.setCursor(5, 40);
    oled.print("Fecha de Creacion: ");
    oled.setCursor(5, 50);
    oled.print("22 julio 2024");
  } else{
    oled.setCursor(5, 10); 
    oled.setTextSize(1); 
    oled.print("lugar: "); 
    oled.setCursor(5, 20);
    oled.print("Tecnoacademia-Mzles");
    oled.setCursor(5, 40);
    oled.print("Tiempo activo:");
    oled.setCursor(5, 50);
    oled.print("22 horas");

    if(steps>1){ // si los pasos del encoder son mayores a 1, mantener el valor en 1 para que no realice mas desplazamientos de pantalla. 
      steps = 1;
    }
  } 
  oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
}

void drawBox(){ // funcion que dibuja el recuadro al rededor de la opcion seleccionada actualmente en el menu principal: 
  int xBoundInit = xPos - 2;
  int yBoundInit = (yPos - 2) + cursorOffset;
  int xBoundEnd = ((itemsMenuPrincipal[itemIndex].length())*6)+4;
  int yBoundEnd = (yPos + 7);
  oled.drawRect(xBoundInit, yBoundInit, xBoundEnd, yBoundEnd, WHITE); // Crear un rectangulo desde la posicion desde la posicion especificada hasta el limite definido por las variables. .
 }
