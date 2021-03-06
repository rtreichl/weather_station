<?php

ini_set('display_errors', 1);

error_reporting(E_ALL | E_STRICT);

if (isset($_GET["sensor"]))
    $Sensor = htmlspecialchars($_GET["sensor"]);
else
    $Sensor = "Sensor2";

$mysqli = new mysqli ("localhost", "root", "ArthurX1901", "WeatherStation");

if ($mysqli->connect_errno) {

    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

}

if($Sensor == 'Home'){
    
}

$res = $mysqli->prepare("SELECT NAME, ADDRESS, SOLAR, MAX17048, HDC1000, TMP102, LPS25H, DS18B20, SI1147 FROM SensorsActive WHERE NAME = '" . $Sensor . "'");
//$res = $mysqli->prepare( "SELECT ADDRESS, NAME FROM SensorsActive ORDER BY NAME" );

$res->execute();



$res->execute();
$res->bind_result($Name, $Address, $Solar, $Max17048, $Hdc1000, $Tmp102, $Lps25h, $Ds18b20, $Si1147);
while ($res->fetch()) {
    if ($Solar) {
        echo '<li data="solar">Solar</li>';
        //echo '<li><a href="#3" data-toggle="tab">Temperature 1</a></li>';
    }
    if ($Max17048) {
        echo '<li data="max17048">Battery</li>';
        //echo '<li><a href="#4" data-toggle="tab">Temperature 2</a></li>';
    }
    if ($Hdc1000) {
        echo '<li data="hdc1000">Temperature and Humidity</li>';
        //echo '<li><a href="#5" data-toggle="tab">Temperature 3</a></li>';
    }
    if ($Tmp102) {
        echo '<li data="tmp102">Temperature</li>';
        //echo '<li><a href="#6" data-toggle="tab">Temperature 4</a></li>';
    }
    if ($Lps25h) {
        echo '<li data="lps25h">Pressure</li>';
        //echo '<li><a href="#7" data-toggle="tab">Temperature 5</a></li>';
    }
    if ($Ds18b20) {
        echo '<li data="ds18b20">Soil Temperature</li>';
        //echo '<li><a href="#8" data-toggle="tab">Temperature 6</a></li>';
    }
    if ($Si1147) {
        echo '<li data="si1147">Luminance</li>';
        //echo '<li><a href="#9" data-toggle="tab">Temperature 7</a></li>';
    }
    echo '</ul>';
    //echo '</li>';
}

?>