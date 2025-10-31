<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

require_once("config.php");
require_once("libs/db/dbclass.php");
require_once("model/ModelAirQ.php");
require_once("libs/gios/gios.php");
require_once("libs/aqicn/aqicn.php");
require_once("libs/FileCache/FileCache.php");

header('Content-Type: application/json; charset=utf-8');

$DB = new DB();
$AirQ = new AirQ($DB);
$AirQGios = new AirQGios();
$AirQAqicn = new AirQAqicn(AQICN_TOKEN);

$flagman = isset($_GET['flagman']) ? $_GET['flagman'] : '';

if ($flagman === 'register') {
    // generujemy nowy kod flagmana
    $znaki = '0123456789QWERTYUIOPASDFGHJKLZXCVBNM';
    $len_id = 10;
    $str = '';
    for ($i = 0; $i < $len_id; $i++) {
        $str .= substr($znaki, mt_rand(0, strlen($znaki) -1), 1);
    }

    $AirQ->register_flagman($str);
    echo json_encode(["name_flagman" => $str]);
    exit;
}

// jeśli flagman został podany
if ($flagman !== '') {
    $AirQ->activity_flagman($flagman);
    $fg = $AirQ->get_flagman($flagman);

    if (!isset($fg['id_station']) || $fg['id_station'] == 0) {
        echo json_encode(["error" => "flagman not paired"]);
        exit;
    }

    $station = $AirQ->get_station($fg['id_station']);
    
    $FC = new FileCache(__DIR__ ."/cache/".$flagman.".txt");
    //jesli dane nieaktualne (w sekundach 2700) to zakeszowanie nowych, jesli brak danych to zrobienie
	if ($FC->Cdata['created'] > 2700 || $FC->Cdata['exist'] == 0){
            //pobranie danych AQICN
            $q = $AirQAqicn->show_quality($station['id_aqicn']);

            //jesli brak danych to z GIOS
            if ($q == "" || $q == -1) {
                $q = $AirQGios->show_quality($station['id_gios']);
            }
            
            //zapisanie danych
			$FC->save($q);
    }
    
    $d = $FC->Cdata['content'];
    
    // jeśli brak danych
    if ($d == "" || $d == -1) {
                echo json_encode(["error" => "no data"]);
                exit;
    }

    echo json_encode([
        "aq" => strval($d),
        "time" => time()
    ]);
    exit;
}


// === Formularz przypisania flagmana ===
if ($flagman === '') {

    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $flagmanName = strtoupper(trim($_POST['flagman'] ?? ''));
        $stationId = intval($_POST['station'] ?? 0);

        if ($flagmanName !== '' && $stationId > 0) {
            // użycie modelu zamiast bezpośredniego SQL
            $success = $AirQ->pair_flagman($flagmanName, $stationId);
            if ($success) {
                $message = "Flagman {$flagmanName} został przypisany do stacji ID {$stationId}.";
            } else {
                $message = "Nie znaleziono flagmana o nazwie {$flagmanName}.";
            }
        } else {
            $message = "Uzupełnij wszystkie pola.";
        }

        header('Content-Type: text/html; charset=utf-8');
        include(__DIR__ . '/view/form.php');
        exit;
    }

    // GET — wyświetlenie formularza
    header('Content-Type: text/html; charset=utf-8');
    include(__DIR__ . '/view/form.php');
    exit;
}



// brak parametru flagman
//echo json_encode(["error" => "missing parameter"]);
exit;
?>

