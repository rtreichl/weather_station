<?php

   	ini_set('display_errors',1);

	error_reporting(E_ALL|E_STRICT);

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
        $Time = "#day";

    $Part = substr($Part, 1);
    $Time = substr($Time, 1);

	$mysqli = new mysqli ( "localhost", "root", "ArthurX1901", "WeatherStation" );

	if ($mysqli->connect_errno) {

		echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

	}

    if($Part == "hdc1000") {
        include_once "jsonHDC1000.php";
    }
    else if($Part == "tmp102") {
        include_once "jsonTMP102.php";
    }
    else if($Part == "lps25h") {
        include_once "jsonLPS25H.php";
    }
    else if($Part == "solar") {
        include_once "jsonSolar.php";
    }
    else if($Part == "max17048") {
        include_once "jsonMAX17048.php";
    }
    else if($Part == "si1147") {
        include_once "jsonSI1147.php";
    }
    else if($Part == "over") {
        include_once "jsonOverview.php";
    }
?>