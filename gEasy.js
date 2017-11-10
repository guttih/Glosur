/*
    Eftir: Guðjón Hólm Sigurðsson
    Athuga hvort Einstaklings- eða fyrirtækjakennitala sé lögleg.
    returns:
        true  : ef kennitala er OK
        false : ef kennitala er ólögleg.
    
    Parameters:
        strKennitala      : Kennitalan sem skoða skal má vera á forminu "110871-4579" og "1108714579".

        baraEinstaklingur : er valkvæð(optional) segir til um hvort bara eigi að samþykkja einstaklings kennitölur.
                            ef true: þá munu einungis einstaklings-kennitölur verða samþykktar.
                            ef false: þá munu bara fyrirtækis-kennitölur verða samþykktar.
                            ef ekki tiltekin(undefined) þá eru bæði löglegar fyrirtækis- og einstaklings kennitölur samþykktar.
    example of use:
        erKennitalaOk('1108714579');       // Mun skila true.   Athugað hvort kennitala sé lögleg.
        erKennitalaOk('1108714579', true); // Mun skila true.   Athugað hvort kennitala sé lögleg einstaklings-kennitala.
        erKennitalaOk('1108714579', false);// Mun skila  false. Athugað hvort kennitala sé lögleg fyrirtækja-kennitala.
	erKennitalaOk('5708982219');       // Mun skila true.   Athugað hvort kennitala sé lögleg.
        erKennitalaOk('5708982219', true); // Mun skila false.  Athugað hvort kennitala sé lögleg einstaklings-kennitala.
        erKennitalaOk('5708982219', false) // Mun skila true.   Athugað hvort kennitala sé lögleg fyrirtækja-kennitala.
*/
function erKennitalaOk(strKennitala, baraEinstaklingur) {

    if (!strKennitala) { return false; }

    var i,
        iLen = strKennitala.length;

    if (iLen == 11 && strKennitala.indexOf('-') == 6) {   //fjarlægja '-'
        strKennitala = strKennitala.substring(0, 6) + strKennitala.substring(7);
        iLen = strKennitala.length;
    }
    if (iLen != 10) { return false; }

    if (!Number(strKennitala)) { return false; }

    if (strKennitala == '1111111111') {
        return false;
    }	//kennitalan er lögleg en það er ansi mikil tilviljun að einhver sé með hana svo ég ætla ekki að leyfa hana, líklegast er að einhver sé að svindla

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

        //vartala er í lagi
        if (baraEinstaklingur === undefined) { return true; }
        var first = strKennitala.charAt(0);
        if (baraEinstaklingur === true) {
            if (first === '0' || first === '1') { return true;}
        } else {
            if (first === '4' || first === '5') { return true; }
        }
    }

    return false;
}
// fengið frá: https://is.wikipedia.org/wiki/Kennitala
function islSSNValidate(ssn) {
        if (typeof ssn !== 'undefined' && ssn != null && ssn.length > 0) {
            ssn = ssn.trim().replace('-', '').replace(' ', '');
            if (ssn.length != 10)
                return false;
			var sSum =
				(3 * parseInt(ssn.substr(0, 1))) +
				(2 * parseInt(ssn.substr(1, 1))) +
				(7 * parseInt(ssn.substr(2, 1))) +
				(6 * parseInt(ssn.substr(3, 1))) +
				(5 * parseInt(ssn.substr(4, 1))) +
				(4 * parseInt(ssn.substr(5, 1))) +
				(3 * parseInt(ssn.substr(6, 1))) +
				(2 * parseInt(ssn.substr(7, 1)));
			var modRes = sSum % 11;
			if (modRes > 0)
				modRes = 11 - modRes;
			if (modRes != parseInt(ssn.substr(8, 1)))
				return false
			var century = parseInt(ssn.substr(9, 1)); 
			if (isNaN(century) || (century != 0 && century != 9 && century != 8)) 
				return false;
        }
        return true;
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
