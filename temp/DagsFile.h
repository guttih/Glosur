#pragma once
#include "dagsetning.h"

#define CDAGSFILE_FILENAME "data.xml"
#define CDAGSFILE_ROOT     "gögn"
#define CDAGSFILE_ITEM     "DateItem"
#define CDAGSFILE_ITEMPATH "/" CDAGSFILE_ROOT "/" CDAGSFILE_ITEM

#define CDAGSFILE_TYPE		"type"
#define CDAGSFILE_NAME		"name"
#define CDAGSFILE_COMMENT	"comment"
#define CDAGSFILE_YEAR		"year"
#define CDAGSFILE_MONTH		"month"
#define CDAGSFILE_DAY		"day"


using namespace System::Xml;

class CDagsFile :
	public CDagsetning
{
private:
	int m_iYear;
	int m_iMonth;
	int m_iDay;
	CStrengur m_cstrType;
	CStrengur m_cstrName;
	CStrengur m_cstrComment;
	void reset();
	
private:
	
public:
	CDagsFile(void);
   ~CDagsFile(void);
	int						erHatid(int iAr, int iManudur, int iDagur);
	char *					NafnHatidardags(int iHatidarIndex);
	
	System::String ^		Type   (){return gcnew System::String(m_cstrType.getString());}
	System::String ^		Name   (){return gcnew System::String(m_cstrName.getString());}
	System::String ^		Comment(){return gcnew System::String(m_cstrComment.getString());}
	System::String ^		Date   ()
							{
								CStrengur cstr;cstr =m_iDay;cstr+=".";cstr+=m_iMonth;cstr+=".";cstr+=m_iYear;
								return gcnew System::String(cstr.getString());
							}
	bool					InitFile(System::Xml::XmlDocument ^* doc);
	CStrengur				strToCstr(System::String ^str);
	System::Xml::XmlNode ^	lesaFremst(System::Xml::XmlDocument ^ doc);
	System::Xml::XmlNode ^	lesaNaest(System::Xml::XmlNode ^inNode);
	System::Xml::XmlNode ^	finnaFremst(System::String ^strVariable, System::String ^strFindMe, System::Xml::XmlDocument ^ doc  );
	System::Xml::XmlNode ^	finnaNaest (System::String ^strVariable, System::String ^strFindMe, System::Xml::XmlNode     ^inNode);
	void					lesa(System::Xml::XmlNode ^inNode);
	// Bætir við nýrri færslu aftast í skránna
	bool skrifaAftast(char * strType, char * strName, char * strComment, int iYear, int iMonth, int iDay, System::Xml::XmlDocument ^ doc);
};
