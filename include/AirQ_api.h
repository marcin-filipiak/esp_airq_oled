
void quality(){
  if (WiFi.status() == WL_CONNECTED) { 

    String fn = data.name_flagman;
        
    HTTPClient http; 
    http.begin("http://api.noweenergie.org/index.php?AirQ/quality/"+fn);  
    int httpCode = http.GET();             
    if (httpCode > 0) {                    
      String payload = http.getString();   
      Serial.println(":"+payload+":");            

      u8g2.clearBuffer();
      if (payload.substring(0) == "err") { 
          u8g2.drawStr(0, 0, "Brak odczytu"); 
      }
      // bardzo dobre
      if (payload.substring(0) == "0") { 
          u8g2.drawStr(45, 0, "Bardzo"); 
          u8g2.drawStr(45, 15, "dobre");
          oled_bardzo_dobre();
      }
      //dopuszczalne
      if (payload.substring(0) == "1") { 
          u8g2.drawStr(45, 0, "Dopuszczalne"); 
          oled_dopuszczalne();
      }
      //niezdrowe dla wrazliwych
      if (payload.substring(0) == "2") { 
          u8g2.drawStr(45, 0, "Niezdrowe"); 
          oled_niezdrowe();
      }
      //ostrzezenie zdrowotne
      if (payload.substring(0) == "3") { 
          u8g2.drawStr(45, 0, "Ostrzezenie");
          oled_ostrzezenie(); 
      }
      //poziom alarmowy
      if (payload.substring(0) == "4") { 
          u8g2.drawStr(45, 0, "Alarm");
          oled_alarm(); 
      }
      //zagrozenie zycia
      if (payload.substring(0) == "5") { 
          u8g2.drawStr(45, 0, "Zagrozenie"); 
          u8g2.drawStr(45, 15, "zycia!");
          oled_zagrozenie();
      }
      
      u8g2.sendBuffer();
    }
    http.end();                           
  }
}

///////////Rejestruj flagmana////////////////////////
void register_flagman(){
  if (WiFi.status() == WL_CONNECTED) { 
    
    //u8g2.clearBuffer();
    //u8g2.drawStr(0, 0, "Rejestrowanie");
    //u8g2.sendBuffer();
    Serial.println("Rejestrowanie...");
        
    HTTPClient http;  
    http.begin("http://api.noweenergie.org/index.php?AirQ/register_flagman");  
    int httpCode = http.GET();            
    if (httpCode > 0) {                    
      String rf = http.getString();  
      Serial.println("name_flagman: "+String(rf));             

      //zapisanie name_flagman do pamieci
      clear_array(data.name_flagman,11);
      for(int x=0;x<11;x++){
        data.name_flagman[x] = rf[x];
      }
      EEPROM.put(0,data);
      EEPROM.commit();

      //u8g2.clearBuffer();
      //u8g2.drawStr(0, 0, fn);
      //u8g2.sendBuffer();
    }
    http.end();                            
  }  
}
