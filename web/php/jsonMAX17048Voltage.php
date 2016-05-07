<?php
if ($Time == 'day')
    $res = $mysqli->prepare("SELECT DATETIME, VOLT_BAT FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC");
else if ($Time == '24')
    $res = $mysqli->prepare("SELECT DATETIME, VOLT_BAT FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC");
else
    $res = $mysqli->prepare("SELECT DATETIME, VOLT_BAT FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC");

$res->execute();

$res->bind_result($DateTime, $Voltage);

$json_data['cols'][] = array(
    'id' => "",
    'label' => "DateTime",
    'pattern' => "",
    'type' => "datetime"
);

$json_data['cols'][] = array(
    'id' => "",
    'label' => "Voltage",
    'pattern' => "",
    'type' => "number"
);
$len = 0;
$mean = $Voltage;
while ($res->fetch()) {
    $mean = ($mean * $len + $Voltage) / ($len + 1);
    if ($len < 25) {
        $len++;
    }
    $json_data['rows'][]['c'] = array(
        array(
            'v' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime)) - 1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
            'f' => date("H:i", strtotime($DateTime)),
        ),
        array(
            'v' => round($mean, 2),
            'f' => round($mean, 2) . 'V'),
    );

}
echo json_encode($json_data, JSON_HEX_QUOT);
?>