#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

bool quality() {
  if (WiFi.status() != WL_CONNECTED) return false;

  String fn = data.name_flagman;
  WiFiClient client;
  HTTPClient http;

  http.begin(client, "http://api.filipiak.cc/?mod=airq&flagman=" + fn);
  int httpCode = http.GET();
  bool success = false;  // flaga powodzenia
  

  if (httpCode > 0) {
    String payload = http.getString();                  

    Serial.println("HTTP code: " + String(httpCode));
    Serial.println("Payload len: " + String(payload.length()));
    Serial.println("Payload: " + payload);

    StaticJsonDocument<500> doc;
    DeserializationError error = deserializeJson(doc, payload);
    u8g2.clearBuffer();

    if (!error) {
        const char* aq = doc["aq"];
        if (strcmp(aq, "0") == 0) { u8g2.drawStr(45, 0, "Bardzo"); u8g2.drawStr(45, 15, "dobre"); oled_bardzo_dobre(); }
        else if (strcmp(aq, "1") == 0) { u8g2.drawStr(45, 0, "Dopuszczalne"); oled_dopuszczalne(); }
        else if (strcmp(aq, "2") == 0) { u8g2.drawStr(45, 0, "Niezdrowe"); oled_niezdrowe(); }
        else if (strcmp(aq, "3") == 0) { u8g2.drawStr(45, 0, "Ostrzezenie"); oled_ostrzezenie(); }
        else if (strcmp(aq, "4") == 0) { u8g2.drawStr(45, 0, "Alarm"); oled_alarm(); }
        else if (strcmp(aq, "5") == 0) { u8g2.drawStr(45, 0, "Zagrozenie"); u8g2.drawStr(45, 15, "zycia!"); oled_zagrozenie(); }
        else { u8g2.drawStr(0, 0, "Nieznany stan"); }
        success = true;  // dane poprawnie sparsowane
    } else {
        u8g2.drawStr(0, 0, "Brak odczytu");
        delay(1000);
    }

    u8g2.sendBuffer();
  } else {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 0, "Blad komunikacji");
    u8g2.sendBuffer();
    delay(1000);
  }

  http.end();
  return success;
}


void register_flagman() {
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.println("Rejestrowanie...");
        
    WiFiClient client;
    HTTPClient http;
    http.begin(client, "http://api.filipiak.cc/?mod=airq&flagman=register");  
    int httpCode = http.GET();            
    if (httpCode > 0) {                    
      String payload = http.getString();  
      Serial.println("Odpowiedz serwera: " + payload);             

      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
          const char* rf = doc["name_flagman"];

          // zapisanie name_flagman do pamieci
          clear_array(data.name_flagman, 11);
          for (int x = 0; x < 11 && x < strlen(rf); x++) {
              data.name_flagman[x] = rf[x];
          }
          EEPROM.put(0, data);
          EEPROM.commit();

          Serial.println("Zapisano name_flagman: " + String(rf));
      } else {
          Serial.println("Blad parsowania JSON");
      }
    }
    http.end();                            
  }  
}
