void printHeader(){ // Funcion que imprime el encabezado de presentacion del codigo:
  Serial.println("|-----------------------------------------------------|");
  Serial.println("|--------- Dispositivo de Monitoreo Ambiental --------|");
  Serial.println("|---------- Environmental Monitoring Device ----------|");
  Serial.println("|-----------------------------------------------------|");
  Serial.println("|------ Codificado por: Sergio Pinilla Valencia ------|");
  Serial.println("|---------- Fecha de Creacion: 16 julio 2024 ---------|");
  Serial.println("|--------- Ultima Modificacion: 01 agosto 2024 -------|");
  Serial.println("|---------- Lugar: TecnoAcademia - Manizales ---------|");
  Serial.println("|-----------------------------------------------------|");
  Serial.println("|-----------------------------------------------------|");
  Serial.println("");
}


void printCustomMessage(String selector){ // Funcion para imprimir mensajes personalizados:
  if(selector == "Bienvenido"){
    Serial.println();
    Serial.println();
    Serial.println("\t______ _                           _     _       \t");
    Serial.println("\t| ___ (_)                         (_)   | |      \t");
    Serial.println("\t| |_/ /_  ___ _ ____   _____ _ __  _  __| | ___  \t");
    Serial.println("\t| ___ \\ |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\ \t");
    Serial.println("\t| |_/ / |  __/ | | \\ V /  __/ | | | | (_| | (_) |\t");
    Serial.println("\t\\____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/ \t");
    Serial.println();
    Serial.println();
  }
}


void printSensorData(){ // Funcion que imprime datos sensados en el monitor Serial:
  sprintf(buffer, "%2d/%2d/%4d - %2d:%2d:%2d", ahora.day(), ahora.month(), ahora.year(), ahora.hour(), ahora.minute(), ahora.second());
  Serial.print(buffer);
  Serial.print("        Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C       Presion: ");
  Serial.print(pres);
  Serial.print(" hPa      Altitud: ");
  Serial.print(alti);
  Serial.println("m"); // Metros
}


void printEncoderData(){ // Funcion que imprime los datos del encoder en el monitor Serial: 
  Serial.print("Pasos Encoder: ");
  Serial.print(steps);
  Serial.print("      Dir: ");
  Serial.println(currentDir);
}
