#include "dagsetning.h"


//#ifndef _WINDOWS_
//	#include <windows.h>
//#endif

#include <stdio.h>

CDagsetning::CDagsetning(void)
: m_iDagur(0)
, m_iManudur(0)
, m_iAr(0)
{
	m_cstr="";
}

// Þetta fall skal bara kalla í úr constructor.  
void CDagsetning::initilize(void)
{

}
CDagsetning::~CDagsetning(void)
{

}
//Meiga paktar vera -1 árið 2090 ? 
int CDagsetning::Paktar(unsigned int uiAr)
{
	/*regla sem gildir fyrir nýja stíl
	Takið ártalið og deilið í það með 19. 
	Afganginn skal margfalda með 11, leggja þar við 8, 
	draga frá aldatalið (fyrir 1970 er aldatalið 19), leggja síðan við fjórðung aldatalsins (að afgangi slepptum) og bæta loks við þeirri tölu sem fæst þegar aldatalið er margfaldað með 8, 13 bætt við og deilt í með 25 (afgangi sleppt). Í töluna sem þá kemur út er deilt með 30, og er afgangurinn þá paktarnir. 
	Dæmi: 1970. Við deilum 19 upp í 1970, fáum 13 í afgang, 
	margföldum þá tölu með 11 og fáum 143. Þar við bætast 8, sem gefa 151. 
	Við drögum frá aldatalið 19 og höfum þá eftir 132. Síðan leggst við fjórðungurinn af 19, 
	sem er 4, og fæst þá 136. Loks tökum við 19, margföldum með 8 (= 152), 
	bætum 13 við (= 165) og deilum með 25. Útkoman þar er 6 sem við leggjum nú við 136 og fáum 142. 
	Í þá tölu deilum við með 30. Afgangur verður 22, og eru það paktar ársins*/

	/*Fyrir gamla stíl gildir styttri regla: 
	Takið ártalið og deilið í það með 19. 
	Afganginn skal margfalda með 11 og leggja 8 við. 
	Síðan er deilt í útkomuna með 30, og er afgangurinn þá paktarnir*/
	int iRest, iOld, iPaktar, iAldatal;
	iAldatal=uiAr/100;
	iRest=uiAr % 19;
	iRest*=11;
	iRest+=8;
	iRest-=iAldatal;
	iRest+=iAldatal/4;
	iOld=(((iAldatal*8)+13)/25);
	iRest+=iOld;
	iPaktar=iRest%30;

	return iPaktar;
}

int CDagsetning::Gyllitala(unsigned int uiAr)
{
	return 1+(uiAr % 19);
}

//skilar mánuði sem páskadagur er í á því ári sem iAr segir til um.
//ef iOutDagur er 0 þá er ekkert gert við þá breytu. annars
//skilar fallið mánaðadegi í þessa breytu
//Páskar ............. 22. mars til 25. apríl 
int CDagsetning::DagurPaskar(int iAr, int *iOutDagur)
{	/*Besta reiknireglan til að finna páska í nýja stíl mun vera sú sem birtist nafnlaust í breska tímaritinu Nature árið 1876. Reglan er þessi: 

       Deilið í ártalið með 19 og kallið afganginn a. 
       Deilið í ártalið með 100, kallað deildina b og afganginn c. 
       Deilið í b með 4, kallið deildina d og afganginn e. 
       Deilið í b + 8 með 25 og kallið deildina f. 
       Deilið í b –f + 1 með 3 og kallið deildina g. 
       Deilið í 19a + b – d – g + 15 með 30 og kallið afganginn h. 
       Deilið í c með 4 og kallið deildina i og afganginn j. 
       Deilið í 32 + 2e + 2i – h – j með 7 og kallið afganginn k. 
       Deilið í a + 11h+22k með 451 og kallið deildina m. 
       Deilið í h + k – 7m + 114 með 31, kallið deildina n og afganginn p. 
		Þá er n mánuðurinn sem páskadagur fellur í, og p + 1 er mánaðardagurinn. 

Ef við tökum 1971 sem dæmi fáum við a = 14, b = 19, c = 71, d = 4, e = 3, f = 1, g = 6, h = 20, i = 17, j = 3, k = 0, m = 0, n = 4, p = 10. Þá eru páskarnir í 4. mánuði ársins og dagurinn er 10 + 1, þ. e. 11. apríl. 
*/
		int a,b,c,d,e,f,g,h,i,j,k,m,n,p;
		a=iAr % 19;					//Deilið í ártalið með 19 og kallið afganginn a. 
        b=iAr/100;					//Deilið í ártalið með 100, kallað deildina b og afganginn c. 
		c=iAr%100;
		d=b/4;						//Deilið í b með 4, kallið deildina d og afganginn e. 
		e=b%4;
		f=(b+8)/25;					//Deilið í b + 8 með 25 og kallið deildina f. 
		g=(b-f+1)/3;				//Deilið í b –f + 1 með 3 og kallið deildina g. 
        h=((19*a)+b-d-g+15)%30;		//Deilið í 19a + b – d – g + 15 með 30 og kallið afganginn h. 
        i=c/4;						//Deilið í c með 4 og kallið deildina i og afganginn j. 
		j=c%4;
        k=(32+(2*e)+(2*i)-h-j)%7;	//Deilið í 32 + 2e + 2i – h – j með 7 og kallið afganginn k. 
		m=(a+(11*h)+(22*k))/451;	//Deilið í a + 11h+22k með 451 og kallið deildina m. 
        n=(h+k-(7*m)+114)/31;		//Deilið í h + k – 7m + 114 með 31, kallið deildina n og afganginn p. 
		p=(h+k-(7*m)+114)%31;
		//Þá er n mánuðurinn sem páskadagur fellur í, og p + 1 er mánaðardagurinn. 
		if (iOutDagur)
			*iOutDagur=p+1;
		return n;
}


// skilar nafni mánaðar í lágstöfum. Ef usManudur er NULL þá reynir fallið að skila mánuði þessarar dagsetningar
// Skilagildið ber að afrita strax því öll föll í klasanum sem skila streng þessa sömu breytu.
// not thread save
char * CDagsetning::NafnManadar(unsigned short usManudur)
{
	if (!usManudur ||(usManudur>12 || usManudur<1))
		return 0;
//lock the temp variable
	switch(usManudur)
	{
		case 1 : m_cstr="janúar";	break;
		case 2 : m_cstr="febrúar";	break;
		case 3 : m_cstr="mars";		break;
		case 4 : m_cstr="apríl";	break;
		case 5 : m_cstr="maí";		break;
		case 6 : m_cstr="júní";		break;
		case 7 : m_cstr="júlí";		break;
		case 8 : m_cstr="ágúst";	break;
		case 9 : m_cstr="september";break;
		case 10: m_cstr="október";	break;
		case 11: m_cstr="nóvember";	break;
		case 12: m_cstr="desember";	break;
	}
	return m_cstr.getString();
}
// skilar númeri þess jólasveins sem kemur í desember
// 
unsigned short CDagsetning::erJolasveinn(int iManudur, int iDagur)
{
	if (iManudur!=12 || iDagur>24 || iDagur<12)
		return 0;
	return iDagur-11;
}
// skilar nafni jólasveins. 
// Ef usJolasveinn er NULL eða ef gildð <1 eða >13 þá skilar fallið 0
// Lögleg gildi eru 1,2,3,4,5,6,7,8,9,10,11,12 og 13.
// Skilagildið ber að afrita strax því öll föll í klasanum sem skila streng þessa sömu breytu.
// not thread save
// Notaðu fallið með erJolasveinn sem skilar númeri jólasveins útfrá dagsetningu
char * CDagsetning::NafnJolasveins(unsigned short usJolasveinn)
{
	usJolasveinn+=11;
	if (!usJolasveinn || usJolasveinn>24 || usJolasveinn<12)
		return 0;
	switch(usJolasveinn)
	{
		/* 1*/case 12: m_cstr="Stekkjastaur";	break;
		/* 2*/case 13: m_cstr="Giljagaur";		break;
		/* 3*/case 14: m_cstr="Stúfur";			break;
		/* 4*/case 15: m_cstr="Þvörusleikir";	break;
		/* 5*/case 16: m_cstr="Pottaskefill";	break;
		/* 6*/case 17: m_cstr="Askasleikir";	break;
		/* 7*/case 18: m_cstr="Hurðaskellir";	break;
		/* 8*/case 19: m_cstr="Skyrjarmur";		break;
		/* 9*/case 20: m_cstr="Bjúgnakrækir";	break;
		/*10*/case 21: m_cstr="Gluggagægir";	break;
		/*11*/case 22: m_cstr="Gáttaþefur";		break;
		/*12*/case 23: m_cstr="Ketkrókur";		break;
		/*13*/case 24: m_cstr="Kertasníkir";	break;
	}
	return m_cstr.getString();
}
// skilar vísu jólasveins. 
// Ef usJolasveinn er NULL eða ef gildð <1 eða >13 þá skilar fallið 0
// Lögleg gildi eru 1,2,3,4,5,6,7,8,9,10,11,12 og 13.
// Skilagildið ber að afrita strax því öll föll í klasanum sem skila streng þessa sömu breytu.
// not thread save
// Notaðu fallið með erJolasveinn sem skilar númeri jólasveins útfrá dagsetningu
char * CDagsetning::VisaJolasveins(unsigned short usJolasveinn)
{
	usJolasveinn+=11;
	if (!usJolasveinn || usJolasveinn>24 || usJolasveinn<12)
		return 0;
	switch(usJolasveinn)
	{									
		/* 1*/case 12: m_cstr="Stekkjastaur kom fyrstur,\nstinnur eins og tré.\nHann laumaðist í fjárhúsin\nog lék á bóndans fé.\n\nHann vildi sjúga ærnar,\n- þá var þeim ekki um sel,\nþví greyið hafði staurfætur,\n- það gekk nú ekki vel.";	break;
		/* 2*/case 13: m_cstr="Giljagaur var annar,\nmeð gráa hausinn sinn.\n- Hann skreið ofan úr gili\nog skauzt í fjósið inn.\n\nHann faldi sig í básunum\nog froðunni stal,\nmeðan fjósakonan átti\nvið fjósamanninn tal.";break;
		/* 3*/case 14: m_cstr="Stúfur hét sá þriðji\nstubburinn sá.\nHann krækti sér í pönnu,\nþegar kostur var á.\n\nHann hljóp með hana í burtu\nog hirti agnirnar,\nsem brunnu stundum fastar\nvið barminn hér og þar.";		break;
		/* 4*/case 15: m_cstr="Sá fjórði, Þvörusleikir,\nvar fjarskalega mjór.\nOg ósköp varð hann glaður,\nþegar eldabuskan fór.\n\nÞá þaut hann eins og elding\nog þvöruna greip,\nog hélt með báðum höndum,\nþví hún var stundum sleip.";	break;
		/* 5*/case 16: m_cstr="Sá fimmti, Pottaskefill,\nvar skrítið kuldastrá.\n- Þegar börnin fengu skófir\nhann barði dyrnar á.\n\nÞau ruku upp, til að gá að\nhvort gestur væri á ferð.\nÞá flýtti' ann sér að pottinum\nog fékk sér góðan verð.";	break;
		/* 6*/case 17: m_cstr="Sá sjötti, Askasleikir,\nvar alveg dæmalaus. -\nHann fram undan rúmunum\nrak sinn ljóta haus.\n\nÞegar fólkið setti askana\nfyrir kött og hund,\nhann slunginn var að ná þeim\nog sleikja á ýmsa lund.";	break;
		/* 7*/case 18: m_cstr="Sjöundi var Hurðaskellir,\n- sá var nokkuð klúr,\nef fólkið vildi í rökkrinu\nfá sér vænan dúr.\n\nHann var ekki sérlega\nhnugginn yfir því,\nþó harkalega marraði\nhjörunum í.";	break;
		/* 8*/case 19: m_cstr="Skyrjarmur, sá áttundi,\nvar skelfilegt naut.\nHann hlemminn o´n af sánum\nmeð hnefanum braut.\n\nSvo hámaði hann í sig\nog yfir matnum gein,\nunz stóð hann á blístri\nog stundi og hrein.";	break;
		/* 9*/case 20: m_cstr="Níundi var Bjúgnakrækir,\nbrögðóttur og snar.\nHann hentist upp í rjáfrin\nog hnuplaði þar.\n\nÁ eldhúsbita sat hann\ní sóti og reyk\nog át þar hangið bjúga,\nsem engan sveik.";	break;
		/*10*/case 21: m_cstr="Tíundi var Gluggagægir,\ngrályndur mann,\nsem laumaðist á skjáinn\nog leit inn um hann.\n\nEf eitthvað var þar inni\nálitlegt að sjá,\nhann oftast nær seinna\ní það reyndi að ná.";	break;
		/*11*/case 22: m_cstr="Ellefti var Gáttaþefur,\n- aldrei fékk sá kvef,\nog hafði þó svo hlálegt\nog heljarstórt nef.\n\nHann ilm af laufabrauði\nupp á heiðar fann,\nog léttur, eins og reykur,\ná lyktina rann.";	break;
		/*12*/case 23: m_cstr="Ketkrókur, sá tólfti,\nkunni á ýmsu lag. -\nHann þrammaði í sveitina\ná Þorláksmessudag.\n\nHann krækti sér í tutlu,\nþegar kostur var á.\nEn stundum reyndist stuttur\nstauturinn hans þá.";	break;
		/*13*/case 24: m_cstr="Þrettándi var Kertasníkir,\n- þá var tíðin köld,\nef ekki kom hann síðastur\ná aðfangadagskvöld.\n\nHann elti litlu börnin\nsem brostu, glöð og fín,\nog trítluðu um bæinn\nmeð tólgarkertin sín.";	break;
	}
	return m_cstr.getString();
}
// Skilar nafni vikudags í lágstöfum. 
// Skilagildi fallsins ber að afrita strax því öll föll í klasanum sem skila streng nota sama minnishólf(breytu).
// sunnudagur=1, mánudagur=2, þriðjudagur=3 o.s.fr.
// ef bLongName er 0 þá skilar fallið þriggja stafa nöfnum eins og:
// sun, mán=2, þri=3 o.s.fr.
// not thread save

char * CDagsetning::NafnVikudags(unsigned short usVikudagur, bool bLongName)
{
	if (usVikudagur>6)
		return 0;

	switch(usVikudagur)
	{
		case 0 : m_cstr="sunnudagur";	break;
		case 1 : m_cstr="mánudagur";	break;
		case 2 : m_cstr="þriðjudagur";	break;
		case 3 : m_cstr="miðvikudagur";	break;
		case 4 : m_cstr="fimmtudagur";	break;
		case 5 : m_cstr="föstudagur";	break;
		case 6 : m_cstr="laugardagur";	break;
	}
	if (!bLongName)
		m_cstr.left(3);

	return m_cstr.getString();
}

//     
//  Athugar hvort viðkomandi dagsetning er hátíðardagur eða hefur textastreng.  
//  -Ef skilagildið er >  0 þá er viðkomandi dagur hátíðardagur.
//  -Ef skilagildið er == 0 þá er viðkomandi dagur EKKI hátíðardagur.
//  -ef skilagildið er <  0 þá er viðkomandi dagur ekki hátíðardagur en
//   það er einhver textastrengur tengdur þessari dagsetningu.
//   T.d. "bóndadagur".
//  Skilgreining hátíðardags: 
//	   Dagur sem er lögbundinn frídagur en þó ekki helgidagur.  
//     Þó að frí sé lögboðið hluta dagsins þá er hann meðhöndlaður sem frídagur.  
//     Dæmi: Aðfangadagur er frídagur þó að lögbundið frí er aðeins eftir 12:00 þann dag.
//
//  Nota má skylagildi þessa falls til þess að setja inn í fallið NafnHatidardags.
//  Dæmi um notkun: 
//		CDagsetning cDags;
//		m_cstring str;
//  	int i=cDags.erHatid(2004, 4, 11);
//  	if (i!=0)
//  		str=cDags.NafnHatidardags(i);
//      Nú inniheldur str textann "páskadagur" 
//
//   erHatid skilar hæsta gild 18 og lægsta gild -16
//   ef þú ætlar að útfæra þetta fall í erfðum klasa þá er 
//   öruggast að nota tölur sem eru minni en -99 og stærri en 99
//   þegar þú ert að vísa í aðra hátíardaga sem þú vilt sjálfur tiltaka.

int CDagsetning::erHatid(int iAr, int iManudur, int iDagur)
{
	int iPaskaMan,iPaskarDag, iVikudagur, m, d;

	if (12==iManudur && 23==iDagur)				return -14;//Þorláksmessa
	if (12==iManudur && 24==iDagur)				return 2;//aðfangadagur
	if (12==iManudur && 25==iDagur)				return 3;//Jóladagur
	if (12==iManudur && 26==iDagur)				return 9;//Annar í jólum
	if ( 5==iManudur &&  1==iDagur)				return 10;//verkalýðsdagurinn
	if ( 1==iManudur &&  1==iDagur)				return 7;//nýársdagur
	if ( 1==iManudur &&  6==iDagur)				return -13;//þrettándinn
	if (12==iManudur && 31==iDagur)				return 8;//gamlársdagur
	if (6==iManudur && 17==iDagur)				return 14;//þjóðhátíðardagurinn

	iPaskaMan=DagurPaskar(iAr, &iPaskarDag);
	if (iPaskaMan==iManudur && iPaskarDag==iDagur)	return 1;//páskadagur
	if (iManudur<=iPaskaMan)
	{	
		DagurFostudagurinnLangi(iAr,&m,&d);	if (m==iManudur && d==iDagur) return 11;//föstudagurinn langi
		DagurSkirdagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return 12;//DagurSkirdagur
		DagurAnnar_i_Paskum(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 13;//DagurAnnar_i_Paskum
		DagurOskudagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return -2;//Öskudagur	rr	
		DagurBolludagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return -8;//bolludagur
		DagurSprengidagur(iAr,&m,&d);		if (m==iManudur && d==iDagur) return -9;//sprengidagur
		DagurPalmasunnudagur(iAr,&m,&d);	if (m==iManudur && d==iDagur) return  18;//Pálmasunnudagur
	}//if (iManudur<=iPaskaMan)
	
	DagurHvitasunnudagur(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 4;//Hvítasunnudagur
	DagurAnnar_i_Hvitasunnu(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 15;//Annar í hvítasunnu
	//komið getur fyrir að uppstigningardagur lendi á sama dag og 1. maí(verklíðsdag) þá sést þessi dagur aldrei
	DagurUppstigningardagur(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 5;//Uppstigningardagur	
	DagurSjomannadagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return  16;//sjómannadagur
	DagurMaedradagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return  -15;//mæðradagur
	DagurAdventa(iAr,&m,&d);				if (m==iManudur && d==iDagur) return  17;//aðventa
	DagurSumardagurinnFyrsti(iAr,&m,&d);	if (m==iManudur && d==iDagur) return  -1;//sumardagurinn fyrsti
	
	if ( 2==iManudur && 14==iDagur)				return -3;//Valentínusdagur
	if (12==iManudur &&  1==iDagur)				return -4;//fullveldisdagurinn 
	if ( 2==iManudur && 29==iDagur)				return -10;//hlaupársdagur
	if (11==iManudur && 11==iDagur)				return -12;//dagur íslenskrar tungu
	if ( 6==iManudur && 24==iDagur)				return -16;//Jónsmessa


	DagurFridagurVerslunarmanna(iAr,&m,&d);	
	if (m==iManudur && d==iDagur)
		return 6;//frídagur verslunarmanna fyrist mánudagur í ágúst
	iVikudagur=vikudagur(iAr, iManudur, iDagur);

	//konudagur og bóndadagur semma ekki árið 2023
	//vetrardagur, fyrsti, laugardagurinn að lokinni 26. viku (í sumaraukaárum 27. viku) sumars. Fyrsta vetrardag ber upp á 21.-27. október, nema í rímspillisárum: 28. október. 
	if (10==iManudur && 28==iDagur && erRimspillisar(iAr))
		return -7;//fyrist vetrardagur
	if (10==iManudur &&  20<iDagur &&  28>iDagur && 6==iVikudagur/*!erRimspillisar(iAr) ekki þarf að tékka á þessu vegna return fyrir ofan*/)
		return -7;//fyrist vetrardagur
	
	//finna bóndadag sem er fyrsti dagur þorra
	//þorri, 4. mánuður vetrar að íslensku tímatali; hefst  með föstudegi í 
	//13. viku vetrar (19.-25. jan. nema á eftir rímspillisári, þá 26. jan.).
	if (1==iManudur &&  18<iDagur &&  27>iDagur)				
	{
		
		if (26==iDagur && erRimspillisar(iAr-1))
		{
				return -5;//bóndadagur
		}
		else
		{
			if (5==iVikudagur && iDagur!=26)
				return -5;//bóndadagur
		}
	}//bóndadagur if (1==iManudur &&  18<iDagur &&  27>iDagur)				

	//konudagur, fyrsti dagur "góu". Sagt er að húsfreyjur hafi átt að fagna góu þennan dag, og að bændur hafi átt að gera húsfreyjum eitthvað vel til. Þess munu einnig dæmi, að hlutverk hjónanna í þessum sið hafi verið hin gagnstæðu. 
	//góa (áður gói), fimmti mánuður vetrar að forníslensku tímatali; hefst með sunnudegi í 18. viku vetrar (18.- 24. febrúar, nema á eftir rímspillisári, þá 25. febrúar). Nafnskýring óviss. 
	if (2==iManudur &&  25==iDagur && erRimspillisar(iAr))
		return -6;//konudagur
	if (2==iManudur &&  17<iDagur &&  25>iDagur && 0==iVikudagur && !erRimspillisar(iAr))
		return -6;//konudagur

	
//	finna bolludag
    //bolludagur, mánudagurinn í "föstuinngang". Nafnið er kennt við bollur sem siður er að borða þennan dag. Þótt siðurinn sé erlendur mun nafnið upprunnið á Íslandi.
	//föstuinngangur (föstuígangur, föstugangur), fyrstu dagar þeirrar viku sem langafasta hefst í, þ. e. sunnudagur, mánudagur og þriðjudagur á undan öskudegi, eða aðeins fyrsti dagurinn af þessum þremur (föstuinngangs-sunnudagur). 
//	finna aðventu
	//aðventa, "jólafasta". Nafnið er dregið af latneska orðinu adventus sem merkir koma, þ. e. koma Krists, og skírskotar til jólanna sem fram undan eru. 
	//jólafasta (aðventa), trúarlegt föstutímabil á undan jólunum. Hefst með 4. sunnudegi fyrir jóladag, þ.e. 27. nóv. - 3. des. 
//	finna bóndadag
	//bóndadagur, fyrsti dagur "þorra", miðsvetrardagur. Þessi dagur var tyllidagur að fornu. Sagt er að bændur hafi þá átt að "bjóða þorra í garð" og að húsfreyjur hafi átt að gera bændum eitthvað vel til. Einnig munu finnast dæmi um það að hlutverk hjónanna í þessum sið hafi verið hin gagnstæðu. 
	//þorri, 4. mánuður vetrar að íslensku tímatali; hefst  með föstudegi í 13. viku vetrar (19.-25. jan. nema á eftir "rímspillisári", þá 26. jan.). Nafnskýring óviss. 
	//rímspillisár (varnaðarár), það ár sem "rímspillir" hefst.
	//rímspillir, tímabil í íslenska misseristalinu þegar allir viðmiðunartímar tengdir gömlu misserunum verða degi seinna (miðað við dagsetningar eða messudaga) en mögulegt er samkvæmt venjulegum rímreglum. Þetta gerist í þau skipti sem "sumarauka" er skotið inn degi síðar en venjulega, oftast á 28 ára fresti. Rímspillir stendur frá "sumaraukanum", þ. e. frá miðsumri,  fram á hlaupársdag næsta ár. 
	// sumarauki (lagningarvika, viðlagning, viðurlag), innskotsvika sem bætt er inn í íslenska misseristalið á nokkurra ára fresti til að samræma það hinu náttúrlega árstíðaári. Í tveimur misserum (sumri og vetri) teljast venjulega tólf mánuðir þrítugnættir og fjórar nætur umfram (aukanætur), eða 364 dagar samtals. Árstíðaárið er rúmum degi lengra. Af því leiðir, að með hverju ári sem líður verða bæði sumar og vetur í misseristalinu stöðugt fyrr á ferðinni miðað við árstíðirnar ef ekki er lagfært með innskotsdögum. Lagfæringin er framkvæmd á þann hátt að einni viku (sumarauka) er skotið inn á eftir aukanóttum svo að miðsumar, og þar með næsta sumarkoma níu mánuðum (270 dögum) síðar, verður viku seinna en ella hefði orðið. Eftir núgildandi reglu (í gregoríanska tímatalinu eða nýja stíl) má sumardagurinn fyrsti ekki koma fyrr en 19. apríl. Sumaraukanum er því skotið inn í hvert sinn sem fyrirsjáanlegt er að sumardagurinn fyrsti myndi annars koma of snemma næsta ár (18. eða 17. apríl). Hægt er að sýna fram á að sumarauki hefst alltaf 22. júlí ef sá dagur er sunnudagur, en 23. júlí ef sá dagur er sunnudagur og hlaupár fer í hönd. Sumaraukaár verða öll ár sem enda á mánudegi, svo og ár sem enda á sunnudegi ef hlaupár fer í hönd.
	//Í prentuðum almanökum íslenskum fram til 1928 var sumarauka bætt aftan við síðasta sumarmánuð, en eftir það var horfið að þeim eldri reglum sem að ofan greinir.
	//Í gamla stíl (júlíanska tímatalinu) var sumarauka skotið inn þau ár sem enduðu á fimmtudegi, svo og þau ár sem enduðu á miðvikudegi, ef næsta ár var hlaupár. Með þessu móti var sumardagurinn fyrsti aldrei fyrr en 9. apríl. 
	//Fyrstu reglur um sumarauka voru lögteknar um miðja 10. öld að ráði Þorsteins surts.



/*Hátíðir sem fylgja páskunum 

Ýmsir merkisdagar kirkjunnar flytjast til í árinu með páskunum svo sem kunnugt er. Þessa daga er hægt að finna með sömu aðferð og notuð er til að finna páskana, nema hvað dagsetningarnar á fingrunum verða aðrar en þær sem sýndar eru á 26. mynd. Ef við tökum hvítasunnuna sem dæmi, getur hún í fyrsta lagi orðið 10. maí (þegar páskar eru 22. mars). Til þess að finna hvítasunnuna tiltekið ár byrjum við á því að leita uppi fingurstað páskadagsins, en þegar að því kemur að finna þá dagsetningu sem svarar til fingurstaðarins, verðum við í stað 22. mars að setja 10. maí á upplið vísifingurs innanverðan og telja þaðan. Kemur þá 11. maí á miðlið vísifingurs innanverðan, 12. maí á framlið vísifingurs innanverðan o. s. frv. þar til komið er að 13. júní á utanverðum upplið litlafingurs hægri handar, en það er síðasti fingurstaðurinn. Kemur það heim, að hvítasunnan er 13. júní þau ár sem páskana ber upp á 25. apríl. 

hvítasunnudagur og uppstigningardagur fylgja páskunum sem sér segir: 
  

Páskar ............. 22. mars til 25. apríl 
Öskudagur ..........  4. febrúar til 10. mars //öskudagur, miðvikudagur í 7. viku fyrir páska
Uppstigningardagur . 30. apríl til 3. júní 
Hvítasunna ......... 10. maí til 13. júní 

Með því að athuga almanakið getur lesandinn hæglega 
fundið fleiri tímamörk, s. s. fyrir níuviknaföstu, 
bolludag, sprengidag, pálmasunnudag, 
kóngsbænadag, trínitatis og dýradag. 
*/
	return 0;
}

// Fallið skilar texta dagsetningar sem fallið erHatid fann.
// Skilagildið frá fallinu ber að afrita strax því öll föll í klasanum sem skila streng nota sömu breytu.
// Skilagildi fallsins ber að afrita strax því öll föll í klasanum sem skila streng nota sama minnishólf(breytu).
// Ef villa skilar fallið NULL
// Not thread save
//  Dæmi um notkun: 
//		CDagsetning cDags;
//		m_cstring str;
//  	int i=cDags.erHatid(2004, 4, 11);
//  	if (i!=0)
//  		str=cDags.NafnHatidardags(i);
//      Nú inniheldur str textann "páskadagur" 

char * CDagsetning::NafnHatidardags(int iHatidarIndex)
{
	if (!iHatidarIndex || iHatidarIndex==0)
		return 0;
	
	unsigned short us;
	if (iHatidarIndex<0)//Ekki hátíðardagur en til er textastrengur fyrir viðkomandi dagsetningu
	{
		us=iHatidarIndex*-1;

		switch(us)
		{
			case 1 : m_cstr="sumardagurinn fyrsti";		break;
			case 2 : m_cstr="öskudagur";				break;
			case 3 : m_cstr="valentínusdagur";			break;
			case 4 : m_cstr="fullveldisdagurinn";		break;
			case 5 : m_cstr="bóndadagur";				break;
			case 6 : m_cstr="konudagur";				break;
			case 7 : m_cstr="fyrsti vetrardagur";		break;
			case 8 : m_cstr="bolludagur";				break;
			case 9 : m_cstr="sprengidagur";				break;
			case 10 : m_cstr="hlaupársdagur";			break;
		  //case 11 : m_cstr="";						break;
			case 12 : m_cstr="dagur íslenskrar tungu";	break;
			case 13 : m_cstr="þrettándinn";				break;
			case 14 : m_cstr="þorláksmessa";			break;
			case 15 : m_cstr="mæðradagur";				break;
			case 16 : m_cstr="jónsmessa";				break;
			
			default: return 0;

		}//switch(us)
		return m_cstr.getString();
	}//if (us<0)//Ekki hátíð en til er textastrengur fyrir viðkomandi dagsetningu
	us=iHatidarIndex;

	switch(us)//Hátíðardagur
	{
		case 1 : m_cstr="páskadagur";				break;
		case 2 : m_cstr="aðfangadagur";				break;
		case 3 : m_cstr="jóladagur";				break;
		case 4 : m_cstr="hvítasunnudagur";			break;
		case 5 : m_cstr="uppstigningardagur";		break;
		case 6 : m_cstr="frídagur verslunarmanna";	break;
		case 7 : m_cstr="nýársdagur";				break;
		case 8 : m_cstr="gamlársdagur";				break;
		case 9 : m_cstr="annar í jólum";			break;
		case 10: m_cstr="verkalýðsdagur";			break;
		case 11: m_cstr="föstudagurinn langi";		break;
		case 12: m_cstr="skírdagur";				break;
		case 13: m_cstr="annar í páskum";			break;
		case 14: m_cstr="þjóðhátíðardagurinn";		break;
		case 15 : m_cstr="annar í hvítasunnu";		break;
		case 16 : m_cstr="sjómannadagur";			break;
		case 17 : m_cstr="aðventa";					break;
		case 18 : m_cstr="pálmasunnudagur";			break;
			
		default: return 0;
	}
	return m_cstr.getString();
}


/*
 *	Count of days, which is Feb 29, from Jan 1, 0 to Jan 1, nYear
 *	There is no Feb 29 between Jan 1, 0 and Jan 1, -3, one between Jan 1, 0 and Jan 1, -4
 *	one between Jan 1, 0 and Jan 1, 3 AD, one between Jan 1, 0 and Jan 1, 4
 */
int	CountOfFeb29( int nYear )
{
	int	nCount = 0;

	if( nYear > 0 ) 
	{
		nCount = 1;	/* Year 0 is a leap year */
		nYear--;/* Year nYear is not in the period */
	}
	nCount += nYear / 4 - nYear / 100 + nYear / 400;

	return nCount;
}
// Skilar vikudag dagsetningar 0=sunnudagur, 1=mánudagur o.s.fr.
 /**************************************************************************
 *                                                                         *
 *   In the Gregorian calendar, which is widely used now, the year AD 1    *
 *   is directly preceded by the year 1 BC; a year 0 does not exist in     *
 *   this system. In contrast, astronomical reckoning indeed uses a year   *
 *   0. For the purpose of distinction, astronomical reckoning drops the   *
 *   symbols AD and BC and uses a plus or minus sign before the year       *
 *   instead. The astronomical year +1 therefore corresponds to the year   *
 *   AD 1, the year 0 corresponds to 1 BC, and the year -1 to 2 BC. For    *
 *   convenience, I'll use astronomical years in the program.              *
 *                                                                         *
 ***************************************************************************/
// Skilar vikudag dagsetningar 0=sunnudagur, 1=mánudagur o.s.fr.
unsigned short CDagsetning::vikudagur(int nYear, int nMonth, int nDay)
{
	int	nDayOfWeek;
	const static int	pnDaysBeforeMonth[] = {
		 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
	};
	
	if (!( nMonth > 0 && nMonth <= 12 )||
		!( nDay > 0 )||
		!( nDay <= ( pnDaysBeforeMonth[ nMonth+1 ] - pnDaysBeforeMonth[ nMonth ] )
		|| ( nMonth == 2 && nDay == 29 && erHlaupar(nYear) ))
		)
		return -1;
	
	/* the day of Jan 1, nYear */
	nDayOfWeek = 6 + nYear % 7 + CountOfFeb29(nYear) % 7 + 14;/* + 14 : makes nDayOfWeek >= 0 */
	
	/* the day of nMonth 1, nYear */
	nDayOfWeek += pnDaysBeforeMonth[ nMonth ];
	if( nMonth > 2 && erHlaupar(nYear) )	nDayOfWeek++;
	
	/* the day of nMonth nDay, nYear */
	nDayOfWeek += nDay - 1;
	nDayOfWeek %= 7;
	
	return nDayOfWeek;
}
//skilar mánuði
unsigned int CDagsetning::ArsDagarToManudur(int iAr, unsigned int ArsManudarDagar)
{
	unsigned int i=erHlaupar(iAr);
	if (!ArsManudarDagar || ArsManudarDagar>365+i)
		return 0;
	ArsManudarDagar--;
	if (ArsManudarDagar<  31  ) return 1;
	if (ArsManudarDagar<  59+i) return 2;
	if (ArsManudarDagar<  90+i) return 3;
	if (ArsManudarDagar< 120+i) return 4;
	if (ArsManudarDagar< 151+i) return 5;
	if (ArsManudarDagar< 181+i) return 6;
	if (ArsManudarDagar< 212+i) return 7;
	if (ArsManudarDagar< 243+i) return 8;
	if (ArsManudarDagar< 273+i) return 9;
	if (ArsManudarDagar< 304+i) return 10;
	if (ArsManudarDagar< 334+i) return 11;
	if (ArsManudarDagar< 365+i) return 12;
	
	return 0;
}
//skilar ársdögum
unsigned int CDagsetning::ArsManudurToDagar(int iAr, int iManudur)
{
	if (!iAr || iAr<0 || !iManudur)
		return 0;
	int i=erHlaupar(iAr);
	switch(iManudur)
	{
		case 1 : return 31;
		case 2 : return 59+i;
		case 3 : return 90+i;
		case 4 : return 120+i;
		case 5 : return 151+i;
		case 6 : return 181+i;
		case 7 : return 212+i;
		case 8 : return 243+i;
		case 9 : return 273+i;
		case 10: return 304+i;
		case 11: return 334+i;
		case 12: return 365+i;
	}
	
	return 0;
}
//eyðir tilteknum dagafjölda úr dagsetningu.
//uiRemove fjöldi daga til að eyða
//iAr ár dagsetningar sem breyta á
//iManudur mánuður dagsetningar breyta á.
//iDagur dagur dagsetningar breyta á.
void CDagsetning::DaysDelete(int *iAr, int *iManudur, int *iDagur, unsigned int uiRemove)
{
	int iTmpAr=*iAr, iTmpMan=*iManudur, iTmpDag=*iDagur, i;
	unsigned int uiArsDagaFjoldi=ArsManudurToDagar(iTmpAr, iTmpMan-1);
	uiArsDagaFjoldi+=iTmpDag;
	while (uiRemove>(unsigned int)(365+erHlaupar(iTmpAr)))
	{
		uiRemove-=(365+erHlaupar(iTmpAr));
		iTmpAr--;
	}
	uiArsDagaFjoldi-=uiRemove;
	iTmpMan=ArsDagarToManudur(iTmpAr, uiArsDagaFjoldi);
	i=ArsManudurToDagar(iTmpAr, iTmpMan-1);
	iTmpDag=uiArsDagaFjoldi-i;
	*iAr=iTmpAr;
	*iManudur=iTmpMan;
	*iDagur=iTmpDag;


	/*
	int months[]={0 ,31 ,28 ,31 ,30 ,31 ,30 ,31 ,31 ,30 ,31 ,30 ,31 };
		//        0  1   2   3   4   5   6   7   8   9   10  11  12

		if (erHlaupar(*iAr)) months[2]=29;
		*iDagur-=uiRemove;
		while ( *iDagur < 1)
			{	*iManudur=*iManudur-1;
				*iDagur+=months[*iManudur];
				
				if (*iManudur<1)
					{
						*iAr=*iAr-1;
						*iManudur=12;
						if (erHlaupar(*iAr))	months[2]=29;
						else					months[2]=28;
					}	
			}//days no more than a month will allows
	*/
}
//bætir tilteknum dagafjölda við dagsetningu.
//uiAdd fjöldi daga til að bæta við
//iAr ár dagsetningar sem breyta á
//iManudur mánuður dagsetningar breyta á.
//iDagur dagur dagsetningar breyta á.
void CDagsetning::DaysAdd(int *iAr, int *iManudur, int *iDagur, unsigned int uiAdd)
{		//           j   f   m   a   m   j   j   a   s   o   n   d 
	int months[]={0 ,31 ,28 ,31 ,30 ,31 ,30 ,31 ,31 ,30 ,31 ,30 ,31 };
		//        0  1   2   3   4   5   6   7   8   9   10  11  12
	    //           31 ,59, 90, 120,151,181,212,243,273,304,334,365

		if (erHlaupar(*iAr)) months[2]=29;
		*iDagur=*iDagur+uiAdd;
		while ( *iDagur > (months[*iManudur]) )
			{
				*iDagur=*iDagur-months[*iManudur];
				*iManudur=*iManudur+1;
				if (*iManudur>12)
					{
						*iAr=*iAr+1;
						*iManudur=0;
						if (erHlaupar(*iAr))	months[2]=29;
						else					months[2]=28;
					}	
			}//days no more than a month will allows
		
		
		while ( *iManudur > 12 )	
		{
			*iManudur-=12;//should never happen just a debug check
			*iAr=*iAr+1;
		}//months no more than 12;

}

bool CDagsetning::erHlaupar(int iAr)
{
	if (!(iAr%4))
	{
		if (!(iAr%100))
		{
			if (!(iAr%400))
				return 1;									
			return 0;
		}//if (gengur(year,100))			
		return 1;
	}//if gengur(year,4)
	return 0;
}

bool CDagsetning::erRimspillisar(int iAr)
{  //rímspillisár verða öll ár sem enda á mánudegi, svo og ár sem enda á sunnudegi ef hlaupár fer í hönd.
	int iVikudagur=vikudagur(iAr, 12, 31);
//	if (iVikudagur==1)
//		return true;
	if (iVikudagur==0 && erHlaupar(iAr+1))
		return true;
	
	return false;
}

//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu föstudagsins langa sem er alltaf á föstudegi
void CDagsetning::DagurFostudagurinnLangi(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 2);
}
//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu Skýrdags sem er alltaf á fimmtudegi
void CDagsetning::DagurSkirdagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 3);
}
//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu annars í páskum sem er alltaf á mánudegi
void CDagsetning::DagurAnnar_i_Paskum(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 1);
}
//pálmasunnudagur 
//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu Pálmasunnudags sem er alltaf sunnudaginn fyrir páska.
void CDagsetning::DagurPalmasunnudagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 7);
}
//Bolludagur ..........  
void CDagsetning::DagurBolludagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 48);
}
//Sprengidagur ..........  
void CDagsetning::DagurSprengidagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 47);
}
//Öskudagur ..........  4. febrúar til 10. mars //öskudagur, miðvikudagur í 7. viku fyrir páska
void CDagsetning::DagurOskudagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 46);
}

//Hvítasunna ......... 10. maí til 13. júní 
void CDagsetning::DagurHvitasunnudagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 49);
}
void CDagsetning::DagurAnnar_i_Hvitasunnu(int iAr, int *iManudur, int *iDagur)
{
	DagurHvitasunnudagur(iAr, iManudur, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 1);
}
//komið getur fyrir að uppstigningardagur lendi á sama dag og 1. maí(verklíðsdag)
//Uppstigningardagur . 30. apríl til 3. júní 
void CDagsetning::DagurUppstigningardagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 39);
}

//frídagur verslunarmanna fyrist mánudagur í ágúst 
void CDagsetning::DagurFridagurVerslunarmanna(int iAr, int *iManudur, int *iDagur)
{//2.8.2004 er frídagur verslunarmanna
	*iManudur=8;
	*iDagur=FyrstiVikudagur(1, iAr, *iManudur);
}

//mæðradagurinn, alþjóðlegur dagur til að heiðra mæður, haldinn annan sunnudag maímánaðar ár hvert.
void CDagsetning::DagurMaedradagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=5;
	*iDagur=FyrstiVikudagur(0, iAr, *iManudur)+7;
	return;//todo: annar sunnudagur í maí (2004 er hann 9.maí)
}
//sjómannadagurinn, hátíðisdagur tileinkaður sjómönnum, haldinn fyrsta sunnudag í júní, nema sá dagur sé hvítasunnudagur, þá er sjómannadagurinn viku síðar. Þessari reglu hefur verið fylgt allar götur síðan 1938, ef frá eru talin árin 1965-1968,  en þau ár var haldið upp á sjómannadaginn í maímánuði.
void CDagsetning::DagurSjomannadagur(int iAr, int *iManudur, int *iDagur)
{   //todo: sjómannadagur er fyrsti sunnudagur í júní nema
	//ef sá dagur er hvítasunnudagur þá er sjómannadagurinn
	//annan sunnudag í júní(2004 er hann 6.júní)
	DagurHvitasunnudagur(iAr, iManudur, iDagur);
	if (*iManudur==6 && *iDagur<8)
	{
		*iDagur=*iDagur+7;//sjómannadagur færist á næstu viku vegna hvítasunnu
		return;
	}
	*iManudur=6;
	*iDagur=FyrstiVikudagur(0, iAr, *iManudur);
}

//jólafasta (aðventa), trúarlegt föstutímabil á undan jólunum. Hefst með 4. sunnudegi fyrir jóladag, þ.e. 27. nóv. - 3. des.
void CDagsetning::DagurAdventa(int iAr, int *iManudur, int *iDagur)
{	*iManudur=11;
	*iDagur=27;

	*iDagur=FyrstiVikudagur(0, iAr, *iManudur, 27);
	if (*iDagur>30)
	{
		*iManudur=12;
		*iDagur=*iDagur-30;
	}

	return;//todo: (2004 er hann 28.nóvember)www
}
//Finnur og skilar fyrsta dag mánaðar sem hefur vikudaginn sem tiltekinn er í iFinnaVikudag.
//Athugið:      Fallið villuleitar ekki.  Þannig að í notkun fallsins skaltu vera
//              viss um að þú sért að senda lögleg gildi í færibreytum fallsins.
//iDagur:       Þessi breyta má vera NULL og er það sjálfgildi hennar.
//              Ef hún er NULL þá skilar fallið fyrsta dag mánaðar sem er tiltekinn er í iFinnaVikudag.
//              Ef hún er Ekki tiltekin þá mun fallið leita frá og með þeim dag sem tiltekinn er.
//              Varúð:  Fallið mun ekki villuleita hvort dagsetningin er lögleg.
//              Dæmi:  Ef færibreytur eru t.d. þessar:  iAr=2004, iManudur=1 og iDagur=30 og iFinnaVikudag=1
//              þá mun fallið skyla 33 sem er ólögleg dagsetning þ.e.a.s "33. janúar 2004" er ekki til.
//iFinnaVikudag:Hvaða vikudag skal leita að.  Lögleg gildi eru frá og með 0 til 6 þar sem 0 er sunnudagur og 6 er laugardagur.
int CDagsetning::FyrstiVikudagur(int iFinnaVikudag, int iAr, int iManudur, int iDagur)
{
	int iOffset=1, iAdd, iVikudagur;
	if (iDagur)
		iOffset=iDagur;
	iVikudagur=vikudagur(iAr, iManudur, iOffset);
	if (iVikudagur<=iFinnaVikudag)
		iAdd=(iFinnaVikudag-iVikudagur);
	else
		iAdd=(7+iFinnaVikudag-iVikudagur);
	
	return iAdd+iOffset;
}


void CDagsetning::DagurSumardagurinnFyrsti(int iAr, int *iManudur, int *iDagur)
{	*iManudur=4;
	*iDagur=FyrstiVikudagur(4, iAr, *iManudur, 19);

	return;//Sumardagurinn fyrsti er í í apríl (4. mán) frá og með 19-25
}

//todo:á að taka sumarsólstöður???
/*jafndægur, sú stund þegar sól er beint yfir miðbaug jarðar. Þetta gerist tvisvar á ári, á tímabilinu 19.-21. mars (vorjafndægur) og 21.-24. september (haustjafndægur). Um þetta leyti er dagurinn (frá sólarupprás til sólarlags) um það bil jafnlangur nóttinni hvar sem er á jörðinni, og af því er nafnið dregið.  Breytileiki dagsetninganna stafar aðallega af því að almanaksárið er ekki nákvæmlega jafnlangt árstíðaárinu, og samræmingin við árstíðaárið verður að gerast í stökkum, með aukadegi í hlaupárum.
Í stjörnufræði teljast jafndægur á því augnabliki þegar miðbaugslengd sólar er 0° eða 180°. Miðbaugslengdin reiknast frá vorpunkti, og munar litlu á þessari skilgreiningu og þeirri sem  áður var nefnd.  
*/
void CDagsetning::DagurVorjafndaegur(int iAr, int *iManudur, int *iDagur)
{//er þetta ekki reiknað eins og vetrardagurinn fyrist?
	return;//todo: hvenær byrjar vorið?  //19.-21. mars (vorjafndægur) (2004 er hann 20 mars)
}
void CDagsetning::DagurHaustjafndaegur(int iAr, int *iManudur, int *iDagur)
{//er þetta ekki reiknað eins og vetrardagurinn fyrist?
	return;//todo: hvenær byrjar haustið?  //21.-24. september (haustjafndægur).
}

// Skilar dagafjölda í mánuði
// Ef villa þá skilar fallið 0;
int CDagsetning::DagaFjoldi(int iAr, int iManudur)
{
	if (!iAr || iAr<0 ||
		!iManudur ||iManudur>12 || iManudur<1)
		return 0;

	int months[]={0 ,31 ,28 ,31 ,30 ,31 ,30 ,31 ,31 ,30 ,31 ,30 ,31 };
	months[2]+=erHlaupar(iAr);
	return months[iManudur];
}

// Skilar fjölda virkra daga frá og með dagsetningum tilteknum í færibreytum
int CDagsetning::FjoldiVirkraDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag)
{
	CDagsetning cd;
	int iRet=0;
	cd.DaysDelete(&iFraAr, &iFraMan, &iFraDag, 1);
	do
	{	cd.DaysAdd(&iFraAr, &iFraMan, &iFraDag, 1);
		iRet+=cd.erVirkurDagur(iFraAr, iFraMan, iFraDag);
		
	}while(!(iFraAr==iTilAr && iFraMan==iTilMan &&iFraDag==iTilDag));
	return iRet;
}
// Skilar fjölda frídaga daga frá og með dagsetningum tilteknum í færibreytum
	// Til frídaga teljast helgidagar og hátíðardagar
int  CDagsetning::FjoldiFriDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag)
{
	CDagsetning cd;
	int iRet=0;
	cd.DaysDelete(&iFraAr, &iFraMan, &iFraDag, 1);
	do
	{	cd.DaysAdd(&iFraAr, &iFraMan, &iFraDag, 1);
		iRet+=!cd.erVirkurDagur(iFraAr, iFraMan, iFraDag);
		
	}while(!(iFraAr==iTilAr && iFraMan==iTilMan &&iFraDag==iTilDag));
	return iRet;
}
//athugar hvort dagur er virkur eða ekki
//Fallið skilar 0 ef dagurinn er sunnudagur, laugardagur eða hátíðardagur
bool CDagsetning::erVirkurDagur(int iAr, int iManudur, int iDagur)
{
	int iVikudagur=vikudagur(iAr, iManudur, iDagur);
	if (iVikudagur==0 || iVikudagur==6)
		return 0;//Helgidagur
	if (erHatid(iAr, iManudur, iDagur)>0)
		return 0;//Hátíðardagur
	return 1;//Virkur dagur


}