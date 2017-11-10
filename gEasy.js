/*
    Eftir: Guðjón Hólm Sigurðsson
    Athuga hvort Einstaklings- eða fyrirtækjakennitala sé lögleg.
    skilar true ef strKennitala er OK
    skilar false ef strKennitala re ekki OK
    Kennitala má hafa bandstrik
*/
function erKennitalaOk(strKennitala) {

    if (!strKennitala) { return false; }

    var i,
        iLen = strKennitala.length;

    if (iLen == 11 && strKennitala.indexOf('-') == 6) {   //breyta úr "110871-4579" í "1108714579"
        strKennitala = strKennitala.substring(0, 6) + strKennitala.substring(7);
        iLen = strKennitala.length;
    }
    if (iLen != 10) { return false; }

    if (!Number(strKennitala)) { return false; }

    if (strKennitala == '1111111111') {
        return false;
    }	//kennitalan er lögleg en þá er ansi mikil tilviljun að einhver sé með hana svo ég ætla ekki að leyfa hana, líklegast er að einhver sé að svindla

    var i = Number(strKennitala.substring(0, 2));
    if (i > 71 || i < 1) { return false; }
    i = Number(strKennitala.substring(2, 4));
    if (i < 1 || i > 12) { return false; }//mánuður er ekki frá 1 til 12

    var summa = 0,
	    vartala = -1;
    studull = 3;
    for (i = 0; i < 8; i++) {
        if (i == 2) { studull = 7; }
        summa += (Number(strKennitala.substring(i, i + 1))) * studull;
        studull--;
    }
    summa = summa % 11;
    if (summa == 0) vartala = 0;
    if (summa >= 2 && summa <= 10) { vartala = 11 - summa; }
    if (vartala == (Number(strKennitala.substring(8, 9)))) {
        return true;
    }

    return false;
}

function addZero(x, n) {
        while (x.toString().length < n) {
            x = "0" + x;
        }
        return x;
    }
function dateToTime(d) {

    var hours        = addZero(d.getHours(), 2),
        minutes      = addZero(d.getMinutes(), 2),
        seconds      = addZero(d.getSeconds(), 2),
        milliseconds = addZero(d.getMilliseconds(), 3);

    return hours + ":" + minutes + ":" + seconds + "." + milliseconds;
}

function dateTimeMsString() {
    return dateToTime(new Date());
}

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
