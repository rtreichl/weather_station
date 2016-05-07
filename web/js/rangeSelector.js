/**
 * Created by Richard Treichl on 05.05.2016.
 */

function createRangeSelector()
{
    var d = new Date();
    d.setHours(d.getHours() - 24);
    d.setSeconds(0);
    d.setMilliseconds(0);
    var r = new Date();
    r.setHours(r.getHours() - 3);
    r.setSeconds(0);
    r.setMilliseconds(0);
    $("#rangeSelector").jqxRangeSelector({
        width: 1200,
        height: 50,
        min: d,
        max: new Date(),
        range: {
            from: r,
            to: new Date(),
        },
        majorTicksInterval: { hours: 1 },
        minorTicksInterval: { minutes: 15 },
        labelsFormat: 'HH:mm',
        markersFormat: 'HH:mm',
        theme: 'metrodark',
    });
}