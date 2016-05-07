<?php
    if(isset($_GET["data"])) {
        $data = htmlspecialchars($_GET["data"]);
    }
    else {
        $data = "both";
    }

    if($data == "humi") {
        include_once("jsonHDC1000Humidity.php");
    }
    else if($data == "temp") {
        include_once("jsonHDC1000Temperature.php");
    }
    else if($data == "both") {
        include_once("jsonHDC1000Both.php");
    }
?>