<?php
 	if($Time == 'now') {
		$res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC LIMIT 1");
	}
    else if($Time == 'day') {
		$res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC");
	}
    else if ($Time == '24') {
		$res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC");
	}
    else {
		$res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC");
	}
	$res->execute();

	$res->bind_result($DateTime, $Temp1, $Temp2);

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

	while ($res->fetch())
	{
		$Temp = $Temp1 + $Temp2;
		$Temp = $Temp / 2;
		$Temp = round($Temp, 2);
		$json_data['rows'][]['c'] =  array(
        	array(
                'v' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime))-1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
			    'f' => date("H:i", strtotime($DateTime)),
            ),
			array(
			'v' => $Temp,
			'f' => $Temp . 'hPa'),
		);

	}
    echo json_encode($json_data, JSON_HEX_QUOT);
?>