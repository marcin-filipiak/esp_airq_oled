<?php
/*****************
Dane z http://powietrze.gios.gov.pl/pjp/content/api

OpenApi zgodne ze zmianami 30.06.2025 r
******************/

class AirQGios {


    public function __construct() {
    }


    //pobranie danych ze stacji
    public function show_quality($id) {
        $json = file_get_contents("https://api.gios.gov.pl/pjp-api/v1/rest/aqindex/getIndex/$id");
        $obj = json_decode($json, true); // konwersja na tablicę

        if (isset($obj['AqIndex']['Wartość indeksu'])) {
            $data = $obj['AqIndex']['Wartość indeksu'];
            return $data;
        } else {
            return null; // lub komunikat o błędzie
        }
    }

   //pobranie listy stacji
    public function list_station() {
        $json = file_get_contents("https://api.gios.gov.pl/pjp-api/v1/rest/station/findAll");
        $obj = json_decode($json, true);

        // Sprawdzenie czy struktura JSON jest poprawna
        if (!isset($obj['Lista stacji pomiarowych']) || !is_array($obj['Lista stacji pomiarowych'])) {
            return []; // brak danych
        }

        $stations = [];
        foreach ($obj['Lista stacji pomiarowych'] as $station) {
            $stations[] = [
                'id' => $station['Identyfikator stacji'] ?? null,
                'code' => $station['Kod stacji'] ?? null,
                'name' => $station['Nazwa stacji'] ?? null,
                'city' => $station['Nazwa miasta'] ?? null,
                'province' => $station['Województwo'] ?? null,
                'latitude' => $station['WGS84 φ N'] ?? null,
                'longitude' => $station['WGS84 λ E'] ?? null,
                'street' => $station['Ulica'] ?? null
            ];
        }

        return $stations;
    }



}

?>
