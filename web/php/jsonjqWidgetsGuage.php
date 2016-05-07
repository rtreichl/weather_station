<?php
$mysqli = new mysqli ("localhost", "root", "ArthurX1901", "WeatherStation");

if ($mysqli->connect_errno) {

    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

}

if(isset($_GET["sensor"]))
    $Sensor = htmlspecialchars($_GET["sensor"]);
else
    $Sensor = "Sensor2";
if(isset($_GET["part"]))
    $Part = htmlspecialchars($_GET["part"]);
else
    $Part = "#hdc1000";
if(isset($_GET["sensor"]))
    $Time = htmlspecialchars($_GET["time"]);
else
    $Time = "day";

if($Sensor == "home") {
    $Sensor = "Sensor2";
}

$res = $mysqli->prepare("SELECT VOLT_SOLAR, VOLT_BAT, CHARGE_BAT FROM " . $Sensor . " ORDER BY ID DESC LIMIT 1" );
$res->execute();

$res->bind_result($Solar, $Battery, $Charge);

while ($res->fetch()) {
    $json_data[] =
        array(
            'text' => 'Battery',
            'value' => $Battery,// * 100 / 4.25,
            'max' => 4.25,
            'vtext' => $Battery . 'V',
        );
    $json_data[] =
        array(
            'text' => 'Solar',
            'value' => $Solar,// * 100 / 1.2,
            'max' => 1.2,
            'vtext' => $Solar . 'V',
        );
    $json_data[] =
        array(
            'text' => 'Charge',
            'value' => $Charge,
            'max' => 100,
            'vtext' => $Charge . '%',
        );
}
echo json_encode($json_data, JSON_NUMERIC_CHECK);
?>