function getColor(i) {
    switch (i) {
        case 0:
            return "red";
        case 1:
            return "green";
        case 2:
            return "blue";
        case 3:
            return "cyan";
        case 4:
            return "purple";
        case 5:
            return "pink";
        case 6:
            return "orange";
        case 7:
            return "brown";
        case 8:
            return "gray";
        case 9:
            return "#060c0a";
        case 10:
            return "#301e17";
        case 11:
            return "#c4aca2";
        case 12:
            return "#b0b249";
        case 13:
            return "#4a6b69";
    }
    return "black";
}

function InitChart(dataIn, yScaleMax) {
    //til að gera
    console.log(dataIn);
    var YscaleMax;
    yScaleMax === undefined ? (YscaleMax = 215) : (YscaleMax = yScaleMax);

    var minMax = getMinMax(dataIn);
    console.log(minMax);
    var iso = d3.time.format.utc("%Y-%m-%d %H:%M:%S");
    var vis = d3.select("#visualisation"),
        WIDTH = 1000,
        HEIGHT = 500,
        MARGINS = {
            top: 20,
            right: 20,
            bottom: 20,
            left: 50
        },
        xScale = d3.scale.linear().range([MARGINS.left, WIDTH - MARGINS.right]);
    xScale.domain([minMax.minDate, minMax.maxDate]);

    (yScale = d3.scale
        .linear()
        .range([HEIGHT - MARGINS.top, MARGINS.bottom])
        .domain([0, minMax.maxVal])), (xAxis = d3.svg
        .axis()
        .scale(xScale)), (yAxis = d3.svg.axis().scale(yScale).orient("left"));
    xAxis.tickFormat(function(d) {
        return iso(new Date(d));
    });
    vis
        .append("svg:g")
        .attr("class", "x axis")
        .attr("transform", "translate(0," + (HEIGHT - MARGINS.bottom) + ")")
        .call(xAxis);
    /*vis
        .append("svg:g")
        .attr("class", "xaxis") // give it a class so it can be used to select only xaxis labels  below
        .attr("transform", "translate(0," + (HEIGHT - 120) + ")")
        .call(xAxis);*/
    vis
        .append("svg:g")
        .attr("class", "y axis")
        .attr("transform", "translate(" + MARGINS.left + ",0)")
        .call(yAxis);

    var lineGen = d3.svg
        .line()
        .x(function(d) {
            return xScale(d.datetime);
        })
        .y(function(d) {
            return yScale(d.val);
        })
        //.interpolate("linear");
        // .interpolate("cardinal");
        .interpolate("monotone");

    var tip = d3
        .tip()
        .attr("class", "d3-tip")
        .offset([-7, 0])
        .html(function(d) {
            return (
                '<span class="tip-key">Name</span><span class="tip-value">' +
                d.name +
                "</span><br>" +
                '<span class="tip-key">Date</span><span class="tip-value">' +
                iso(new Date(d.datetime)) +
                "</span><br>" +
                '<span class="tip-key">Pin</span><span class="tip-value">' +
                d.pin +
                "</span><br>" +
                '<span class="tip-key">Value</span><span class="tip-value">' +
                d.val +
                "</span><br>"
            );
        });

    vis.call(tip);

    //adding the lines
    var keys = Object.keys(dataIn);
    var color = d3.scale.category20();
    keys.forEach(function logArrayElements(key, i, item) {
        vis
            .append("svg:path")
            .attr("d", lineGen(dataIn[key]))
            .attr("stroke", getColor(i))
            .attr("stroke-width", 2)
            .attr("fill", "none");

        vis
            .selectAll("dot")
            .data(dataIn[key])
            .enter()
            .append("circle")
            .attr("stroke", "white")
            .attr("fill", getColor(i))
            .attr("r", 4)
            .attr("cx", function(d, i) {
                return xScale(d.datetime);
            })
            .attr("cy", function(d, i) {
                return yScale(d.val);
            })
            .on("mouseover", tip.show)
            .on("mouseout", tip.hide);
    });
}

//converst logs object to a chartPinObject which will allow d3 to draw a chart for all pin values.
function logsToChartPins(logs) {
    var i, x, pins;
    var ret = {};
    for (i = 0; i < logs.length; i++) {
        log = logs[i];
        for (x = 0; x < log.pins.length; x++) {
            if (ret[log.pins[x].name] === undefined) {
                ret[log.pins[x].name] = [];
            }
            ret[log.pins[x].name].push({
                datetime: log.datetime,
                pin: log.pins[x].pin,
                val: log.pins[x].val,
                name: log.pins[x].name
            });
        }
    }
    return ret;
}

function getMinMax(dataIn) {
    var now = new Date();
    var tmp = {};
    var keys = Object.keys(dataIn);
    keys.forEach(function logArrayElements(element) {
        var pin = dataIn[element];
        var len = pin.length;
        for (x = 0; x < len; x++) {
            if (tmp.minDate === undefined) {
                tmp.minDate = tmp.maxDate = pin[x].datetime;
                tmp.minVal = tmp.maxVal = pin[x].val;
            } else if (dataIn[element][x].datetime < tmp.minDate) {
                tmp.minDate = dataIn[element][x].datetime;
            } else if (dataIn[element][x].datetime > tmp.maxDate) {
                tmp.maxDate = dataIn[element][x].datetime;
            }

            if (dataIn[element][x].val < tmp.minVal) {
                tmp.minVal = dataIn[element][x].val;
            } else if (dataIn[element][x].val > tmp.maxVal) {
                tmp.maxVal = dataIn[element][x].val;
            }
        }
    });
    return {
        minVal: tmp.minVal,
        maxVal: tmp.maxVal,
        minDate: tmp.minDate,
        maxDate: tmp.maxDate
    };
}

var logs = [
    {
        datetime: new Date("2017-06-06T10:08:42.803Z"),
        pins: [
            { pin: 0, val: 0, name: "D0" },
            { pin: 1, val: 10, name: "D1" },
            { pin: 2, val: 20, name: "D2" },
            { pin: 3, val: 210, name: "D3" },
            { pin: 4, val: 111, name: "D4" },
            { pin: 5, val: 211, name: "D5" },
            { pin: 6, val: 22, name: "D6" },
            { pin: 7, val: 44, name: "D7" },
            { pin: 8, val: 3, name: "D8" },
            { pin: 9, val: 33, name: "D9" },
            { pin: 10, val: 133, name: "D10" },
            { pin: 11, val: 233, name: "D11" }
        ]
    },
    {
        datetime: new Date("2017-06-06T12:08:42.803Z"),
        pins: [
            { pin: 0, val: 15, name: "D0" },
            { pin: 1, val: 110, name: "D1" },
            { pin: 2, val: 210, name: "D2" },
            { pin: 3, val: 210, name: "D3" },
            { pin: 4, val: 211, name: "D4" },
            { pin: 5, val: 111, name: "D5" },
            { pin: 6, val: 22, name: "D6" },
            { pin: 7, val: 0, name: "D7" },
            { pin: 8, val: 3, name: "D8" },
            { pin: 9, val: 33, name: "D9" },
            { pin: 10, val: 233, name: "D10" },
            { pin: 11, val: 133, name: "D11" }
        ]
    },
    {
        datetime: new Date("2017-06-06T14:08:42.803Z"),
        pins: [
            { pin: 0, val: 55, name: "D0" },
            { pin: 1, val: 10, name: "D1" },
            { pin: 2, val: 12, name: "D2" },
            { pin: 3, val: 110, name: "D3" },
            { pin: 4, val: 2, name: "D4" },
            { pin: 5, val: 11, name: "D5" },
            { pin: 6, val: 122, name: "D6" },
            { pin: 7, val: 110, name: "D7" },
            { pin: 8, val: 223, name: "D8" },
            { pin: 9, val: 133, name: "D9" },
            { pin: 10, val: 33, name: "D10" },
            { pin: 11, val: 0, name: "D11" }
        ]
    }
];
var gdat = logsToChartPins(logs);
InitChart(gdat);
