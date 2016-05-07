<?php

	//phpinfo();

    $Sensor = htmlspecialchars($_GET["sensor"]);
    $Part = htmlspecialchars($_GET["part"]);
    $Part = substr($Part, 1);
    $Time = htmlspecialchars($_GET["time"]);
    $Time = substr($Time, 1);

	ini_set('display_errors',1);

	error_reporting(E_ALL|E_STRICT);

	if(isset($_GET['data']))

	$data = htmlspecialchars($_GET['data']);

	$data = 'temp';

	$mysqli = new mysqli ( "localhost", "root", "ArthurX1901", "WeatherStation" );

	//echo $mysqli->get_client_info();

	if ($mysqli->connect_errno) {

		echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

	}

    if($Part == "hdc1000") {
        $Select = " HDC1000_TEMP, HDC1000_HUMI ";
    }
    else if($Part == "tmp102") {
        $Select = " TMP102_TEMP ";
    }
    else if($Part == "lps25h") {
        $Select = " LPS25H_PRESS "
    }

    if($Time == 'day')
		$res = $mysqli->prepare( "SELECT DATETIME, HDC1000_TEMP, HDC1000_HUMI FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC" );
    else if ($Time == '24')
        $res = $mysqli->prepare( "SELECT DATETIME, HDC1000_TEMP, HDC1000_HUMI FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC" );
    else
        $res = $mysqli->prepare( "SELECT DATETIME, HDC1000_TEMP, HDC1000_HUMI FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC" );

	//$res = $mysqli->prepare( "SELECT TIME, HDC1000_TEMP, HDC1000_HUMI FROM Sensor11 WHERE DATE=DATE(NOW()) ORDER BY ID ASC" );

	$res->execute();

	//echo "Affected Rows: " . $res->affected_rows() . "<br/>";

	

	$res->bind_result($DateTime, $Temp, $Humi);

    $json_data['cols'][] = array(

		'id' => "",

		'label' => "DateTime",

		'pattern' =>"",

		'type' => "datetime"
	);

	$json_data['cols'][] = array(

		'id' => "",

		'label' => "Temperature",

		'pattern' =>"",

		'type' => "number"

	);

	

	$json_data['cols'][] = array(

		'id' => "",

		'label' => "Humidity",

		'pattern' =>"",

		'type' => "number"

	);

	

	while ($res->fetch())

	{

		//echo date('H', strtotime($DateTime));

		//echo date('m', strtotime($DateTime));

		//echo date('s', strtotime($DateTime));

		$json_data['rows'][]['c'] =  array(

			array(

            'v' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime))-1) . date(", d, H, i, s", strtotime($DateTime)) . ')',

			'f' => date("H:i", strtotime($DateTime))

            ),

			array(

			'v' => $Temp,

			'f' => $Temp . '°'),

			array(

			'v' => $Humi,

			'f' => $Humi . '%'),

		);

	}

	

    //$result = mysqli_query($db, "Select * FROM 'Sensor11' WHERE DATE =  DATE(NOW()");

    //$row = mysqli_affected_rows($db);

    echo json_encode($json_data, JSON_HEX_QUOT);

?>