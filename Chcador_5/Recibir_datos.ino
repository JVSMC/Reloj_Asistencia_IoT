void recibirDatosCloud() {
 //-----------------------------------------------------------------------------------
   std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
   client->setInsecure();
   HTTPClient https;
   String url= "https://script.google.com/macros/s/"+script_id+"/exec?read";
   Serial.println("Reading Data From Google Sheet.....");
   https.begin(*client, url.c_str());
   //-----------------------------------------------------------------------------------
   //Removes the error "302 Moved Temporarily Error"
   https.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
   //-----------------------------------------------------------------------------------
   //Get the returning HTTP status code
   int httpCode = https.GET();
   Serial.print("HTTP Status Code: ");
   Serial.println(httpCode);
   //-----------------------------------------------------------------------------------
   if(httpCode <= 0){Serial.println("Error on HTTP request"); https.end(); return;}
   //-----------------------------------------------------------------------------------
   //reading data comming from Google Sheet
   String payload = https.getString();
   Serial.println("Payload: "+payload);
   //-----------------------------------------------------------------------------------
   if(httpCode == 200)
   data_recibida= payload;
   //-------------------------------------------------------------------------------------
   https.end();
}
