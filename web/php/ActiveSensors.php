<?php
/**
 * Created by PhpStorm.
 * User: Richard Treichl
 * Date: 05.05.2016
 * Time: 12:30
 */

$res = $mysqli->prepare("SELECT ADDRESS, NAME FROM SensorsActive ORDER BY NAME");

$res->execute();

echo '<li data="home">Home</li>';

$res->bind_result($Address, $Name);
while ($res->fetch()) {
    echo '<li data="Sensor ' . $Address . '">' . $Name . '</li>';
}

?>