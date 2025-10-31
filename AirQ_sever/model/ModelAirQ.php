<?php

class AirQ {

    private $db;

	public function __construct(&$db) {
        	$this->db = $db;
	}

	public function getip(){    
		return $_SERVER['REMOTE_ADDR'];	
	}

	//pobranie informacji o sygnalizatorze
    public function get_flagman($name_flagman){
        $name_flagman = strtoupper($name_flagman);
        $query = "SELECT * FROM AirQ_flagman WHERE name_flagman='$name_flagman'";
        $result = $this->db->sql_query($query);
        $row = $this->db->sql_fetcharray($result);
        return $row ?: null;  // jeśli brak wyniku, zwróć null
    }

	//zarejestrowanie sygnalizatora w systemie
    public function register_flagman($name_flagman){
        $name_flagman = strtoupper($name_flagman);
        $datetime = date("Y-m-d H:i:s");
        $ip = $this->getip();
        
        // pobranie danych o sygnalizatorze
        $f = $this->get_flagman($name_flagman);

        // jeśli brak go w systemie (null lub pusty)
        if ($f === null || empty($f['name_flagman'])) {
            // dodanie do systemu
            $query = "INSERT INTO AirQ_flagman 
                      (name_flagman,last_connection,ip) 
                      VALUES ('$name_flagman','$datetime','$ip')";
            $this->db->sql_query($query);
            return 1;
        }

        // był w systemie
        return 0;
    }


	//zarejestrowanie aktywnosci flagmana
	public function activity_flagman($name_flagman){

		$name_flagman = strtoupper($name_flagman);
		$datetime = date("Y-m-d H:i:s");
		$ip = $this->getip();

		$fl = $this->get_flagman($name_flagman);
		if ($fl['name_flagman'] != ""){
			$query = "UPDATE AirQ_flagman 
				  SET ip='$ip', last_connection = '$datetime'  
				  WHERE name_flagman='$name_flagman'";
		        $this->db->sql_query($query);	
			return 1;
		}
		else {
			return 0;
		}
	}

	//polaczenie sygnalizatora ze stacja
    public function pair_flagman($name_flagman,$id_station){
        $name_flagman = strtoupper($name_flagman);
        $fl = $this->get_flagman($name_flagman);

        if ($fl !== null && !empty($fl['name_flagman'])) {
            $query = "UPDATE AirQ_flagman SET id_station='$id_station' WHERE name_flagman='$name_flagman'";
            $this->db->sql_query($query);
            return 1;
        }
        return 0;
    }

	//pobranie listy stacji
	public function list_station(){
		$query = "SELECT * FROM AirQ_station ORDER BY name";
		$result = $this->db->sql_query($query);
		if ($result) {
        	        $row = $this->db->sql_fetchassoc($result);
			return $row;
		}
	}

	//pobranie stacji
	public function get_station($id_station){
		$query = "SELECT * FROM AirQ_station WHERE id_station = '$id_station' ";
		$result = $this->db->sql_query($query);
		if ($result) {
        	        $row = $this->db->sql_fetcharray($result);
			return $row;
		}
	}

}

?>
