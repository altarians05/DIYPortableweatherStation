/* |-----------------------------------------------------|
 * |------------- prueba de funcionamiento --------------|
 * |--------------- Pantalla OLED 0.96'' ----------------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 08 Julio 2024 ---------|
 * |--------- Ultima Modificacion: 13 Julio 2024 --------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | El presente codigo muestra la implementacion        | 
 * | de una pantalla OLED biColor de 0.96'' (pulgadas)   |
 * | de tamaño la cual se caracteriza por ser de bajo    |
 * | consumo, y que permite mostrar informacion, como    | 
 * | datos, graficos o simples animaciones.              |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Pantalla OLED 0.96'' 128x64:                        |
 * |    SCL -> Pin A05                                   |      
 * |    SDA -> Pin A04                                   | 
 * |    Vin -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Libreria: https://n9.cl/xlc9w - https://n9.cl/xv1dp |
 * | Guia de Funcionamiento: https://n9.cl/l03ufr        |
 * | Tutorial: www.n9.cl/jzy5xj - www.n9.cl/f29yyf       |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/


/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#include <Wire.h> // Libreria que contiene un set de graficos primitivos comunes (puntos, lineas, circulos) para un manejo mas sencillo de la pantalla OLED.
#include <Adafruit_GFX.h> // Libreria que incluye las instrucciones necesarias para trabajar con pantallas Genericas que requieren de graficos a traves de pixeles. 
#include <Adafruit_SSD1306.h> // Libreria para las pantallas OLED basadas en el Driver SSD1306. Permite comunicacion I2C o SPI.

#define ANCHO 128 // Constante que contiene el tamaño Horizontal en pixeles de la pantalla OLED.
#define ALTO 64 // Constante que contiene el tamaño Vertical en pixeles de la pantalla OLED.
#define OLED_RESET 4 // Pin de Reset de la pantalla OLED conectada al Arduino, aunque no se utiliza con pantallas genericas, es necesario declararlo para que se pueda crear el objeto.


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET); // Crear Objeto OLED-SSD1306 segun algunos parametros como el tamaño de pantalla, tipo de comunicacion, y Pin de Reset.

char opcion;

/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
void setup() {
  Serial.begin(9600); // Inicializar Comunicacion Serial.
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  Serial.println("¡Canal Serial Abierto!");
  Serial.println("");

  Serial.print("Iniciando pantalla OLED...");
  Wire.begin(); // Inicializar comunicacion I2C.

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
  delay(2000);
  oled.clearDisplay(); // Limpar pantalla despues de dos (2) segundos.
}


/* |-----------------------------------------------------|
 * |------------------ Codigo Principal -----------------|
 * |-----------------------------------------------------| */
void loop(){
  if(Serial.available()){
    opcion = Serial.read();
    switch(opcion){
      case '1': Text(); break;
      case '2': point(); break;
      case '3': testdrawline(); break;
      case '4': testdrawcircle(); break;
      default: break;
    }
  }
}


/* |-----------------------------------------------------|
 * |----------------- Funciones Propias -----------------|
 * |-----------------------------------------------------| */
void Text(){
  oled.clearDisplay(); // Limpiar Pantalla OLED.
  oled.setTextColor(WHITE); // Establecer el color de los pixeles a encender en color BLANCO.
  oled.setCursor(0, 0); // Mover el cursor a la posicion X0, Y0, para iniciar la escritura en pantalla.
  oled.setTextSize(1); // Establecer el tamaño de la letra, donde 1 = 6x8 px.
  oled.print("hola, Han Pasado:"); // Escribir texto de prueba segun parametros previos de configuracion.
  oled.setCursor(10, 10); // mover el cursor a una nueva posicion (X10, Y30), con la intencion que el siguiente texto a imprimir quede centrado.
  oled.setTextSize(2); // Cambiar el tamaño de la letra, donde 2 = 12x16 px.
  oled.print(millis()/1000); // Imprimir la cantidad de seg. que pasan desde que el arduino esta en funcionamiento. 
  oled.print("seg."); // Imprimir la magnitud de medicion.
  oled.drawRect(20, 30, 88, 54, WHITE); // Crear un rectangulo desde la posicion X20 Y40 y que a partir de alli mida 88x64 px.
  oled.setCursor(28,44); 
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.print("ALARMA"); // Imprimir el mensaje "alarma" dentro del recuadro. 
  oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
  opcion = ""; // Limpiar Variable para proximo pedido. 
}

void point(){
  oled.clearDisplay(); // Limpiar Pantalla OLED.
  oled.drawPixel(10, 10, WHITE); // Dibujar punto de color Blanco.
  oled.display(); // mostrar en pantalla lo que se acabo de configurar, ya que todos los comandos son temporales, no definitivos. 
  opcion = ""; // Limpiar Variable para proximo pedido. 
}

void testdrawline(){  
  for (int16_t i=0; i<oled.width(); i+=4) {
    oled.drawLine(0, 0, i, oled.height()-1, WHITE);
    oled.display();
    delay(1);
  }
  for (int16_t i=0; i<oled.height(); i+=4) {
    oled.drawLine(0, 0, oled.width()-1, i, WHITE);
    oled.display();
    delay(1);
  }
  delay(250);
  
  oled.clearDisplay();
  for (int16_t i=0; i<oled.width(); i+=4) {
    oled.drawLine(0, oled.height()-1, i, 0, WHITE);
    oled.display();
    delay(1);
  }
  for (int16_t i=oled.height()-1; i>=0; i-=4) {
    oled.drawLine(0, oled.height()-1, oled.width()-1, i, WHITE);
    oled.display();
    delay(1);
  }
  delay(250);
  
  oled.clearDisplay();
  for (int16_t i=oled.width()-1; i>=0; i-=4) {
    oled.drawLine(oled.width()-1, oled.height()-1, i, 0, WHITE);
    oled.display();
    delay(1);
  }
  for (int16_t i=oled.height()-1; i>=0; i-=4) {
    oled.drawLine(oled.width()-1, oled.height()-1, 0, i, WHITE);
    oled.display();
    delay(1);
  }
  delay(250);

  oled.clearDisplay();
  for (int16_t i=0; i<oled.height(); i+=4) {
    oled.drawLine(oled.width()-1, 0, 0, i, WHITE);
    oled.display();
    delay(1);
  }
  for (int16_t i=0; i<oled.width(); i+=4) {
    oled.drawLine(oled.width()-1, 0, i, oled.height()-1, WHITE); 
    oled.display();
    delay(1);
  }
  delay(250);
  opcion = ""; // Limpiar Variable para proximo pedido. 
}

void testdrawcircle(void) {
  for (int16_t i=0; i<oled.height(); i+=2) {
    oled.drawCircle(oled.width()/2, oled.height()/2, i, WHITE);
    oled.display();
    delay(1);
  }
  opcion = ""; // Limpiar Variable para proximo pedido. 
}
