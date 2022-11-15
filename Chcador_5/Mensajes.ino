void mnsj_ini() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Bienvenido");
  lcd.setCursor (2, 1);
  lcd.write(byte(0));
  lcd.setCursor(4, 1);
  lcd.print("Ibot4Fun");
  lcd.setCursor (13, 1);
  lcd.write(byte(1));
}

void mnsj_wifi() {
  lcd.clear();
  lcd.home();
  lcd.print("Conectando...");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  //Serial.println();
  lcd.clear();
  lcd.home();
  lcd.print("Wifi conectado");
  lcd.setCursor(0, 1);
  lcd.print("correctamente");
  delay(1500);
  //Serial.print("Conectado, dirección IP: ");
  //Serial.println(WiFi.localIP());
}

void mnsj_nombre() {
  /*S*E*P*A*R*A*R**D*A*T*A*/
  String hora = s.separa(data_recibida, '-', 0);
  String nombre = s.separa(data_recibida, '-', 1);
  /*S*E*P*A*R*A*R**D*A*T*A*/
  lcd.clear();
  lcd.home();
  if (nombre == "Javi" || nombre == "Javier") {
    lcd.print("Hola " + nombre + " ");
    lcd.write(byte(5));
  } else {
    lcd.print("Hola " + nombre + " ");
    lcd.write(byte(4));
  }
  //lcd.print(nombre);
  lcd.setCursor(0, 1);
  lcd.print(hora + " ");
  lcd.write(byte(2));
}

void tag_rfid() { //Muestra el tag de la tarjeta
  lcd.clear();
  lcd.home();
  lcd.print("Tag RFID: ");
  lcd.setCursor(0, 1);
  lcd.print(numero2);
}

void espera() {
  lcd.clear();
  lcd.home();
  lcd.print("Enviando datos...");
  lcd.setCursor(0, 1); //
  lcd.write(byte(3));//Animar
  delay(500);
  lcd.write(byte(3));
  delay(500);
  lcd.write(byte(3));
}
