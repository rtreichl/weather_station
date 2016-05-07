/**
 * Created by Richard Treichl on 26.04.2016.
 */
function createTrends() {
    $("#trend1").jqxBulletChart({
        width: 50,
        height: 150,
        title:'',
        description:'',
        theme: 'energyblue',
        showTooltip: false,
        pointer: {
            color: 'red',
            value: 25,
        },
        ticks: {
            position: 'none',
        },
        orientation: "vertical",
        target: {
            value: 0,
            size: "1%",
            color: "#407ec3"
        },
        ranges: [{
            startValue: -50,
            endValue: 50,
            color: "#686868",
            opacity: 0.6
        }]
    });
}

function updateTrends() {
    $("#trend1").jqxBulletChart('val', 30);
}