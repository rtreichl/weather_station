<?php

	//phpinfo();

	ini_set('display_errors',1);

	error_reporting(E_ALL|E_STRICT);

	$mysqli = new mysqli ( "localhost", "root", "ArthurX1901", "WeatherStation" );

	//echo $mysqli->get_client_info();

	if ($mysqli->connect_errno) {

		echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

	}



	$res = $mysqli->prepare( "SELECT TIME, LPS25H_PRESS FROM Sensor3 WHERE DATE=DATE(NOW()) ORDER BY ID ASC" );

	$res->execute();

	$res->bind_result($DateTime, $Press);

	$json_data['cols'][] = array(
		'id' => "",
		'label' => "DateTime",
		'pattern' =>"",
		'type' => "datetime"
	);

	$json_data['cols'][] = array(
		'id' => "",
		'label' => "Pressure",
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
			'v' => $Press,
			'f' => $Press . 'hPa'),
		);

	}

    echo json_encode($json_data, JSON_HEX_QUOT);

?>