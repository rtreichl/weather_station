<?php

ini_set('display_errors', 1);

error_reporting(E_ALL | E_STRICT);

if(isset($_GET["sensor"]))
    $sensor = htmlspecialchars($_GET["sensor"]);
else
    $sensor = "Sensor2";

if(isset($_GET["what"]))
    $what = htmlspecialchars($_GET["what"]);
else
    $what = "sensors";

if(isset($_GET["data"]))
    $data = htmlspecialchars($_GET["data"]);
else
    $data = "html";

$mysqli = new mysqli ("localhost", "root", "ArthurX1901", "WeatherStation");

if ($mysqli->connect_errno) {

    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

}

if($what == "sensors") {
    include_once "ActiveSensors.php";
}
else if($what == "data") {
    include_once "SensorData.php";
}

?>