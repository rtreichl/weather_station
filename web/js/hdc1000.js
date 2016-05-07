function hdc1000_draw_Chart(sensor, distime) {
    var d = new Date();
    var grid = "11";
    if(distime == '#day') {
        WinMode = {
	    	viewWindowMode: 'explicit',
            min: new Date(d.getFullYear(), d.getMonth(), d.getDate(), 0, 0, 0),
    		max: new Date(d.getFullYear(), d.getMonth(), d.getDate(), 23, 59, 59),
	    };
    }
    else {
        WinMode = {
	    	viewWindowMode: 'maximized',
    	};
    }
    var hdc1000options = {
        width: 450,
        height: 250,
        title: 'Temperature and Humidity of today',
        curveType: 'function',		hAxis:{
			format: 'HH:mm',
			viewWindow: WinMode,
			gridlines: {count: grid}
		},
        legend: { position: 'bottom' }
    };
	var hdc1000jsonData =  $.ajax({
		//url: "/jquery/getValues.php",
        url: "/php/getChartData.php",
        type: "get",
        data: {
            sensor: sensor,
            part: part,
            time: distime
        },
	    dataType: "json",
		async: false
	}).responseText;
   	var hdc1000data = new google.visualization.DataTable(hdc1000jsonData);
    var hdc1000chart = new google.visualization.LineChart(document.getElementById('hdc1000_chart'));
	hdc1000chart.draw(hdc1000data, hdc1000options);
}

setInterval(function() {
     hdc1000_draw_Chart(sensor, distime);
}, 60000);