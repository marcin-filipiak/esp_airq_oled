# FLAGMAN AirQ OLED - ESP8266

Projekt wykorzystuje ESP8266 i wyświetlacz OLED do monitorowania jakości powietrza za pomocą własnego API AirQ.
Układ wyświetlający dane jest nazywany flagman.

## Funkcje

- **Rejestracja urządzenia ("flagman")**  
  ESP8266 pobiera unikalną nazwę urządzenia z serwera i zapisuje ją w pamięci EEPROM.

- **Odczyt jakości powietrza**  
  Pobiera dane w formacie JSON, np. `{"aq":"1","time":1761737001}` i wyświetla status na OLED:
  - `0` – Bardzo dobre
  - `1` – Dopuszczalne
  - `2` – Niezdrowe dla wrażliwych
  - `3` – Ostrzeżenie zdrowotne
  - `4` – Alarm
  - `5` – Zagrożenie życia

- **Wyświetlanie statusu na OLED**  
  Każdy poziom jakości powietrza wyświetla odpowiedni tekst i grafikę na ekranie.

## Wymagania

- ESP8266
- Wyświetlacz OLED (U8g2)
- Biblioteki:
  - ESP8266WiFi
  - ESP8266HTTPClient
  - U8g2
  - ArduinoJson
  - EEPROM

## Instalacja

1. Skopiuj projekt do Arduino IDE.
2. Zainstaluj wymagane biblioteki.
3. Wgraj na ESP8266.
3. Skonfiguruj ESP8266 przez terminal UART.



