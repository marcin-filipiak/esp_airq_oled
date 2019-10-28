////////////zapis konfiguracji///////////
void write_config(){
  
  char z = ' ';
  char index = 0;

  clear_array(data.ssid,32);
  clear_array(data.pass,32);

  Serial.println("Podaj SSID:");
  read_uart(data.ssid);
  Serial.println("SSID:"+String(data.ssid));


  Serial.println("Podaj haslo:");
  read_uart(data.pass);
  Serial.println("haslo:"+String(data.pass));

  Serial.println("name_flagman:"+String(data.name_flagman));

  data.set = 1;
  
  EEPROM.put(0,data);
  EEPROM.commit();
  
}

////////////wczytaj konfiguracje/////////////
void read_config(){
  
  String ssid = "";
  String haslo = "";
  String name_flagman="";

  EEPROM.get(0,data); 
  
  ssid = data.ssid;
  haslo = data.pass;
  name_flagman = data.name_flagman;

  Serial.println(" ");
  Serial.println("SSID: "+ssid);
  Serial.println("Haslo: "+String(data.pass));
  Serial.println("name_flagman: "+name_flagman);  
}
