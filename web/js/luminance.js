function luminance_draw_Chart() {
    var luminanceoptions = {
        width: 450,
        height: 250,
        title: 'Luminance of today',
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
	var luminancejsonData =  $.ajax({
		url: "/jquery/getLuminance.php",
        type: "get",
        data: {
            sensor: $('.nav-tabs .active').text()
        },
	    dataType: "json",
		async: false
	}).responseText;
   	var luminancedata = new google.visualization.DataTable(luminancejsonData);
    var luminancechart = new google.visualization.LineChart(document.getElementById('luminance_chart'));
	luminancechart.draw(luminancedata, luminanceoptions);
}

setInterval(function() {
     luminance_draw_Chart();
}, 60000);

$(document).ready(function() {
$(".nav-tabs li").click(function() {
    setTimeout(function() {
    luminance_draw_Chart();
    }, 20);
});
});