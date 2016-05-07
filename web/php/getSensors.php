<?php

    ini_set('display_errors',1);

	error_reporting(E_ALL|E_STRICT);

	$mysqli = new mysqli ( "localhost", "root", "ArthurX1901", "WeatherStation" );

	if ($mysqli->connect_errno) {

		echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

	}



	$res = $mysqli->prepare( "SELECT NAME, ADDRESS, SOLAR, MAX17048, HDC1000, TMP102, LPS25H, DS18B20, SI1147 FROM SensorsActive ORDER BY NAME");

	$res->execute();
	$res->bind_result($Name, $Address, $Solar, $Max17048, $Hdc1000, $Tmp102, $Lps25h, $Ds18b20, $Si1147);
    echo '<li class="active"><a href="#home" data-toggle="tab">Home</a></li>';
	while ($res->fetch()) {
        echo '<li data-toogle="tab" class="dropdown">';
        echo '<a class="dropdown-toggle" data-toggle="dropdown" href="#Sensor' . $Address . '">' . $Name;
        echo '<span class="caret"></span></a>';
        echo '<ul class="dropdown-menu">';
        if($Solar) {
            echo '<li><a href="#solar-' . $Address . '" data-toggle="tab">Solar</a></li>';
            //echo '<li><a href="#3" data-toggle="tab">Temperature 1</a></li>';
        }
        if($Max17048) {
            echo '<li><a href="#max17048-' . $Address . '" data-toggle="tab">Battery</a></li>';
            //echo '<li><a href="#4" data-toggle="tab">Temperature 2</a></li>';
        }
        if($Hdc1000) {
            echo '<li><a href="#hdc1000-' . $Address . '" data-toggle="tab">Temperature and Humidity</a></li>';
            //echo '<li><a href="#5" data-toggle="tab">Temperature 3</a></li>';
        }
        if($Tmp102) {
            echo '<li><a href="#tmp102-' . $Address . '" data-toggle="tab">Temperature</a></li>';
            //echo '<li><a href="#6" data-toggle="tab">Temperature 4</a></li>';
        }
        if($Lps25h) {
            echo '<li><a href="#lps25h-' . $Address . '" data-toggle="tab">Pressure</a></li>';
            //echo '<li><a href="#7" data-toggle="tab">Temperature 5</a></li>';
        }
        if($Ds18b20) {
            echo '<li><a href="#ds18b20-' . $Address . '" data-toggle="tab"></a>Soil Temperature</li>';
            //echo '<li><a href="#8" data-toggle="tab">Temperature 6</a></li>';
        }
        if($Si1147) {
            echo '<li><a href="#si1147-' . $Address . '" data-toggle="tab">Luminance</a></li>';
            //echo '<li><a href="#9" data-toggle="tab">Temperature 7</a></li>';
        }
        echo '</ul>';
        echo '</li>';
	}

?>