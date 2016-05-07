<?php

include("functions.php");

$mysqli = new mysqli ("localhost", "root", "ArthurX1901", "WeatherStation");

if ($mysqli->connect_errno) {

    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

}

if(isset($_GET["sensor"]))
    $Sensor = htmlspecialchars($_GET["sensor"]);
else
    $Sensor = "Sensor3";
if(isset($_GET["part"]))
    $Part = htmlspecialchars($_GET["part"]);
else
    $Part = "hdc1000";
if(isset($_GET["sensor"]))
    $Time = htmlspecialchars($_GET["time"]);
else
    $Time = "day";

if($Sensor == "home") {
    $Sensor = "Sensor2";
}

$res = $mysqli->prepare("SELECT HDC1000_TEMP, TMP102_TEMP, HDC1000_HUMI FROM " . $Sensor . " ORDER BY ID DESC LIMIT 1" );
$res->execute();

$res->bind_result($Temp1, $Temp2, $Humi);
while ($res->fetch()) {
    $Temp = round(($Temp2 + $Temp1) / 2, 2);
    $DewPoint = calcDewPointTemperature($Temp, $Humi);
    $FrostPoint = calcFrostPointTemperature($Temp, $Humi);
    $json_data[] =
        array(
            'text' => 'Temperature',
            'value' => $Temp,// * 100 / 4.25,
            'min' => -40,
            'max' => 120,
            'vtext' => $Temp . '°C',
        );
    $json_data[] =
        array(
            'text' => 'Humidity',
            'value' => $Humi,// * 100 / 1.2,
            'min' => 0,
            'max' => 100,
            'vtext' => $Humi . '%',
        );
    $json_data[] =
        array(
            'text' => 'Dew Point',
            'value' => $DewPoint,// * 100 / 4.25,
            'min' => -40,
            'max' => 120,
            'vtext' => $DewPoint . '°C',
        );
    $json_data[] =
        array(
            'text' => 'Frost Point',
            'value' => $FrostPoint,// * 100 / 1.2,
            'min' => 0,
            'max' => 100,
            'vtext' => $FrostPoint . '°C',
        );
}
echo json_encode($json_data, JSON_NUMERIC_CHECK);
?>