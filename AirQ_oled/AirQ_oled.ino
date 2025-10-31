// Płytka: Generic ESP8266 Module
// Biblioteki: U8g2, ESP8266WiFi, ESP8266HTTPClient

#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#include <ESP8266HTTPClient.h>

//========================================
// STRUKTURA KONFIGURACJI
//========================================
struct {
  uint set = 0;
  char name_flagman[11] = "";
  char ssid[32] = "";
  char pass[32] = "";
} data;

//========================================
// ZMIENNE GLOBALNE
//========================================
unsigned long last_wifi_attempt = 0;
unsigned long last_quality_attempt = 0;

const unsigned long quality_interval = 20;    // interwał pobierania danych m
const unsigned long wifi_retry_delay = 20UL * 1000UL;           // interwał ponawiania połączenia po jego utracie ms

bool waiting_for_quality = false;  //stan czy oczekiwanie na dane, po starcie tak

// OLED
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/5, /* data=*/4, /* reset=*/16);

//========================================
// FUNKCJE POMOCNICZE
//========================================
void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.setFontMode(0);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void clear_array(char *a, int s) {
  for (int x = 0; x < s; x++) {
    a[x] = '\0';
  }
}

void read_uart(char *r) {
  char z = ' ';
  char index = 0;
  do {
    if (Serial.available() > 0) {
      z = Serial.read();
      if (z != '\n') {
        r[index] = z;
        index++;
      }
    }
  } while (z != '\n');
  r[index + 1] = '\0';
}

void help() {
  Serial.println("s - skanuj sieci");
  Serial.println("c - konfiguruj siec");
  Serial.println("r - rejestruj");
  Serial.println("o - czytaj konfiguracje");
  Serial.println("j - polacz z siecia");
  Serial.println("h - wyswietl to menu");
}

//========================================
// TIMER MINUTOWY (około 60 sek)
//========================================
int ticker = 0;
int polh = 0;
int minuter() {
  delay(10);
  ticker++;
  if (ticker > 6000) {
    ticker = 0;
    return 1;
  }
  return 0;
}

//========================================
// BIBLIOTEKI POMOCNICZE
//========================================

#include "include/buzie.h"
#include "include/AirQ_api.h"
#include "include/wifi.h"
#include "include/config.h"


//========================================
// SETUP
//========================================
void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  delay(300);
  u8g2.begin();
  u8g2_prepare();

  u8g2.clearBuffer();
  u8g2.drawStr(0, 0, "AirQ");
  u8g2.drawStr(0, 15, "filipiak.cc");
  u8g2.sendBuffer();
  delay(1000);

  u8g2.clearBuffer();
  u8g2.sendBuffer();

  read_config();

  if (data.set == 1) {
    connect_wifi();
  }

  help();
}

//========================================
// LOOP
//========================================
void loop() {
  u8g2_prepare();

  unsigned long now = millis();

  // co minutę zwiększ licznik
  if (minuter() == 1) {
    polh++;
  }

  // jesli mamy quality_interval minut to rozpocznij cykl pobierania jakości
  if (polh > quality_interval && !waiting_for_quality) {
    waiting_for_quality = true;
    last_quality_attempt = now;
    polh = 0;
  }

  // próba pobrania danych (z nieblokującym łączeniem WiFi)
  if (waiting_for_quality) {
    // próba pobrania danych (nieblokujące WiFi)
      if (WiFi.status() == WL_CONNECTED) {
          // jeśli trzeba pobrać dane
          if (waiting_for_quality) {
              u8g2.clearBuffer();
              u8g2.drawStr(0, 0, "Pobieranie danych");
              u8g2.sendBuffer();

              // tylko jeśli pobranie powiodło się, resetujemy flagi
              if (quality()) {
                  waiting_for_quality = false;
                  polh = 0;
                  last_quality_attempt = now;
                  delay(400);
              }
          }
      } else {
          // brak WiFi – próbuj połączenia co wifi_retry_delay
          if (now - last_quality_attempt > wifi_retry_delay) {
              Serial.println("Próba połączenia z WiFi...");
              u8g2.clearBuffer();
              u8g2.drawStr(0, 0, "Laczenie WiFi");
              u8g2.sendBuffer();

              connect_wifi_nonblocking();
              last_quality_attempt = now;
          }
      }
  }

  // jeśli przyszły dane po UART
  if (Serial.available() > 0) {
    char z[3];
    read_uart(z);

    switch (z[0]) {
      case 's': scan(); break;
      case 'c': write_config(); break;
      case 'r': register_flagman(); break;
      case 'o': read_config(); break;
      case 'j': connect_wifi(); break;
      case 'h': help(); break;
    }
  }
}
