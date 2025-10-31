# AirQ – System monitorowania jakości powietrza

AirQ to projekt składający się z dwóch głównych komponentów: serwera PHP zarządzającego danymi o jakości powietrza oraz urządzenia ESP8266 z wyświetlaczem OLED, zwanego **flagmanem**, które wizualizuje stan powietrza lokalnie.

---

## Komponenty projektu

### 1. Flagman AirQ OLED (ESP8266)

Urządzenie ESP8266 wyposażone w wyświetlacz OLED monitoruje i wyświetla jakość powietrza w czasie rzeczywistym.

**Funkcje:**

* Rejestracja unikalnego flagmana w systemie poprzez serwer.
* Pobieranie danych jakości powietrza w formacie JSON, np. `{"aq":"1","time":1761737001}`.
* Wyświetlanie statusu na OLED według poziomu AQI:

  * 0 – Bardzo dobre
  * 1 – Dopuszczalne
  * 2 – Niezdrowe dla wrażliwych
  * 3 – Ostrzeżenie zdrowotne
  * 4 – Alarm
  * 5 – Zagrożenie życia
* Wyświetlanie tekstu i symboli graficznych dla każdego poziomu jakości powietrza.

**Wymagania:**

* ESP8266
* Wyświetlacz OLED kompatybilny z U8g2
* Biblioteki: ESP8266WiFi, ESP8266HTTPClient, U8g2, ArduinoJson, EEPROM

---

### 2. Serwer AirQ

Modułowy system zarządzania flagmanami i danymi o jakości powietrza, działający na serwerze PHP z bazą MySQL/MariaDB.

**Funkcjonalności:**

* Rejestracja flagmanów z unikalnym identyfikatorem i zapisem ostatniego połączenia.
* Przypisywanie flagmanów do stacji pomiarowych poprzez formularz webowy.
* Pobieranie danych AQI z lokalnych i zewnętrznych źródeł (AQICN, GIOS).
* System cache przechowujący dane w plikach z automatycznym odświeżaniem.
* JSON API umożliwiające zdalny dostęp do danych przez flagmany i aplikacje.

**Baza danych:**

* `AirQ_flagman` – przechowuje identyfikatory flagmanów, przypisanie do stacji, datę ostatniego połączenia i adres IP.
* `AirQ_station` – przechowuje dane stacji pomiarowych i ich powiązanie z zewnętrznymi źródłami AQICN/GIOS.

**Technologie:**

* PHP 8.x
* MySQL / MariaDB
* HTML + CSS dla formularza webowego
* JSON API do komunikacji z urządzeniami

---

## Schemat działania

1. Flagman łączy się z serwerem i rejestruje swoją nazwę.
2. Użytkownik zapisuje flagmana w bazie danych i przypisuje do stacji pomiarowej w formularzu web.
3. Flagman cyklicznie pobiera dane AQI w formacie JSON.
4. OLED wyświetla aktualny stan jakości powietrza w postaci tekstu i grafiki.

---

## Instalacja

### Flagman ESP8266

1. Skopiuj projekt do Arduino IDE.
2. Zainstaluj wymagane biblioteki.
3. Wgraj program na ESP8266.
4. Skonfiguruj urządzenie przez terminal UART.

### Serwer PHP

1. Wgraj moduł AirQ na serwer obsługujący PHP i MySQL/MariaDB.
2. Utwórz bazę danych i tabele `AirQ_flagman` oraz `AirQ_station`.
3. Skonfiguruj połączenie z bazą danych w module.
4. Korzystaj z API i formularza webowego do obsługi flagmanów.

---

## Przykłady użycia API

* **Rejestracja flagmana:**
  `GET index.php?flagman=register` → zwraca JSON z nową nazwą flagmana.
* **Pobranie danych flagmana:**
  `GET index.php?flagman=FLAG1234` → zwraca aktualne dane AQI w formacie JSON.
* **Przypisanie flagmana do stacji:**
  `GET index.php` → wyświetla formularz webowy do przypisania flagmana.

