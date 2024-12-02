/* |-----------------------------------------------------|
 * |------------- prueba de funcionamiento --------------|
 * |------------------ Modulo MicroSD -------------------|
 * |-----------------------------------------------------|
 * |------ Codificado por: Sergio Pinilla Valencia ------|
 * |---------- Fecha de Creacion: 05 Julio 2024 ---------|
 * |--------- Ultima Modificacion: 13 Julio 2024 --------|
 * |---------- Lugar: TecnoAcademia - Manizales ---------|
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Descripcion ---------------------|
 * |-----------------------------------------------------|
 * | El presente codigo muestra la implementacion        | 
 * | (lectura y escritura) del modulo MicroSD para       | 
 * | almacenar las muestras de Temperatura, y Presion    |
 * | Atmosferica (°C y hPa) presente en el ambiente.     |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------- Conexiones ----------------------|
 * |-----------------------------------------------------|
 * | Modulo MicroSD:                                     |
 * |    CS   -> Pin D10                                  |      
 * |    MOSI -> Pin D11                                  |      
 * |    SCK  -> Pin D13                                  |      
 * |    MISO -> Pin D12                                  |      
 * |    +5v -> 5v Arduino                                |
 * |    GND -> Ground Arduino                            |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------------ Bibliografia ---------------------|
 * |-----------------------------------------------------|
 * | Libreria: https://n9.cl/z0hjuf                      |
 * | Guia de Funcionamiento: https://n9.cl/nbez7         |
 * | Tutorial Simple: https://n9.cl/s88k9                |
 * |-----------------------------------------------------|
 * |-----------------------------------------------------|*/

/* |-----------------------------------------------------|
 * |------------- Librerias y Constantes ----------------|
 * |-----------------------------------------------------| */
#include <SPI.h>
#include <SD.h> // Libreria necesaria para la comunicacion SPI entre el modulo SD y el arduino.

#define SSPIN 10 // Pin de Arduino donde va conectado el pin CS del modulo SD.


/* |-----------------------------------------------------|
 * |-------- Declaracion de Variables y Objetos ---------|
 * |-----------------------------------------------------| */
File datos; // Crear objeto Archivo que permite manipular los datos a enviar o leer a la SD.

const char filename[] = "datalog.csv";
float temp, pres, alti; // variables para almacenar los valores medidos por el sensor. .


/* |-----------------------------------------------------|
 * |---------------- Zona Configuracion -----------------|
 * |-----------------------------------------------------| */
void setup() {
  Serial.begin(9600);
  while (!Serial) { // Esperar hasta que se Abra el Canal Serial.
  }

  Serial.println("¡Canal Serial Abierto!");
  Serial.println("");
  
  Serial.print("Iniciando SD...");
  
  for(int i=0; i<=10; i++){
    if(!SD.begin(SSPIN)){
      Serial.print(".");
      delay(1000);
    } else{
      Serial.println(" ¡Modulo SD Encontrado!\n");
      break;
    }

    if(i==10){
      Serial.println(" |Error al inicializar el modulo SD.");
      Serial.println("1. Revisa la Conexion.");
      Serial.println("2. Reinicia el arduino.");
      Serial.println("3. vuelve a intentarlo.");
      while(1){};
    }
  }

  if(!SD.exists(filename)){
    datos = SD.open(filename, FILE_WRITE);

    if(datos){
      Serial.println("archivo Nuevo Creado, Escribiendo encabezados (Fila 1)...");
      datos.println("Temperatura(°C),Presion(hPa),Altitud(m)");
      datos.close();
    } else{
      Serial.println("Error al crear el nuevo archivo");
    }
  }

  randomSeed(analogRead(A0)); // Establecer semilla para secuencia de numeros aleatorios diferentes a aprtir del ruido del pin analogico.

  delay(2000);
}


/* |-----------------------------------------------------|
 * |------------------ Codigo Principal -----------------|
 * |-----------------------------------------------------| */
void loop(){
  datos = SD.open(filename, FILE_WRITE); // Instruccion para abrir el archivo donde se almacenara la informacion recolectada.
  
  temp = random(23,35) + (random(0,9)/100); // Generar valor aleatorio para temperatura. 
  pres = random(1,100) + (random(0,9)/100); // Generar valor aleatorio para presion.
  alti = random(1,100) + (random(0,9)/100); // Generar valor aleatorio para altitud.

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C       Presion: ");
  Serial.print(pres);
  Serial.print(" hPa      Altitud: ");
  Serial.print(alti);
  Serial.println("m"); // Metros

  if(datos){
    datos.print(temp);
    datos.print(",");
    datos.print(pres);
    datos.print(",");
    datos.println(alti);

    datos.close(); // Cerrar el archivo.
  } else{
    Serial.println("Error al abrir el archivo");
  }

  delay(1000);
}
