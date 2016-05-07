<?php
    if($Time == 'day')
        $res = $mysqli->prepare( "SELECT DATETIME, LPS25H_TEMP ,LPS25H_PRESS, HDC1000_HUMI FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC" );
    else if ($Time == '24')
        $res = $mysqli->prepare( "SELECT DATETIME, LPS25H_TEMP, LPS25H_PRESS, HDC1000_HUMI FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC" );
    else
        $res = $mysqli->prepare( "SELECT DATETIME, LPS25H_TEMP, LPS25H_PRESS, HDC1000_HUMI FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC" );

	$res->execute();

	$res->bind_result($DateTime, $Temp, $Press, $Humi);

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

	$R = 8314.3;
	$mw = 18.016;

	while ($res->fetch())
	{
		if($Temp >= 0) {
			$a = 7.5;
			$b = 237.3;
		}
		else {
			$a = 7.6;
			$b = 240.7;
		}
		$SDD = 6.1078 * pow(10, ($a*$Temp) / ($b-$Temp));
		$DD = $Humi / 100 * $SDD;
		$v = log10($DD/6.1078);
		$DewPoint = $b*$v/($a-$v);
		$AF = pow(10,5) * $mw / $R *$DD / ($Temp + 273.15);
		$DewPoint = round($DewPoint, 2);
		$json_data['rows'][]['c'] =  array(
        	array(
                'v' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime))-1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
			    'f' => date("H:i", strtotime($DateTime)),
            ),
			array(
			'v' => $DewPoint,
			'f' => $DewPoint . '&deg;C'),
		);

	}
    echo json_encode($json_data, JSON_HEX_QUOT);
?>