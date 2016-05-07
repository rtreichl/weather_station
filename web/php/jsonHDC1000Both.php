<?php
    if($Time == 'day')
        $res = $mysqli->prepare( "SELECT DATETIME, HDC1000_TEMP, HDC1000_HUMI FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC" );
    else if ($Time == '24')
        $res = $mysqli->prepare( "SELECT DATETIME, HDC1000_TEMP, HDC1000_HUMI FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC" );
    else
        $res = $mysqli->prepare( "SELECT DATETIME, HDC1000_TEMP, HDC1000_HUMI FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC" );

    $res->execute();

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
		$json_data['rows'][]['c'] =  array(
			array(
            'v' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime))-1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
			'f' => date("H:i", strtotime($DateTime)),
            ),
			array(
			'v' => $Temp,
			'f' => $Temp . '&deg;'),
			array(
			'v' => $Humi,
			'f' => $Humi . '%'),
		);
	}
    echo json_encode($json_data, JSON_HEX_QUOT);
?>