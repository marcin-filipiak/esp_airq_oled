# SERWER AirQ – System monitorowania jakości powietrza

## Opis projektu
AirQ to modułowy system wymiany danych dotyczących jakości powietrza. Pozwala na rejestrację i obsługę tzw. **flagmanów** (sygnalizatorów), przypisywanie ich do stacji pomiarowych oraz pobieranie danych z lokalnych i zewnętrznych źródeł (AQICN, GIOS).

Moduł `airq` obsługuje logikę przypisywania flagmanów do stacji i zapewnia mechanizm cache’owania danych w plikach. Projekt jest przygotowany do uruchomienia na serwerze PHP z bazą danych MySQL/MariaDB.

---

## Funkcjonalności

### Rejestracja flagmana
- Tworzenie unikalnych identyfikatorów flagmanów.
- Przechowywanie daty ostatniego połączenia i adresu IP.
- Możliwość sprawdzenia, czy flagman istnieje w systemie.

### Przypisywanie flagmana do stacji
- Formularz webowy (`form.php`) pozwalający przypisać istniejącego flagmana do wybranej stacji.
- Walidacja danych wejściowych oraz komunikaty o błędach, jeśli flagman nie istnieje.

### Pobieranie danych o jakości powietrza
- Mechanizm pobierania danych z API AQICN i GIOS.
- Plikowa pamięć podręczna (`FileCache`) z możliwością automatycznego odświeżania po upływie określonego czasu.
- API JSON umożliwia dostęp zdalny przez urządzenia i aplikacje.

### System cache
- Cache przechowywany w plikach w katalogu modułu.
- Automatyczne ustawianie daty utworzenia przy pierwszym zapisie.
- Sprawdzanie wieku danych w sekundach, aby odświeżać informacje tylko w razie potrzeby.

---

## Baza danych

### Tabela `AirQ_flagman`
| Kolumna          | Typ         | Opis                        |
|-----------------|------------|-----------------------------|
| id_flagman      | int        | ID flagmana (auto_increment)|
| name_flagman    | varchar(10)| Nazwa flagmana              |
| id_station      | int        | ID przypisanej stacji       |
| last_connection | datetime   | Data ostatniego połączenia  |
| ip              | varchar(20)| Adres IP flagmana           |

### Tabela `AirQ_station`
| Kolumna   | Typ        | Opis                       |
|----------|-----------|-----------------------------|
| id_station | int      | ID stacji (auto_increment) |
| name       | varchar(50) | Nazwa stacji             |
| id_aqicn  | int       | ID stacji w API AQICN       |
| id_gios   | int       | ID stacji w GIOS            |

---

## Technologie
- PHP 8.x
- MySQL / MariaDB
- HTML + CSS (formularz przypisania flagmana)
- JSON API do wymiany danych

---

## Przykłady użycia API
- Rejestracja flagmana:  
`GET index.php?flagman=register` → zwraca JSON z nową nazwą flagmana.  

- Pobranie danych flagmana:  
`GET index.php?flagman=FLAG1234` → zwraca aktualne dane AQI w formacie JSON.  

- Formularz przypisania flagmana do stacji:  
`GET index.php` → wyświetla estetyczny formularz webowy.

