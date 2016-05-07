function lps25h_draw_Chart() {
    var lps25hoptions = {
        width: 450,
        height: 250,
        title: 'Pressure of today',
        curveType: 'function',
		hAxis:{
			format: 'HH:mm',
			viewWindow: {
				viewWindowMode:'explicit',
				min: [0, 0],
				max: [23, 59],
			},
			gridlines: {count: 23}
		},
        legend: { position: 'bottom' }
    };
	var lps25hjsonData =  $.ajax({
		url: "/jquery/getPress.php",
        type: "get",
        data: {
            sensor: $('.nav-tabs .active').text()
        },
	    dataType: "json",
		async: false
	}).responseText;
   	var lps25hdata = new google.visualization.DataTable(lps25hjsonData);
    var lps25hchart = new google.visualization.LineChart(document.getElementById('lps25h_chart'));
	lps25hchart.draw(lps25hdata, lps25hoptions);
}

setInterval(function() {
     lps25h_draw_Chart();
}, 60000);

$(document).ready(function() {
$(".nav-tabs li").click(function() {
    setTimeout(function() {
    lps25h_draw_Chart();
    }, 20);
});
});