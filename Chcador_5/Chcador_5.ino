/*
   Checador JJ
   Javier Martínez
   V 5.0 16-08-2022
   Versión de placa 3.0.2
   Versión estable (Envia tag rfid y regresa nombre y hora)
*/

//L I B R E R I A S
/*lcd*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
/*rfid*/
#include <SPI.h>
#include <MFRC522.h>
/*servicio web*/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
/*separar datos*/
#include <Separador.h>

//C O N S T A N T E S
/*rfid*/
#define rst_pin D3 //Reset
#define ss_pin D4 //SDA
/*servicio web*/
const char* ssid = "Ibot4Wifi2.4";
const char* password = "PD$75nk8pK";
const char* myDomain = "script.google.com";
const String script_id = "AKfycbx0fbENw1MJdH4xPHX8XOFqLUbcXx55NffjL_VxkAFXymuoXfRdIOH7bt4XOSjEytlSGQ";
const String script = "/macros/s/AKfycbx0fbENw1MJdH4xPHX8XOFqLUbcXx55NffjL_VxkAFXymuoXfRdIOH7bt4XOSjEytlSGQ/exec";

//O B J E T O S
/*lcd*/
LiquidCrystal_I2C lcd (0x27, 16, 2); //Objeto lcd
/*rfid*/
MFRC522 rfid(ss_pin, rst_pin);
/*Separador*/
Separador s;

//V A R I A B L E S
int numero = 0;//
String numero2 = "";
String data_recibida = "";

//C A R A C T E R E S
byte robot[8] = {
  B10001,
  B11111,
  B10101,
  B01110,
  B00100,
  B01110,
  B11111,
  B01010
};
byte nave [8] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B01110
};
byte campana [8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};
byte flash [8] {
  B00010,
  B00100,
  B01100,
  B11111,
  B00110,
  B01100,
  B01000,
  B10000

};
byte feliz [8] {
  B00000,
  B01010,
  B01010,
  B00000,
  B11111,
  B10001,
  B01110,
  B00000
};
byte corazon [8] {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //LCD
  lcd.init();//iniciar objeto lcd
  lcd.backlight();
  //Caracteres
  lcd.createChar(0, robot);
  lcd.createChar(1, nave);
  lcd.createChar(2, campana);
  lcd.createChar(3, flash);
  lcd.createChar(4, feliz);
  lcd.createChar(5, corazon);
  lcd.begin(16, 2);

  //rfid
  SPI.begin();
  rfid.PCD_Init();//iniciar el objeto rfid

  //Wifi
  WiFi.begin(ssid, password);
  mnsj_wifi();
  delay(2000);
  mnsj_ini();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent())//Buscamos una ajeta cerca de lector
    return;
  if (!rfid.PICC_ReadCardSerial()) //Leemos la tarjeta
    return;
  Serial.print ("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) { //Detecta el tamaño de bytes de la tarjeta
    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print (" 0");
    } else {
      Serial.print(" ");
    }

    //Serial.print(rfid.uid.uidByte[i],HEX);//Ver cadena de bytes en Hexadecimal

    numero = int (rfid.uid.uidByte[i]);//Valor en bytes
    numero2 += numero; //Almacena el UID en un valor del tipo int en un String //Para enviar
    Serial.print(numero, DEC); //Ver cadena de bytes en decimal
  }
  Serial.println();
  //tag_rfid();
  espera ();
  enviarDatosCloud();
  delay (1500);
  recibirDatosCloud();
  mnsj_nombre();
  Serial.println(data_recibida);
  delay(3000);
  /*Limpiar variables*/
  numero2 = "";
  mnsj_ini();
  rfid.PICC_HaltA();//Finalizar servicio rfid
}
