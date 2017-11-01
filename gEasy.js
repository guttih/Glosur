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
function msTime() {
    return msToTime(Date.now());
}

function logStr(str) {
    console.log(msTime() + ' | ' + str);
}
function log(arg) {
    if (arguments.length === 1 && typeof arg == 'string') {
        return logStr(arg);
    }
    console.log(msTime() + ' | Object below');
    try {
        console.log.apply(console, arguments);
    } catch (e) {
        try {
            opera.postError.apply(opera, arguments);
        } catch (e) {
            logStr(arg);
        }
    }
}
