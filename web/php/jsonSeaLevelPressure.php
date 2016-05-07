<?php
ini_set('display_errors', 1);

error_reporting(E_ALL | E_STRICT);
$Sensor = "Sensor3";
$Time = "now";

$mysqli = new mysqli ("localhost", "root", "ArthurX1901", "WeatherStation");

if ($mysqli->connect_errno) {

    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

}


if ($Time == 'now') {
    $res = $mysqli->prepare("SELECT DATETIME, LPS25H_TEMP, LPS25H_PRESS FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC LIMIT 1");
} else if ($Time == 'day') {
    $res = $mysqli->prepare("SELECT DATETIME, LPS25H_TEMP, LPS25H_PRESS FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC");
} else if ($Time == '24') {
    $res = $mysqli->prepare("SELECT DATETIME, LPS25H_TEMP, LPS25H_PRESS FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC");
} else {
    $res = $mysqli->prepare("SELECT DATETIME, LPS25H_TEMP, LPS25H_PRESS FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC");
}
$res->execute();

$res->bind_result($DateTime, $Temp, $Press);

if ($Time != 'now') {

    $json_data['cols'][] = array(
        'id' => "",
        'label' => "DateTime",
        'pattern' => "",
        'type' => "datetime"
    );

    $json_data['cols'][] = array(
        'id' => "",
        'label' => "Sea level Pressure",
        'pattern' => "",
        'type' => "number"
    );
}
while ($res->fetch()) {
    $Temp += 275.15;
    $scale = $Temp / ($Temp + 0.0065 * 477);
    //$scale = (1 - 0.0065 * -470 / $Temp);
    $SeaLevelPress = $Press * pow($scale, -5.255);
    $SeaLevelPress = round($SeaLevelPress, 2);
    if ($Time != 'now') {
        $json_data['rows'][]['c'] = array(
            array(
                'v' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime)) - 1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
                'f' => date("H:i", strtotime($DateTime)),
            ),
            array(
                'v' => $SeaLevelPress,
                'f' => $SeaLevelPress . 'hPa'),
        );
    } else {
        $json_data[] =
            array(
                'text' => 'Pressure',
                'value' => $SeaLevelPress,// * 100 / 1.2,
                'min' => 990,
                'max' => 1040,
                'vtext' => $SeaLevelPress . 'hPa',
            );
    }
}
echo json_encode($json_data, JSON_HEX_QUOT);
?>