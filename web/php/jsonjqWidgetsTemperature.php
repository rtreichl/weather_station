<?php

ini_set('display_errors', 1);

error_reporting(E_ALL | E_STRICT);

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

if($Sensor == 'Home') {
    if($Part == 'solar') {
        $res2 = $mysqli->prepare("SELECT NAME FROM SensorsActive WHERE SOLAR");
    }
    elseif($Part == 'battery') {
        $res2 = $mysqli->prepare("SELECT NAME FROM SensorsActive WHERE MAX17048");
    }
    elseif($Part == 'press') {
        $res2 = $mysqli->prepare("SELECT NAME FROM SensorsActive WHERE LPS25H");
    }
    else {
        $res2 = $mysqli->prepare("SELECT NAME FROM SensorsActive WHERE HDC1000 AND TMP102");
    }
    $res2->execute();
    $res2->bind_result($Name);
    while ($res2->fetch()) {
        $Sensors[] = $Name;
    }
}
else{
    $Sensors[] = $Sensor;
}

foreach ($Sensors as $Sensor) {

    if($Part == 'solar') {
        if ($Time == 'now') {
            $res = $mysqli->prepare("SELECT DATETIME, VOLT_SOLAR FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC LIMIT 1");
        } else if ($Time == 'day') {
            $res = $mysqli->prepare("SELECT DATETIME, VOLT_SOLAR FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC");
        } else if ($Time == '24') {
            $res = $mysqli->prepare("SELECT DATETIME, VOLT_SOLAR FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC");
        } else {
            $res = $mysqli->prepare("SELECT DATETIME, VOLT_SOLAR FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC");
        }
        $res->execute();

        $res->bind_result($DateTime, $Solar);

        while ($res->fetch()) {
            $json_data[] =
                array(
                    //'Captured' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime)) - 1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
                    'Time' => strtotime($DateTime) * 1000,
                    $Sensor => $Solar,
                    //'Temperature5' => $Temp+8,
                );

        }
    }
    elseif($Part == 'battery') {
        if ($Time == 'now') {
            $res = $mysqli->prepare("SELECT DATETIME, CHARGE_BAT FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC LIMIT 1");
        } else if ($Time == 'day') {
            $res = $mysqli->prepare("SELECT DATETIME, CHARGE_BAT FROM " . $Sensor . " WHERE DATE=DATE(NOW()) ORDER BY ID ASC");
        } else if ($Time == '24') {
            $res = $mysqli->prepare("SELECT DATETIME, CHARGE_BAT FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '1' DAY) ORDER BY ID ASC");
        } else {
            $res = $mysqli->prepare("SELECT DATETIME, CHARGE_BAT FROM " . $Sensor . " WHERE DATETIME > DATE_SUB(NOW(), INTERVAL '" . $Time . "' HOUR) ORDER BY ID ASC");
        }
        $res->execute();

        $res->bind_result($DateTime, $Battery);

        while ($res->fetch()) {
            $json_data[] =
                array(
                    //'Captured' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime)) - 1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
                    'Time' => strtotime($DateTime) * 1000,
                    $Sensor => $Battery,
                    //'Temperature5' => $Temp+8,
                );

        }
    }
    elseif($Part == 'press') {
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

        while ($res->fetch()) {
            $Temp += 275.15;
            $scale = $Temp / ($Temp + 0.0065 * 477);
            //$scale = (1 - 0.0065 * -470 / $Temp);
            $SeaLevelPress = $Press * pow($scale, -5.255);
            $SeaLevelPress = round($SeaLevelPress, 2);
            $json_data[] =
                array(
                    //'Captured' => 'Date(' . date("Y, ", strtotime($DateTime)) . (date("n", strtotime($DateTime)) - 1) . date(", d, H, i, s", strtotime($DateTime)) . ')',
                    'Time' => strtotime($DateTime) * 1000,
                    $Sensor => $SeaLevelPress,
                    //'Temperature5' => $Temp+8,
                );

        }
    }
    else {
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
                    'Time' => strtotime($DateTime) * 1000,
                    $Sensor => $Temp,
                    //'Temperature5' => $Temp+8,
                );

        }
    }
}
echo json_encode($json_data, JSON_NUMERIC_CHECK);
?>