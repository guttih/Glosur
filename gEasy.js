//Nice to have functions

function msToTime(duration) {
    var milliseconds = parseInt((duration % 1000) / 100)
        , seconds = parseInt((duration / 1000) % 60)
        , minutes = parseInt((duration / (1000 * 60)) % 60)
        , hours = parseInt((duration / (1000 * 60 * 60)) % 24);

    hours = (hours < 10) ? "0" + hours : hours;
    minutes = (minutes < 10) ? "0" + minutes : minutes;
    seconds = (seconds < 10) ? "0" + seconds : seconds;

    return hours + ":" + minutes + ":" + seconds + "." + milliseconds;
}

function logStr(str) {
    var d = Date();
    var timeStr = msToTime(Date.now());
    console.log(timeStr + ' | ' + str);
}
function log(obj) {
    var d = Date();
    var timeStr = msToTime(Date.now());
    console.log(timeStr);
    console.log(obj);
}

