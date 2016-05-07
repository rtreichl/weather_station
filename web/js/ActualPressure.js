/**
 * Created by Richard Treichl on 05.05.2016.
 */
function createActualPress(id) {
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
        data: createSeverData('now'),
        url: 'php/jsonSeaLevelPressure.php'
    };
    
    var dataAdapterDataView = new $.jqx.dataAdapter(sourceDataView,
        {
            autoBind: true,
            async: false,
            beforeLoadComplete: function (records) {
                var end = records.length;
                for (var i = 0; i < end; i++) {
                    var all = records[i].max - records[i].min;
                    records[i]['value' + i.toString()] = (records[i].value - records[i].min) / all * 100;
                    records[i + end] = jQuery.extend({}, records[i]);
                    records[i + end]['value' + i.toString()] = (100 - records[i]['value' + i.toString()]);
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
    var settings = {
        title: dataAdapterDataView.records[0].text,
        description: '',
        enableAnimations: true,
        showLegend: false,
        showBorderLine: false,
        backgroundColor: '#3E3E42',
        padding: {left: 5, top: 5, right: 5, bottom: 5},
        titlePadding: {left: 5, top: 5, right: 5, bottom: 5},
        source: dataAdapterDataView,
        showToolTips: false,
        seriesGroups: [
            {
                type: 'donut',
                useGradientColors: false,
                series: [
                    {
                        showLabels: false,
                        enableSelection: true,
                        displayText: 'text',
                        dataField: 'value0',
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
    settings.drawBefore = function (renderer, rect) {
        //var i = this.seriesGroups[0].series[0].dataField;
        //i = i.substr(5, 1);
        var valueText = dataAdapterDataView.records[0].vtext;
        sz = renderer.measureText(valueText, 0, {'class': 'chart-inner-text2'});
        renderer.text(
            valueText,
            rect.x + (rect.width - sz.width) / 2,
            rect.y + rect.height / 2 + 5,
            0,
            0,
            0,
            {'class': 'chart-inner-text2'}
        );
    };
    $(id).jqxChart(settings);
    $(id).jqxChart('addColorScheme', 'customColorScheme2', ['#1C97EA', '#686868']);
    $(id).jqxChart({colorScheme: 'customColorScheme2'});
    return dataAdapterDataView;
}

function updateActualPress(dataAdapterPressure, id) {
    dataAdapterPressure._source.data = createSeverData('now');
    dataAdapterPressure.dataBind();
    $(id).jqxChart('update');
}