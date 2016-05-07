<?php

	ini_set('display_errors',1);

	error_reporting(E_ALL|E_STRICT);

    $Sensor = htmlspecialchars($_GET["sensor"]);

	$mysqli = new mysqli ( "localhost", "root", "ArthurX1901", "WeatherStation" );

	if ($mysqli->connect_errno) {

		echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

	}

	

	$res = $mysqli->prepare("SELECT VOLT_SOLAR, VOLT_BAT, CHARGE_BAT FROM " . $Sensor . " ORDER BY ID DESC LIMIT 1" );

	$res->execute();

	

	$res->bind_result($SolarVolt, $BatteryVolt, $BatteryCharge);

	

	$json_data['cols'][] = array(

		'id' => "A",

		'label' => "Solar",

		'type' => "number"

	);

    $json_data['cols'][] = array(

		'id' => "B",

		'label' => "Battery",

		'type' => "number"

	);

    $json_data['cols'][] = array(

		'id' => "C",

		'label' => "Charge",

		'type' => "number"

	);
	

	while ($res->fetch()) 

	{

		$json_data['rows'][]['c'] =  array(
            array(
    			'v' => $SolarVolt * 100 / 1.2,
    			'f' => $SolarVolt . 'V'
    		),
            array(
    			'v' => $BatteryVolt * 100 / 4.2,
    			'f' => $BatteryVolt . 'V'
    		),
            array(
    			'v' => $BatteryCharge,
    			'f' => $BatteryCharge . '%'
    		),
        );

	}

    echo json_encode($json_data);

?>