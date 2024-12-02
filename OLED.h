/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Pantalla OLED 0.96'' 128x64:                        |
 * |    SCL -> PIN 21 (MEGA) - GPIO22 (ESP32)            |
 * |    SDA -> PIN 20 (MEGA) - GPIO21 (ESP32)            |
 * |    Vin -> 5v ESP32                                  |
 * |    GND -> Ground ESP32                              |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Pantalla OLED 0.96'' 128x64:                        |
 * | - Libraria: www.n9.cl/xlc9w - www.n9.cl/xv1dp       |
 * | - Guia de Funcionamiento: https://n9.cl/l03ufr      |
 * | - Tutorial: www.n9.cl/jzy5xj - www.n9.cl/f29yyf     |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#if defined(__AVR_ATmega2560__) // en caso de que se conecte un arduino MEGA, ejecutar las siguientes instrucciones: 
  #include <Adafruit_GFX.h> // Libreria que incluye las instrucciones necesarias para trabajar con pantallas Genericas que requieren de graficos a traves de pixeles. 
  #include <Adafruit_SSD1306.h> // Libreria para las pantallas OLED basadas en el Driver SSD1306. Permite comunicacion I2C o SPI.

  #define ANCHO 128 // Constante que contiene el tamaño Horizontal en pixeles de la pantalla OLED.
  #define ALTO 64 // Constante que contiene el tamaño Vertical en pixeles de la pantalla OLED.
  #define OLED_RESET 4 // Pin de Reset de la pantalla OLED conectada al Arduino, aunque no se utiliza con pantallas genericas, es necesario declararlo para que se pueda crear el objeto.

#elif defined(ESP32) // en caso de que se conecte una esp32, ejecutar las siguientes instrucciones: 
  #include <Adafruit_GFX.h> // Libreria que incluye las instrucciones necesarias para trabajar con pantallas Genericas que requieren de graficos a traves de pixeles. 
  #include <Adafruit_SSD1306.h> // Libreria para las pantallas OLED basadas en el Driver SSD1306. Permite comunicacion I2C o SPI.

  #define ANCHO 128 // Constante que contiene el tamaño Horizontal en pixeles de la pantalla OLED.
  #define ALTO 64 // Constante que contiene el tamaño Vertical en pixeles de la pantalla OLED.
  #define OLED_RESET -1 // Pin de Reset de la pantalla OLED conectada a la ESP, aunque no se utiliza con pantallas genericas, es necesario declararlo para que se pueda crear el objeto.

#elif defined(ESP8266) // en caso de que se conecte una esp8266, ejecutar las siguientes instrucciones: 
  #include <Adafruit_GFX.h> // Libreria que incluye las instrucciones necesarias para trabajar con pantallas Genericas que requieren de graficos a traves de pixeles. 
  #include <Adafruit_SSD1306.h> // Libreria para las pantallas OLED basadas en el Driver SSD1306. Permite comunicacion I2C o SPI.

  #define ANCHO 128 // Constante que contiene el tamaño Horizontal en pixeles de la pantalla OLED.
  #define ALTO 64 // Constante que contiene el tamaño Vertical en pixeles de la pantalla OLED.
  #define OLED_RESET -1 // Pin de Reset de la pantalla OLED conectada a la ESP, aunque no se utiliza con pantallas genericas, es necesario declararlo para que se pueda crear el objeto.
  
#endif


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
 Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET); // Crear Objeto OLED-SSD1306 segun algunos parametros como el tamaño de pantalla, tipo de comunicacion, y Pin de Reset.

// variables y constantes relacionadas con la generacion de los Menus:
String itemsMenuPrincipal[] = {"1. Ver Variables", "2. Frec. Muestreo", "3. Info"}; // Items Menu Principal
byte itemGap = 15; // Espaciado entre los items del menu a la hora de imprimir el menu principal.
byte xPos = 5; // posicion en X del cursor en la pantalla OLED para el menu principal.
byte yPos = 5; // posicion en Y del cursor en la pantalla OLED para el menu principal.

// Variables y constantes Utilizadas para reemplazar el delay con la funcion millis():
unsigned long refreshTime = 0;
const int refreshInterval = 700;


/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void initOLED(){ // Funcion que se encarga de inicializar y configurar la pantalla OLED:
  Serial.print("Iniciando pantalla OLED...");
  
  for(int i=0; i<=10; i++){ // Bucle de 10 intentos para comprobar comunicacion con la pantalla OLED:
    if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
      Serial.print(".");
      delay(1000);
    } else{
      oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializar comunicacion con la pantalla con algunos parametros como la alimentacion base, y la direccion I2C del dispositivo.
      Serial.println(" ¡Pantalla OLED Encontrada!");
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
}


void mainMenu(){ // funcion que contiene la estructura del menu principal, para imprimirlo en pantalla: 
  minSteps = 0; // cambiar la maxima cantidad de pasos del encoder, ya que esta vez sera para definir el limite minimo de movimiento en el menu principal.
  maxSteps = 4; // cambiar la maxima cantidad de pasos del encoder, ya que esta vez sera para definir el limite superior de movimiento en el menu principal.
  byte sizeMenuPrincipal = sizeof(itemsMenuPrincipal)/sizeof(itemsMenuPrincipal[0]);
  
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


void drawBox(){ // funcion que dibuja el recuadro al rededor de la opcion seleccionada actualmente en el menu principal: 
  int xBoundInit = xPos - 2;
  int yBoundInit = (yPos - 2) + cursorOffset;
  int xBoundEnd = ((itemsMenuPrincipal[itemIndex].length())*6)+4;
  int yBoundEnd = (yPos + 7);
  oled.drawRect(xBoundInit, yBoundInit, xBoundEnd, yBoundEnd, WHITE); // Crear un rectangulo desde la posicion desde la posicion especificada hasta el limite definido por las variables. .
}


void variablesMenu(){ // funcion que contiene la estructura del menu de variables, para imprimirlo en pantalla: 
  minSteps = 0; // cambiar la minima cantidad de pasos del encoder, ya que solo se mostrara maximo tres (3) variables.
  maxSteps = 2; // cambiar la minima cantidad de pasos del encoder, ya que solo se mostrara maximo tres (3) variables.
  byte dataSensorSelector = readEncoder(); // leer la posicion del encoder para tomarlo como el valor que selecciona la variable a mostrar en la pantalla OLED.
  
  if(dataSensorSelector == 0){ // mostrar temperatura:
    oled.setCursor(40, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.print("Temp"); // Escribir texto en pantalla.
    oled.setCursor(33, 38); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.print(temp);
    oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
  }

  if(dataSensorSelector == 1){ // mostrar presion:
    oled.setCursor(22, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.print("Presion"); // Escribir texto en pantalla.
    oled.setCursor(27, 38); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.print(pres);
    oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
  }

  if(dataSensorSelector == 2){ // Mostrar Altitud: 
    oled.setCursor(22, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
    oled.print("Altitud"); // Escribir texto en pantalla.
    oled.setCursor(21, 38); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
    oled.print(alti);
    oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
  }
} 


void frecMenu(){ // funcion que contiene la estructura del menu de frecuencia, para imprimirlo en pantalla: 
  minSteps = 0; // cambiar la minima cantidad de pasos del encoder, ya que esta vez sera para definir la frecuencia de muestreo (cantidad de muestras por minuto).
  maxSteps = 29; // cambiar la maxima cantidad de pasos del encoder, ya que esta vez sera para definir la frecuencia de muestreo (cantidad de muestras por minuto).
  freq = readEncoder()+1; // leer la posicion del encoder para tomarlo como el valor de la frecuencia y almacenarlo. 
  
  oled.setCursor(5, 10); // Mover el cursor a la posicion especificada, para iniciar la escritura en pantalla.
  oled.setTextSize(2); // Establecer el tamaño de la letra, donde 1 = 6x8 px; 2 = 12x16 px.
  oled.print("Frecuencia"); // Escribir texto en pantalla.
  oled.setCursor((ANCHO/2)-7, 38); // Mover el cursor a la posicion especificada, en este caso, la mitad de la pantalla, para iniciar la escritura.
  oled.print(freq); // imprimir el valor de la frecuencia en pantalla. 
  oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
}


void infoMenu(){ // funcion que contiene la estructura del menu de informacion, para imprimirlo en pantalla: 
  minSteps = 0; // cambiar la minima cantidad de pasos del encoder, ya que solo se mostrara maximo tres (3) variables.
  maxSteps = 1; // cambiar la minima cantidad de pasos del encoder, ya que solo se mostrara maximo tres (3) variables.
  byte displayPage = readEncoder(); // leer la posicion del encoder para tomarlo como el valor de la pantalla de informacion a mostrar. 

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
  } 
  oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
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
