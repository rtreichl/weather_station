<?php
$mysqli = new mysqli ("localhost", "root", "ArthurX1901", "WeatherStation");

if ($mysqli->connect_errno) {

    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;

}

if(isset($_GET["sensor"]))
    $Sensor = htmlspecialchars($_GET["sensor"]);
else
    $Sensor = "Sensor2";
if(isset($_GET["part"]))
    $Part = htmlspecialchars($_GET["part"]);
else
    $Part = "#hdc1000";
if(isset($_GET["sensor"]))
    $Time = htmlspecialchars($_GET["time"]);
else
    $Time = "day";
if(isset($_GET["_"]))
    $Timestamp = htmlspecialchars($_GET["_"]);
else
    $Timestamp = 0;

if ($Time == 'now') {
    $res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC LIMIT 1");
} else if ($Time == 'day') {
    $res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC");
} else if ($Time == '24') {
    $res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC");
} else {
    $res = $mysqli->prepare("SELECT DATETIME, HDC1000_TEMP, TMP102_TEMP FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC");
}
$res->execute();

$res->bind_result($DateTime, $Temp1, $Temp2);

while ($res->fetch()) {
    $Temp = $Temp1 + $Temp2;
    $Temp = $Temp / 2;
    $Temp = round($Temp, 2);
    $json_data[] =
        array(
            //'Captured' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime)) - 1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
            'Captured' => strtotime($DateTime) * 1000,
            'Temperature' => $Temp,
            'Temperature2' => $Temp1
        );

}
echo json_encode($json_data, JSON_NUMERIC_CHECK);
?>