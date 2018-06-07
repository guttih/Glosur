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

    var i = Number(strKennitala.substring(0, 2));
    if (i > 71 || i < 1) { return false; }
    i = Number(strKennitala.substring(2, 4));
    if (i < 1 || i > 12) { return false; } // Mánuður er ekki frá 1 til 12, kannski óþarfa tékk

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

        // Vartala er í lagi
        var stafur = strKennitala.charAt(9); // Öldin
        if (stafur !== '0' && stafur !== '9' && stafur !== '8') {
            return false;
        }

        if (baraEinstaklingur === undefined) { return true; } // Lögleg kennitala
        var tala = Number(strKennitala.charAt(0));
        if (baraEinstaklingur === true) {
            if ( tala > -1 && tala < 4 ) { return true; } // Einstaklins-kennitala
        } else {
            if ( tala > 3 && tala < 8 ) { return true; } // Fyrirtækis-kennitala
        }
    }

    return false;
}
