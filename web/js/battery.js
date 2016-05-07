function battery_draw_Chart(sensor) {
    var batteryoptions = {
        width: 120,
        height: 400,
		greenFrom: 25,
        greenTo: 100,
        redFrom: 0,
        redTo: 10,
        yellowFrom:10,
        yellowTo: 25,
        minorTicks: 5,
    };
	var batteryjsonData =  $.ajax({
		url: "/jquery/getBattery.php",
        type: "get",
        data: {
            sensor: sensor,
            part: sensor,
        },
	    dataType: "json",
		async: false
	}).responseText;
   	var batterydata = new google.visualization.DataTable(batteryjsonData);
    var batterychart = new google.visualization.Gauge(document.getElementById('battery_chart'));
    batterychart.draw(batterydata, batteryoptions);
    battery_drawn = 1;
}

setInterval(function() {
     battery_draw_Chart(sensor);
}, 60000);