google.charts.load('current', {packages: ['corechart', 'gauge', 'bar']});
var sensor = "Sensor2";
var part = "#overview";
var distime = "#day";
var parts = [];
$(document).ready(function() {
    $('nav .nav-tabs a').on('shown.bs.tab', function(event){
        sensor = $(event.target).text();
        $.get('/php/getSensorDatas.php?sensor=' + $(event.target).text(), function(data) {
            $('section#part').children().children().html(data);
            $('section#part .active').removeClass("active");
            $('section#part .nav-pills li:first').addClass("active");
            parts = [];
            $.each($('section#part .nav-pills li a'), function (i, val) {
                parts[i] = $(this).attr("href");
            });
            part = $('section#part .nav-pills li:first a').attr("href");
            update_content(part);
        });
    });
    $(document).on('shown.bs.tab', 'section#part .nav-pills a', function(event){
        part = $(event.target).attr("href");
        update_content(part);
    });
    $('section#time .nav-pills a').on('shown.bs.tab', function(event){
        distime = $(event.target).attr("href");
        update_content(part);
    });
    update_content(part);
    clock_draw();
});

function update_content(part){
    if(part != $('nav#menu .nav-pills li:first a').attr("href")) {
        if(part == "#hdc1000") {
            drawHDC1000();
        }
        else if(part == "#max17048") {
            drawMAX17048();
        }
        else if(part == "#solar") {
            drawSolar();
        }
        else if(part == "#tmp102") {
            drawTMP102();
        }
        else if(part == "#lps25h") {
            drawLPS25H();
        }
        else if(part == "#si1147") {
            drawSI1147();
        }
        else {
            drawOverview();
        }
        battery_draw_Chart(sensor);
    }
}

setInterval(function() {
     update_content(part);
}, 60000);

function jsonGetData(sensor, part, time, data) {
    var jsonData =  $.ajax({
		//url: "/jquery/getValues.php",
        url: "/php/getChartData.php",
        type: "get",
        data: {
            sensor: sensor,
            part: part,
            time: time,
            data: data,
        },
	    dataType: "json",
		async: false
	}).responseText;
    var chartdata = new google.visualization.DataTable(jsonData);
    return chartdata;
}

function drawChart(data, options, id) {
    var chart = new google.visualization.LineChart(document.getElementById(id));
	chart.draw(data, options);
}

function drawAreaChart(data, options, id) {
    var chart = new google.visualization.AreaChart(document.getElementById(id));
    chart.draw(data, options);
}

function drawBubbleChart(data, options, id) {
    var chart = new google.visualization.ColumnChart(document.getElementById(id));
    chart.draw(data, options);
}

function clearChart(id) {
    document.getElementById(id).innerHTML = '';
}

function generateChartOptions(title, height, width, time, grid) {
    var d = new Date();
    if(time == '#day') {
        WinViewMode = {
	    	viewWindowMode: 'explicit',
            min: new Date(d.getFullYear(), d.getMonth(), d.getDate(), 0, 0, 0),
    		max: new Date(d.getFullYear(), d.getMonth(), d.getDate(), 23, 59, 59),
	    };
    }
    else {
        WinViewMode = {
	    	viewWindowMode: 'maximized',
    	};
    }
    var Options = {
        width: width,
        height: height,
        title: title,
        //curveType: 'function',
        hAxis:{
			format: 'HH:mm',
			viewWindow: WinViewMode,
			gridlines: {count: grid}
		},
        legend: { position: 'bottom' }
    };
    return Options;
}

function drawHDC1000() {
    drawChart(
        jsonGetData(sensor, part, distime, 'temp'),
        generateChartOptions(
            "Temperature of HDC1000",
            250,
            450,
            distime,
            11
        ),
        "hdc1000_chart"
    );
    drawChart(
        jsonGetData(sensor, part, distime, 'humi'),
        generateChartOptions(
            "Humidity of HDC1000",
            250,
            450,
            distime,
            11
        ),
        "lps25h_chart"
    );
    clearChart("luminance_chart");
}

function drawMAX17048() {
    drawChart(
        jsonGetData(sensor, part, distime, 'volt'),
        generateChartOptions(
            "Voltage of Battery",
            250,
            450,
            distime,
            11
        ),
        "hdc1000_chart"
    );
    drawAreaChart(
        jsonGetData(sensor, part, distime, 'charge'),
        generateChartOptions(
            "Charge of Battery",
            250,
            450,
            distime,
            11
        ),
        "lps25h_chart"
    );
    var Options = {
        width: 450,
        height: 250,
        haxis: {
            viewWindowMode: 'pretty'
        },
        //explorer: { keepInBounds: true,
        //            maxZoomIn: 1,
        //            minZoomOut: 1,
        //},
        title: 'I do not Know',
        legend: { position: 'bottom' }
    };
    drawBubbleChart(
        jsonGetData(sensor, part, distime, 'rate'),
        Options,
        "luminance_chart"
    );
}

function drawSI1147() {
    drawChart(
        jsonGetData(sensor, part, distime, 'vis'),
        generateChartOptions(
            "Visible of light",
            250,
            450,
            distime,
            11
        ),
        "hdc1000_chart"
    );
    drawChart(
        jsonGetData(sensor, part, distime, 'ir'),
        generateChartOptions(
            "Infrared of light",
            250,
            450,
            distime,
            11
        ),
        "lps25h_chart"
    );
    drawChart(
        jsonGetData(sensor, part, distime, 'uv'),
        generateChartOptions(
            "UV-Index of light",
            250,
            450,
            distime,
            11
        ),
        "luminance_chart"
    );
}

function drawSolar() {
    drawChart(
        jsonGetData(sensor, part, distime, 'volt'),
        generateChartOptions(
            "Voltage of solar cell",
            250,
            450,
            distime,
            11
        ),
        "hdc1000_chart"
    );
    clearChart("lps25h_chart");
    clearChart("luminance_chart");
}

function drawTMP102() {
    drawChart(
        jsonGetData(sensor, part, distime, 'temp'),
        generateChartOptions(
            "Temperature of TMP102",
            250,
            450,
            distime,
            11
        ),
        "hdc1000_chart"
    );
    clearChart("lps25h_chart");
    clearChart("luminance_chart");
}

function drawLPS25H() {
    drawChart(
        jsonGetData(sensor, part, distime, 'press'),
        generateChartOptions(
            "Pressure of LPS25H",
            250,
            450,
            distime,
            11
        ),
        "hdc1000_chart"
    );
    drawChart(
        jsonGetData(sensor, part, distime, 'temp'),
        generateChartOptions(
            "Temperature of LPS25H",
            250,
            450,
            distime,
            11
        ),
        "lps25h_chart"
    );
    clearChart("luminance_chart");
}

function drawOverview() {
    if ($.inArray("#hdc1000", parts) != -1) {
        drawChart(
            jsonGetData(sensor, part, distime, 'temp'),
            generateChartOptions(
                "Temperature and humidity",
                250,
                450,
                distime,
                11
            ),
            "hdc1000_chart"
        );
    }
    if ($.inArray("#lps25h", parts) != -1) {
        drawChart(
            jsonGetData(sensor, part, distime, 'sealevpress'),
            generateChartOptions(
                "Sea level pressure",
                250,
                450,
                distime,
                11
            ),
            "lps25h_chart"
        );
    }
    else {
        clearChart("lps25h_chart");
    }
    if ($.inArray("#lps25h", parts) != -1) {
        drawChart(
            jsonGetData(sensor, part, distime, 'dewpoint'),
            generateChartOptions(
                "Dew point temperature",
                250,
                450,
                distime,
                11
            ),
            "luminance_chart"
        )
    }
    else {
        clearChart("luminance_chart");
    }
}