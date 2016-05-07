<?php
if(isset($_GET["data"])) {
    $data = htmlspecialchars($_GET["data"]);
}
else {
    $data = "all";
}

if($data == "dewpoint") {
    include_once("jsonDewpoint.php");
}
else if($data == "sealevpress") {
    include_once("jsonSeaLevelPressure.php");
}
else if($data == "temp") {
    include_once("jsonHDC1000Both.php");
}
?>