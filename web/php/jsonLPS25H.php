<?php
    if(isset($_GET["data"])) {
        $data = htmlspecialchars($_GET["data"]);
    }
    else {
        $data = "press";
    }

    if($data == "press") {
        include_once("jsonLPS25HPressure.php");
    }
    else if($data == "temp") {
        include_once("jsonLPS25HTemperature.php");
    }
    else if($data == "dew") {
        include_once("jsonDewpoint.php");
    }
    else if($data == "seapress") {
        include_once("jsonSeaLevelPressure.php");
    }
?>