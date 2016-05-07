<?php
    if(isset($_GET["data"])) {
        $data = htmlspecialchars($_GET["data"]);
    }
    else {
        $data = "volt";
    }

    if($data == "volt") {
        include_once("jsonMAX17048Voltage.php");
    }
    else if($data == "charge") {
        include_once("jsonMAX17048Charge.php");
    }
    else if($data == "rate") {
        include_once("jsonMAX17048ChargeRate.php");
    }
?>