/**
 * Created by Richard Treichl on 12.04.2016.
 */
function createGauge(id) {
    var sourceGauge =
    {
        datatype: "json",
        datafields: [
            {name: 'text', type: 'string'},
            {name: 'value', type: 'float'},
            {name: 'max', type: 'float'},
            {name: 'vtext', type: 'string'},
        ],
        data: createSeverData('now'),
        url: 'php/jsonjqWidgetsGuage.php'
    };
    var dataAdapterGauge = new $.jqx.dataAdapter(sourceGauge,
        {
            autoBind: true,
            async: false,
            downloadComplete: function () {
            },
            loadComplete: function (records) {
                //$('#chartContainer4').jqxBarGauge('val', [records[0].value]);
            },
            loadError: function () {
            }
        });
    $(id).jqxKnob({
        allowValueChangeOnClick: false,
        allowValueChangeOnDrag: false,
        allowValueChangeOnMouseWheel: false,
        value: dataAdapterGauge.records[2].value,
        min: 0,
        max: dataAdapterGauge.records[2].max,
        startAngle: 180,
        endAngle: 540,
        step: 0.01,
        snapToStep: true,
        width:150,
        height:150,
        pointerGrabAction: 'progressBar',
        rotation: 'clockwise',
        style: {fill: '#3E3E42'},
        marks: {
            drawAboveProgressBar: true,
            colorRemaining: 'white',
            colorProgress: 'white',
            style: 'line',
            offset: '78%',
            thickness: 3,
            size: '18%',
            minorInterval: 5
        },
        progressBar: {
            style: {fill: '#1C97EA', stroke: '#407ec3'},
            size: '18%',
            offset: '78%',
            background: {fill: '#686868', stroke: '#686868'}
        },
        pointer: {type: 'line', visible: false, style: {fill: '#407ec3'}, size: '18%', offset: '78%', thickness: 0}
    });
    var input = $('<div id="knobinput1" class="inputField">');
    var input2 = $('<div id="knobinput2" class="inputField2">');
    var input3 = $('<div id="knobinput3" class="inputField3">');
    var knob2 = $('<div id="knob2">');
    var knob3 = $('<div id="knob3">');
    $(id).append(knob2);
    $('#knob2').jqxKnob({
        allowValueChangeOnClick: false,
        allowValueChangeOnDrag: false,
        allowValueChangeOnMouseWheel: false,
        value: dataAdapterGauge.records[1].value,
        min: 0,
        max: dataAdapterGauge.records[1].max,
        startAngle: 190,
        width: 100,
        step: 0.01,
        height: 100,
        endAngle: 350,
        snapToStep: true,
        pointerGrabAction: 'progressBar',
        rotation: 'clockwise',
        style: {fill: 'transparent'},
        progressBar: {
            style: {fill: '#ea4e1a', stroke: '#ea4e1a'},
            size: '18%',
            offset: '78%',
            background: {fill: '#686868', stroke: '#686868'}
        },
        pointer: {type: 'line', visible: false, style: {fill: '#33AADD'}, size: '18%', offset: '78%', thickness: 0}
    });
    $(knob2).append(knob3);
    $('#knob3').jqxKnob({
        allowValueChangeOnClick: false,
        allowValueChangeOnDrag: false,
        allowValueChangeOnMouseWheel: false,
        value: dataAdapterGauge.records[0].value,
        min: 0,
        max: dataAdapterGauge.records[0].max,
        startAngle: 10,
        width: 100,
        height: 100,
        step: 0.01,
        endAngle: 170,
        snapToStep: true,
        pointerGrabAction: 'progressBar',
        rotation: 'clockwise',
        style: {fill: 'transparent'},
        progressBar: {
            style: {fill: '#82ea1a', stroke: '#82ea1a'},
            size: '18%',
            offset: '78%',
            background: {fill: '#686868', stroke: '#686868'}
        },
        pointer: {type: 'line', visible: false, style: {fill: '#00a4e1'}, size: '18%', offset: '78%', thickness: 0}
    });
// Add label element to the Knob widget and attach event handlers to update them when the widget value updates.
// Note that labels need not be sub elements of the knobs, and they are there just to display that they can be.
    $(id).append(input);
    $('#knob2').append(input2);
    $('#knob3').append(input3);
    $(input).html('<span style="font-size: 8px; width: 30%; display:inline-block; color: #1C97EA">Battery</span><span style="width:40%; display:inline-block; font-size:8px; color: whitesmoke;">' + dataAdapterGauge.records[2].vtext + '</span><span style="width:30%; font-size: 8px; color: #1C97EA; display:inline-block;">Charge</span>');
    $(input2).html('<div style="color: whitesmoke;">' + dataAdapterGauge.records[1].vtext + '</div><div style="font-size: 8px; color: #ea4e1a">Solar Voltage</div>');
    $(input3).html('<div style="font-size: 8px; color: #82ea1a">Battery Voltage</div><div style="color: whitesmoke;">' + dataAdapterGauge.records[0].vtext + '</div>');
    $('#knob2').css('position', 'absolute');
    $('#knob2').css('top', '25px');
    $('#knob2').css('left', '25px');
    $('#knob3').css('position', 'absolute');
    $('#knob3').css('top', '0px');
    $('#knob3').css('left', '0px');

    return dataAdapterGauge;
}

function updateGauge(dataAdapterGauge, id) {
    dataAdapterGauge._source.data = createSeverData('now');
    dataAdapterGauge.dataBind();
    $(id).val(dataAdapterGauge.records[2].value);
    $('#knob2').val(dataAdapterGauge.records[1].value);
    $('#knob3').val(dataAdapterGauge.records[0].value);
    var html = '<div style="font-size: 8px; color: #82ea1a">Battery Voltage</div><div style="color: whitesmoke;">' + dataAdapterGauge.records[0].vtext + '</div>';
    $('#knobinput3').html(html);
    html = '<div style="color: whitesmoke;">' + dataAdapterGauge.records[1].vtext + '</div><div style="font-size: 8px; color: #ea4e1a">Solar Voltage</div>';
    $("#knobinput2").html(html);
    html = '<span style="font-size: 8px; width: 30%; display:inline-block; color: #1C97EA">Battery</span><span style="width:40%; display:inline-block; font-size:8px; color: whitesmoke;">' + dataAdapterGauge.records[2].vtext + '</span><span style="width:30%; font-size: 8px; color: #1C97EA; display:inline-block;">Charge</span>';
    $('#knobinput1').html(html);
}