////////////////skanowanie sieci/////////////////
void scan () {


  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.println("Skanowanie rozpoczete");


  int n = WiFi.scanNetworks();
  Serial.println("Skanowanie zakonczone");
  if (n == 0)
    Serial.println("");
  else
  {
    Serial.print(n);
    Serial.println(" znalezionych sieci");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");
}

////////////polaczenie z wifi/////////////////
void connect_wifi(){
  
      u8g2.setFont(u8g2_font_6x10_tf);
  
      char x=0;
      WiFi.begin(data.ssid, data.pass);
      
      u8g2.drawStr(0, 0, "Laczenie z WiFi");
      
      while (WiFi.status() != WL_CONNECTED && x<7) {
        u8g2.drawStr(x*11, 10, "*");
        u8g2.sendBuffer();
        delay(1000);
        x++;
      }
      if (x<7){
        u8g2.drawStr(0, 20, "Polaczono z WiFi");
        u8g2.sendBuffer();
        Serial.print("Polaczony\n");
        //pobranie jakosci powietrza
        quality();
      }
      else {
        Serial.print("Blad WiFi\n");
        u8g2.drawStr(0, 20, "Blad WiFi");
        u8g2.sendBuffer();
      }
      delay(2000);
}

//////////Polaczenie z wifi z wznawianiem/////////
bool connect_wifi_nonblocking() {
  if (WiFi.status() == WL_CONNECTED) return true;

  WiFi.mode(WIFI_STA);
  WiFi.begin(data.ssid, data.pass);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 7000) { // max 7s
    u8g2.clearBuffer();
    u8g2.drawStr(0, 0, "Laczenie...");
    u8g2.sendBuffer();
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Polaczono z WiFi");
    u8g2.clearBuffer();
    u8g2.drawStr(0, 0, "Polaczono z WiFi");
    u8g2.sendBuffer();
    delay(1000);
    return true;
  } else {
    Serial.println("Blad WiFi");
    u8g2.clearBuffer();
    u8g2.drawStr(0, 0, "Blad WiFi");
    u8g2.sendBuffer();
    delay(1000);
    return false;
  }
}

