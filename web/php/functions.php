<?php
/**
 * Created by PhpStorm.
 * User: Richard Treichl
 * Date: 25.04.2016
 * Time: 23:24
 */

function calcSeaLevelPressure($Pressure, $Temp)
{
    $Temp += 275.15;
    $scale = $Temp / ($Temp + 0.0065 * 477);
    //$scale = (1 - 0.0065 * -470 / $Temp);
    $SeaLevelPress =  $Pressure * pow($scale, -5.255);
    $SeaLevelPress = round($SeaLevelPress, 2);
    return $SeaLevelPress;
}

function calcDewPointTemperature($Temp, $Humi)
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
    return $DewPoint;
}

function calcFrostPointTemperature($Temp, $Humi)
{
    $a = 9.5;
    $b = 265.5;
    $SDD = 6.1078 * pow(10, ($a*$Temp) / ($b-$Temp));
    $DD = $Humi / 100 * $SDD;
    $v = log10($DD/6.1078);
    $DewPoint = $b*$v/($a-$v);
    $AF = pow(10,5) * $mw / $R *$DD / ($Temp + 273.15);
    $DewPoint = round($DewPoint, 2);
    return $DewPoint;
}

?>