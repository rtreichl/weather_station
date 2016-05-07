/**
 * Created by Richard Treichl on 25.04.2016.
 */
function createGraph()
{
    var sourceGraph =
    {
        datatype: "json",
        datafields: [
            {name: 'Time', type: 'date', format: "HH:mm"},
            {name: 'Sensor2', type: 'float'},
            {name: 'Sensor3', type: 'float'},
            {name: 'Sensor8', type: 'float'},
            {name: 'Sensor0', type: 'float'},
            {name: 'Sensor1', type: 'float'}
        ],
        data: createSeverData(24),
        url: 'php/jsonjqWidgetsTemperature.php'
    };

    sourceGraph.data.time = '24';

    var dataAdapterGraph = new $.jqx.dataAdapter(sourceGraph,
        {
            autoBind: true,
            async: false,
            downloadComplete: function () {
            },
            loadComplete: function () {
            },
            loadError: function () {
            }
        });
    d = new Date();
    d.setHours(d.getHours() - 3);
// prepare jqxChart settings
    var settingsGraph = {
        title: "Temperatures last 24h",
        description: "NASDAQ Composite compared to S&P 500",
        showLegend: true,
        enableAnimations: true,
        padding: {left: 5, top: 5, right: 5, bottom: 5},
        titlePadding: {left: 90, top: 0, right: 0, bottom: 10},
        source: dataAdapterGraph,
        xAxis: {
            text: 'Time',
            baseUnit: "minute",
            valuesOnTicks: true,
            textRotationAngle: 0,
            dataField: 'Time',
            minValue: d,
            maxValue: new Date(),
            labels: {
                formatFunction: function (value) {
                    //var tmp_date = new Date(value);
                    return $.jqx.dataFormat.formatdate(new Date(value), "HH:mm");
                    //return tmp_date.getHours() +  ':' + tmp_date.getMinutes();
                },
                angle: 0,
                horizontalAlignment: 'right'
            },
            tickMarks: {visilbe: true},
            valueAxis: {
                displayValueAxis: true,
                description: 'Temperature',
                axisSize: 'auto',
                tickMarksColor: '#888888',
                gridLinesColor: '#888888'
            },
            rangeSelector: {
                // Uncomment the line below to render the selector in a separate container
                renderTo: $('#rangeSelector'),
                size: 100,
                padding: { top: 10, bottom: 0 },
                backgroundColor: '#3E3E42',
                dataField: 'Sensor2',
                valuesOnTicks: true,
                baseUnit: 'minute',
                showGridLines: true,
                formatFunction: function (value) {
                    return $.jqx.dataFormat.formatdate(new Date(value), "HH:mm");
                }
            }
        },
        backgroundColor: "#3E3E42",
        borderLineColor: "#888888",
        colorScheme: 'scheme05',
        seriesGroups: [
            {
                //useGradient: true,
                type: 'spline',
                series: [
                    {dataField: 'Sensor2', displayText: 'Sensor2', toolTipBackground: '#252526'},
                    {dataField: 'Sensor3', displayText: 'Sensor3', toolTipBackground: '#252526'},
                    {dataField: 'Sensor8', displayText: 'Sensor8', toolTipBackground: '#252526'},
                    {dataField: 'Sensor1', displayText: 'Sensor1', toolTipBackground: '#252526'},
                    {dataField: 'Sensor0', displayText: 'Sensor0', toolTipBackground: '#252526'},
                ]
            },
        ]
    }
    $('#chartContainer5').jqxChart(settingsGraph);
    return dataAdapterGraph;
}

function updateGraph(dataAdapterGraph) {
    dataAdapterGraph._source.data = createSeverData(24);
    dataAdapterGraph.dataBind();
    //$('#chartContainer5').jqxChart()
    $('#chartContainer5').jqxChart('update');
}