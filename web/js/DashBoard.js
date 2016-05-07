/**
 * Created by Richard Treichl on 05.05.2016.
 */

function createDashBoard() {
    $.get(
        "php/getSensorData2.php",
        {
            sensor: sensor,
            what: 'data',
            data: 'json',
        },
        function (data) {
           if(data.temp){
               var index = 1;
               for(var i = 1; i < 8; i++) {
                   $('#Acutal' + i.toString()).html('');
                   $('#Acutal' + i.toString()).css('width', '200px');
                   $('#Acutal' + i.toString()).css('height', '200px');
               }
               if(data.battery){
                   dataAdapterGauge = createGauge('#Acutal' + index.toString());
                   index += 1;
               }
               if(data.temp){
                   dataAdapterDataView = createActualTemp('#Acutal', index);
                   index += 4;
               }
               if(data.pressure){
                   dataAdapterPressure = createActualPress('#Acutal' + index.toString());
                   index += 1;
               }
               if(data.light){
                   //alert('light');
               }
               if(data.ground){
                   //alert('ground');
               }
               updateGraph(dataAdapterGraph);
           }
        },
        'json'
    );
}

function updateDashBoard() {
    $.getJSON(
        "php/getSensorData2.php",
        {
            sensor: sensor,
            what: 'data',
            data: 'json',
        },
        function (data) {
            var index = 1;
            if(data.battery){
                updateGauge(dataAdapterGauge, '#Acutal' + index.toString());
                index += 1;
            }
            if(data.temp){
                updateActualTemp(dataAdapterDataView, '#Acutal', index);
                index += 4;
            }
            if(data.pressure){
                updateActualPress(dataAdapterPressure, '#Acutal' + index.toString());
                index += 1;
            }
            if(data.light){
                //alert('light');
            }
            if(data.ground){
                //alert('ground');
            }
            updateGraph(dataAdapterGraph);
        }
    );
}