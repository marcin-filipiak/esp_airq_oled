<?php
/*****************
Dane z http://aqicn.org/json-api/doc/
stacje http://aqicn.org/json-api/demo/
******************/

class AirQAqicn {

    private $token;

    public function __construct($token) {
	    $this->token = $token;
    }


    //pobranie danych ze stacji
     public function show_quality($id) {
        $url = "http://api.waqi.info/feed/@$id/?token=" . $this->token;
        $json = @file_get_contents($url);

        // jeśli brak odpowiedzi
        if ($json === false) {
            return -1;
        }

        $obj = json_decode($json);

        // sprawdzenie poprawności JSON
        if ($obj === null || !isset($obj->status)) {
            return -1;
        }

        // jeśli API zwraca błąd, np. {"status":"error","data":"Invalid key"}
        if ($obj->status !== "ok" || !isset($obj->data->iaqi->pm10->v)) {
            return -1;
        }

        $q = $obj->data->iaqi->pm10->v;

        // przeliczenie skali AQI (pm10)
        if ($q < 51) return 0;
        if ($q < 101) return 1;
        if ($q < 151) return 2;
        if ($q < 201) return 3;
        if ($q < 301) return 4;
        return 5;
    }



}

?>
