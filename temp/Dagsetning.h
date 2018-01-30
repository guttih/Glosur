#ifndef CDAGSETNING
#define CDAGSETNING
#include "CStrengur.h"

class CDagsetning
{
public:
	CDagsetning(void);
	~CDagsetning(void);
	int		Paktar(unsigned int uiAr);
	int		Gyllitala(unsigned int uiAr);
	int		DagurPaskar(int iAr, int *iOutDagur);
	char *	NafnManadar(unsigned short usManudur=0);// skilar nafni mánaðar
	char *	NafnVikudags(unsigned short usVikudagur, bool bLongName=true);//skilar nafni vikudags

protected:
		CStrengur m_cstr;// Kemur í stað m_cTemp;
private:
	
	int m_iDagur;// Dagur dagsetningar
	int m_iManudur;// Mánuður dagsetningar
	int m_iAr;// Ár dagsetningar
	//char *m_cTemp;// Temp breyta sem notuð er þegar fall þarf að skyla streng.  Vara verður við í lýsingu fallsins að innihaldi þessarar breytu ber að afrita strax því öll föll í klasanum sem skyla þurfi streng munu nota þessa breytu.
	// Þetta fall skal bara kalla í úr constructor.  
	void initilize(void);
	unsigned int ArsManudurToDagar(int iAr, int iManudur);
	unsigned int ArsDagarToManudur(int iAr, unsigned int ArsManudarDagar);

public:
	// Athugar hvort viðkomandi dagsetning er hátíðardagur.  Ef skilagildi er minna en 0 þá er viðkomandi dagur ekki hátíðardagur ef skilagildið er minna en 0 þá er viðkomandi dagur ekki hátíðardagur en það er eitthvað sérstakt við hann.  Nota má skylagildi þessarar skipunar til þess að setja inn í fallið HatidIstreng
	virtual int erHatid(int iAr, int iManudur, int iDagur);
	// Fallið skilar nafni hátíðar sem fallið erHatid fann. 
	virtual char * NafnHatidardags(int iHatidarIndex);
	unsigned short erJolasveinn(int iManudur, int iDagur);
	char * NafnJolasveins(unsigned short usJolasveinn);
	// Skilar nafni jólasveins
	char * VisaJolasveins(unsigned short usJolasveinn);
	// Skilar vísu jólasveins
	unsigned short vikudagur (int iAr, int iManudur, int iDagur);
	void DaysDelete(int *iAr, int *iManudur, int *iDagur, unsigned int uiRemove);
	void DaysAdd   (int *iAr, int *iManudur, int *iDagur, unsigned int uiAdd);
	bool erHlaupar(int iAr);
	bool erRimspillisar(int iAr);
	int	 FyrstiVikudagur(int iFinnaVikudag, int iAr, int iManudur, int iDagur=0);
	void DagurFostudagurinnLangi(int iAr, int *iManudur, int *iDagur);
	void DagurOskudagur(int iAr, int *iManudur, int *iDagur);
	void DagurHvitasunnudagur(int iAr, int *iManudur, int *iDagur);
	void DagurAnnar_i_Hvitasunnu(int iAr, int *iManudur, int *iDagur);
	void DagurUppstigningardagur(int iAr, int *iManudur, int *iDagur);
	void DagurFridagurVerslunarmanna(int iAr, int *iManudur, int *iDagur);
	void DagurSkirdagur(int iAr, int *iManudur, int *iDagur);
	void DagurAnnar_i_Paskum(int iAr, int *iManudur, int *iDagur);
	void DagurBolludagur(int iAr, int *iManudur, int *iDagur);
	void DagurSprengidagur(int iAr, int *iManudur, int *iDagur);
	void DagurPalmasunnudagur(int iAr, int *iManudur, int *iDagur);
	void DagurMaedradagur(int iAr, int *iManudur, int *iDagur);
	void DagurSjomannadagur(int iAr, int *iManudur, int *iDagur);
	void DagurAdventa(int iAr, int *iManudur, int *iDagur);
	void DagurSumardagurinnFyrsti(int iAr, int *iManudur, int *iDagur);
	void DagurVorjafndaegur(int iAr, int *iManudur, int *iDagur);
	void DagurHaustjafndaegur(int iAr, int *iManudur, int *iDagur);
	// Skilar dagafjölda í mánuði
	int DagaFjoldi(int iAr, int iManudur);
	// Skilar fjölda virkra daga frá og með dagsetningum tilteknum í færibreytum
	int FjoldiVirkraDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag);
	// Skilar fjölda frídaga daga frá og með dagsetningum tilteknum í færibreytum
	// Til frídaga teljast helgidagar og hátíðardagar
	int FjoldiFriDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag);
	bool erVirkurDagur(int iAr, int iManudur, int iDagur);
};

#endif //CDAGSETNING