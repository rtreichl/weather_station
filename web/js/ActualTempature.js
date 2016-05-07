/**
 * Created by Richard Treichl on 12.04.2016.
 */
function createActualTemp(id, startNum) {
    var sourceDataView =
    {
        datatype: "json",
        datafields: [
            {name: 'text', type: 'string'},
            {name: 'value', type: 'float'},
            {name: 'min', type: 'float'},
            {name: 'max', type: 'float'},
            {name: 'vtext', type: 'string'},
        ],
        data: createSeverData(),
        url: 'php/jsonjqWidgetsActualls.php'
    };

    var dataAdapterDataView = new $.jqx.dataAdapter(sourceDataView,
        {
            autoBind: true,
            async: false,
            beforeLoadComplete: function (records) {
                var end = records.length;
                for(var i = 0; i < end; i++) {
                    var all = records[i].max - records[i].min;
                    records[i]['value' + i.toString()] = (records[i].value - records[i].min) / all * 100;
                    records[i+end] = jQuery.extend({}, records[i]);
                    records[i+end]['value' + i.toString()] = (100 - records[i]['value' + i.toString()]);
                }
                return records;
            },
            downloadComplete: function () {
            },
            loadComplete: function () {
            },
            loadError: function () {
            }
        });
    for (var i = 0; i < 4; i++) {
        var settings = {
            title: dataAdapterDataView.records[i].text,
            description: '',
            enableAnimations: true,
            showLegend: false,
            showBorderLine: false,
            backgroundColor: '#3E3E42',
            padding: { left: 5, top: 5, right: 5, bottom: 5 },
            titlePadding: { left: 5, top: 5, right: 5, bottom: 5 },
            source: dataAdapterDataView,
            showToolTips: false,
            seriesGroups:
                [
                    {
                        type: 'donut',
                        useGradientColors: false,
                        series:
                            [
                                {
                                    showLabels: false,
                                    enableSelection: true,
                                    displayText: 'text',
                                    dataField: 'value' + i.toString(),
                                    labelRadius: 120,
                                    initialAngle: 90,
                                    radius: 60,
                                    innerRadius: 50,
                                    centerOffset: 0
                                }
                            ]
                    }
                ]
        };
        var selector = id + (startNum + i).toString();
        settings.drawBefore = function (renderer, rect) {
            var i = this.seriesGroups[0].series[0].dataField;
            i = i.substr(5,1);
            var valueText = dataAdapterDataView.records[i].vtext;
            sz = renderer.measureText(valueText, 0, { 'class': 'chart-inner-text' });
            renderer.text(
                valueText,
                rect.x + (rect.width - sz.width) / 2,
                rect.y + rect.height / 2 + 5,
                0,
                0,
                0,
                { 'class': 'chart-inner-text' }
            );
        };
        $(selector).jqxChart(settings);
        $(selector).jqxChart('addColorScheme', 'customColorScheme', ['#1C97EA', '#1C97EA', '#1C97EA', '#1C97EA', '#686868', '#686868', '#686868', '#686868']);
        $(selector).jqxChart({ colorScheme: 'customColorScheme' });
    }
    return dataAdapterDataView;
}

function updateActualTemp(dataAdapterDataView, id, startNum)
{
    dataAdapterDataView._source.data = createSeverData();
    dataAdapterDataView.dataBind();
    for (var i = 0; i < 4; i++) {
        var selector = id + (startNum + i).toString();
        $(selector).jqxChart('update');
    }
}