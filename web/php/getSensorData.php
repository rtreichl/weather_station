<?php

    ini_set('display_errors',1);

	error_reporting(E_ALL|E_STRICT);

	$mysqli = new mysqli ( "localhost", "root", "ArthurX1901", "WeatherStation" );

	if ($mysqli->connect_errno) {

		echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

	}



	$res = $mysqli->prepare( "SELECT ADDRESS, NAME FROM SensorsActive ORDER BY NAME" );

	$res->execute();

    echo '<li class="active"><a href="#home" data-toggle="tab">Home</a></li>';

	$res->bind_result($Address, $Name);
	while ($res->fetch()) {
        echo '<li><a href="#Sensor' . $Address . '" data-toggle="tab">' . $Name . '</a></li>';
	}

?>