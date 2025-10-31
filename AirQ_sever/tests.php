<?
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

require_once("config.php");

require_once("libs/gios/gios.php");
$AirQGios = new AirQGios();
//$q = $AirQGios->show_quality(789); //bielsko-biala
//$q = $AirQGios->list_station();

require_once("libs/aqicn/aqicn.php");
$AirQAqicn = new AirQAqicn(AQICN_TOKEN);
$q = $AirQAqicn->show_quality(6535); //bielsko-biala

print_r($q);

?>
