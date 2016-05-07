<?php

	//phpinfo();

	ini_set('display_errors',1);

	error_reporting(E_ALL|E_STRICT);

	$mysqli = new mysqli ( "localhost", "root", "ArthurX1901", "WeatherStation" );

	//echo $mysqli->get_client_info();

	if ($mysqli->connect_errno) {

		echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

	}

	

	$res = $mysqli->prepare( "SELECT TIME, SI1147_VIS, SI1147_IR FROM Sensor3 WHERE DATE=DATE(NOW()) ORDER BY ID ASC" );

	$res->execute();

	

	$res->bind_result($DateTime, $LightVis, $LightIr);

	

	$json_data['cols'][] = array(

		'id' => "",

		'label' => "DateTime",

		'pattern' =>"",

		'type' => "timeofday"

	);

	

	$json_data['cols'][] = array(

		'id' => "",

		'label' => "Visible",

		'pattern' =>"",

		'type' => "number"

	);

	

	$json_data['cols'][] = array(

		'id' => "",

		'label' => "Infrared",

		'pattern' =>"",

		'type' => "number"

	);

	

	while ($res->fetch()) 

	{

		$json_data['rows'][]['c'] =  array(

			array(

			'v' => array(

				date('H', strtotime($DateTime)),

				date('i', strtotime($DateTime)),

				date('s', strtotime($DateTime))

			),

			'f' => $DateTime),

			array(

			'v' => $LightVis - $LightIr,

			'f' => $LightVis - $LightIr . 'lux'),

			array(

			'v' => $LightIr,

			'f' => $LightIr . 'lux'),

		);

	}

    echo json_encode($json_data, JSON_HEX_QUOT);

?>