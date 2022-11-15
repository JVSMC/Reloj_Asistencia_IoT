//NO FUNCIONA PERO PUEDES APRENDER
//void enviarDatosCloud() { 
//  if ((WiFi.status() == WL_CONNECTED)) {
//    WiFiClient client; //Crear objeto cliente
//    HTTPClient http;
//    Serial.print("[HTTP begin...\n]");
//    
//    http.begin(client, sheet_url"/postplain/");
//    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//    Serial.print("[HTTP] POST...\n");
//    int httpCode = http.POST("{\"hello\":\"world\"}");
//
//    //httpCode enviara un error
//    if (httpCode > 0) {
//      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
//      //Encontramos el servidor
//      if (httpCode == HTTP_CODE_OK) {
//        const String& payload = http.getString();
//        Serial.println("received payload:\n<<");
//        Serial.println(payload);
//        Serial.println(">>");
//      }
//    }else {
//      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
//      }
//      http.end();
//  }
//  delay(5000);
//}

void enviarDatosCloud() {
  WiFiClientSecure clientSecure;
  clientSecure.setInsecure();
  if (clientSecure.connect(myDomain, 443)) {
    Serial.println("Connection successful");

    String Data = "data=" + numero2; // data es la variable a enviar por medio del link
    clientSecure.println("POST " + script + " HTTP/1.1");
    clientSecure.println("Host: " + String(myDomain));
    clientSecure.println("Content-Length: " + String(Data.length()));
    clientSecure.println("Content-Type: application/x-www-form-urlencoded");
    clientSecure.println();

    clientSecure.print(Data);
    Serial.println("Waiting for response.");

    long int StartTime = millis();
    while (!clientSecure.available()) {
      Serial.print(".");
      delay(100);
      if ((StartTime + 60000) < millis()) {
        Serial.println();
        Serial.println("No response.");

        break;
      }
    }
    Serial.println();

    while (clientSecure.available()) {
      Serial.print(char(clientSecure.read()));
    }

  } else {
    Serial.println("Connected to " + String(myDomain) + " failed.");
    delay(2500);
  }
  clientSecure.stop();
}
