<?php
    if(isset($_GET["data"])) {
        $data = htmlspecialchars($_GET["data"]);
    }
    else {
        $data = "vis";
    }

    if($data == "ir") {
        include_once("jsonSI1147Ir.php");
    }
    else if($data == "uv") {
        include_once("jsonSI1147Uv.php");
    }
    else if($data == "vis") {
        include_once("jsonSI1147Visible.php");
    }
?>