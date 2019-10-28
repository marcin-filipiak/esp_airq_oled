//Plytka Generic ESP8266 Module

#include "ESP8266WiFi.h"
#include <EEPROM.h>

struct {
    uint set = 0;
    char name_flagman[11]="";
    char ssid[32] = "";
    char pass[32] = "";
  } data;


//OLED//
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ 16);

//ustawianie ekranu//
void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.setFontMode(0); // disable transparent font mode 
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

//czyszczenie tablicy//
void clear_array(char *a, int s){
  for(int x=0;x<s;x++){
    a[x]='\0';
  }
}

////pobranie danych z uart do tablicy////
void read_uart(char *r){
    char z = ' ';
    char index = 0;
  
    do {  
    if (Serial.available()>0) {
      z = Serial.read();
      if (z != '\n'){
        r[index] = z;
        index ++;
      }
    }
  } while (z!='\n');
  r[index+1]='\0';
}

#include "include/buzie.h"
#include <ESP8266HTTPClient.h>
#include "include/AirQ_api.h"
#include "include/wifi.h"
#include "include/config.h"

////////////menu///////////////////////
void help(){
  Serial.println("s - skanuj sieci");
  Serial.println("c - konfiguruj siec");
  Serial.println("r - rejestruj");
  Serial.println("o - czytaj konfiguracje");
  Serial.println("j - polacz z siecia");
  Serial.println("h - wyswietl to menu");
}


//////////////minuter///////////////////
int ticker = 0;
int polh = 0;
//w tym wsadzie zwraca 1 co 60 sekund
int minuter(){
  delay(10);
  ticker++;
  if (ticker > 6000){
    ticker = 0;
    return 1;
  }
  else {
    return 0;
  }
}

//////////////////////SETUP/////////////////
void setup() {
  Serial.begin(115200);
  
  EEPROM.begin(512); //ile pamieci
  
  delay(300);
  u8g2.begin(); //uruchomienie ekranu

  u8g2_prepare();
  u8g2.clearBuffer();
  u8g2.drawStr(0, 0, "AirQ");
  u8g2.drawStr(0, 15, "NoweEnergie.org");
  u8g2.sendBuffer();
  delay(1000);

  //czyszczenie ekranu
  u8g2.clearBuffer();
  u8g2.sendBuffer();
  
  read_config();

  if (data.set == 1){
    connect_wifi();
  }
      
 help();
}

/////////////////LOOP//////////////////
void loop() {
  u8g2_prepare();
  u8g2.clearBuffer();

  //jesli minela minuta
  if (minuter() == 1){
    //doliczenie minuty do licznika 10 minut
    polh++;
      //jesli minelo 30 minut
      if (polh > 29){
          //pobranie danych jakosci powietrza
          quality();
          polh = 0;
      }
      //Serial.println("minuta");
  }
  
  //jesli przyszly dane
  if (Serial.available()>0) { 
    char z[3];
    read_uart(z);
    
    //skanowanie sieci
    if (z[0] == 's'){
        scan();
    }
    //konfiguruj siec
    if (z[0] == 'c'){
      write_config();
    }
    //rejestruj
    if (z[0] == 'r'){
      register_flagman();
    }
    //czytaj konfiguracje
    if (z[0] == 'o'){
      read_config();
    }
    //polacz
    if (z[0] == 'j'){
      connect_wifi();
    }
    //help
    if (z[0] == 'h'){
      help();
    }
  }
}
