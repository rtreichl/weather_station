<?php
if ($Time == 'day')
    $res = $mysqli->prepare("SELECT RATE_BAT, COUNT(*) FROM " . $Sensor . " WHERE DATE=DATE(NOW()) AND `RATE_BAT` != 0 GROUP BY `RATE_BAT`");
else if ($Time == '24')
    $res = $mysqli->prepare("SELECT RATE_BAT, COUNT(*) FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) AND `RATE_BAT` != 0 GROUP BY `RATE_BAT`");
else
    $res = $mysqli->prepare("SELECT RATE_BAT, COUNT(*) FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) AND `RATE_BAT` != 0 GROUP BY `RATE_BAT`");

$res->execute();

$res->bind_result($Rate, $Count);

if($Time == 'day') {
    $Time = date("G");
}

$json_data['cols'][] = array(
    'id' => "",
    'label' => "Percentage per hour",
    'pattern' => "",
    'type' => "number"
);

$json_data['cols'][] = array(
    'id' => "",
    'label' => "Total Counts in " . $Time . "hr",
    'pattern' => "",
    'type' => "number"
);



while ($res->fetch()) {
    $json_data['rows'][]['c'] = array(
        array(
            'v' => $Rate,
            'f' => $Rate . '%/hr'
        ),
        array(
            'v' => $Count,
            'f' => $Count,
        ),
    );

}
echo json_encode($json_data, JSON_HEX_QUOT);
?>