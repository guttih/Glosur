//strengur.cpp                
//fyrir Visual Studio 8


#include "CStrengur.h"
#include <stdlib.h>
#include <stdio.h> //for sprintf


CStrengur::CStrengur()
{
        CStrengur("");
}
CStrengur::CStrengur(const char *pStrengur)
{
        set(pStrengur);
}

int CStrengur::set(const char *pStrengur)
{
        return copy(m_strengur, pStrengur);
}

void CStrengur::set(unsigned long ul)
{
    _ultoa_s(ul, m_strengur, 10);
}

int CStrengur::copy(char *pStrDest, const char *pStrSource)
{
    if (!pStrDest)
        return -1;
    if (!pStrSource)
    {
        pStrDest[0]='\0';
        return 0;
    }

    int i= 0;
    while ((pStrDest[i] = pStrSource[i]) != '\0')
        i++;
    return i;
}

//returns the length of pStr1

int CStrengur::compare(const CStrengur a, const CStrengur b)
{
    const char    *pstrA,
                  *pstrB;
    pstrA=a.m_strengur;
    pstrB=b.m_strengur;
     int i;

   for (i=0; pstrA[i] == pstrB[i]; i++)
      if (pstrA[i] == '\0')
         return 0;

   return pstrA[i]-pstrB[i];
}

int CStrengur::cat(char * strDestination, const char * pStrAddMe)
{
    if (!strDestination)
        return -1;
    if (!pStrAddMe)
        return 0;
    int i = 0,
        j = 0;
    while (strDestination[i] != '\0')
        i++;

    while ((strDestination[i++] = pStrAddMe[j++]) != '\0');

    return i;
}
int CStrengur::len(const char * pStr)
{
    if (!pStr)
        return -1;
    const char *pString_loc = pStr;
    while (*pStr != '\0')
        pStr++;

    return pStr-pString_loc;
}
unsigned long CStrengur::toULong()
{   //todo what if -
    char *endptr;
    return strtoul(getString(), &endptr, 10);
}
long CStrengur::toLong()
{   //todo what if -
    char *endptr;
    return strtol(getString(), &endptr, 10);
}
double CStrengur::toDouble()
{   //todo what if -
    char *endptr;
    CStrengur temp;
    temp=m_strengur;
    temp.replace(",",".");
    int iPos,iCount=temp.countChars('.');
    if (iCount>1)
    {
        iPos=temp.posReverse('.');
        iCount=temp.replace(".","");
        iCount--;
        iPos-=iCount;
        temp.insert(iPos,".");
    }
    return strtod(temp.getString(), &endptr);

}

int CStrengur::operator ==(const char *pStr)
{
    return 0==compare(m_strengur, pStr);
}
int CStrengur::operator !=(const char *pStr)
{
    return 0!=compare(m_strengur, pStr);
}
int CStrengur::operator ==(const CStrengur a)
{
    return 0==compare(m_strengur, a.m_strengur);
}
int CStrengur::operator >(const CStrengur a)
{
    return 0>compare(m_strengur, a.m_strengur);
}
int CStrengur::operator <(const CStrengur a)
{
    return 0<compare(m_strengur, a.m_strengur);
}

CStrengur CStrengur::operator=(const CStrengur a)
{
    *this=a.m_strengur;
    return *this;
}
CStrengur CStrengur::operator=(const char *pStr)
{
    this->set(pStr);
    return *this;
}
CStrengur CStrengur::operator = (int i)
{
    _itoa_s(i, this->m_strengur, 10);
    return *this;
}
CStrengur CStrengur::operator = (unsigned int ui)
{
    _ultoa_s(ui, this->m_strengur, 10);
    return *this;
}
CStrengur CStrengur::operator =(unsigned long ul)
{
    _ultoa_s(ul, this->m_strengur, 10);
    return *this;
}

CStrengur CStrengur::operator = (double d)
{
    sprintf_s(this->m_strengur, "%lf", d);
    return *this;

}

CStrengur CStrengur::operator+=(const CStrengur a)
{
    *this+=a.m_strengur;
    return *this;
}
CStrengur CStrengur::operator+=(const char *pStr)
{
    cat(m_strengur, pStr);
    return *this;
}
CStrengur CStrengur::operator+=(unsigned long ul)
{
    char str[20];
    _ultoa_s(ul, str, 10);
    cat(m_strengur, str);
    return *this;
}

CStrengur CStrengur::operator-=(const CStrengur a)
{
    *this-=a.m_strengur;
    return *this;
}
CStrengur CStrengur::operator-=(const char *pStr)
{
    replace(pStr, "", 1);
    return *this;
}

CStrengur CStrengur::operator-(const CStrengur a)
{
    CStrengur temp(m_strengur);

    temp-=a.m_strengur;
    return temp;
}

CStrengur CStrengur::operator-(const char *pStr)
{
    CStrengur temp(m_strengur);
    temp-=pStr;
    return temp;
}
CStrengur CStrengur::operator+(const CStrengur a)
{
    CStrengur temp(m_strengur);
    temp+=a.m_strengur;
    return temp;
}
CStrengur CStrengur::operator+(const char *pStr)
{
    CStrengur temp(m_strengur);
    temp+=pStr;
    return temp;
}

unsigned int CStrengur::replace(const char * strDeleteMe, const char * strInsertMe, unsigned int uiHowManyReplacements)
{
    return replace(m_strengur, strDeleteMe, strInsertMe, uiHowManyReplacements);
}
//repace replaces one sub-string with another sub-string.
//strToBeChanged is the string that will be changed
//Deletes all occurrences of strDeleteMe and inserts strInsertMe in it's place.
//returns the number of occurrences replaced
//you can spectify how many replacements you want by spectifying iHowManyReplacements
//iHowManyReplacements is default set to -1 and that means untill all has been replaced
unsigned int CStrengur::replace(char * strToBeChanged, const char * strDeleteMe, const char * strInsertMe, unsigned int uiHowManyReplacements)
{
    char *pFound;
    unsigned int  iRet=0;
    pFound=find(strToBeChanged, strDeleteMe);
    while (pFound && iRet<uiHowManyReplacements)
    {
        iRet++;
        del(pFound, 0, len(strDeleteMe));
        insert(pFound, 0, strInsertMe);
        pFound=find(pFound+len(strInsertMe), strDeleteMe);
    }

    return iRet;
}
int CStrengur::insert(int iStart, const char *strInsertMe)
{
    return  insert(m_strengur, iStart, strInsertMe);
}
//returns the length of the new strSource string
int CStrengur::insert(char * strSource, int iStart, const char *strInsertMe)
{
    int iSourceLen=len(strSource),
        iInsertLen=len(strInsertMe),
        iNewLength=iSourceLen+iInsertLen,
        i;
    if (iInsertLen<1)
        return iSourceLen;
    for(i=iNewLength;i>iStart;i--)
        strSource[i]=strSource[i-iInsertLen];
    for(i=iStart;i<iStart+iInsertLen;i++)
        strSource[i]=strInsertMe[i-iStart];
    return iNewLength;
}
bool CStrengur::del(int iStart, int iLength)
{
    return  del(m_strengur, iStart, iLength);
}
//returns true if deleted
//returns false if not deleted
bool CStrengur::del(char * strSource, int iStart, int iLength)
{
    int strLen=len(strSource),
        i=iStart;
    if (iStart>strLen-1)
        return false;

    if (iLength>strLen-iStart)
        return left(iStart);

    while (strSource[i] != '\0')
    {
        strSource[i++] = strSource[i+iLength];
    }

    return true;
}
//returns 0 if nothing found
int CStrengur::find(const char * strFindMe)
{
        char *cFound;
        int i=0;
        cFound=find(m_strengur, strFindMe);
        if (0!=cFound)
                i=cFound-m_strengur;

        return i;

}
//returns 0 if nothing found
//Þessi skipun er ekki alveg rétt.
//prufaðu
//strSource "hæ þeemail=gudjon@undri.com\nttaa er textinn c=getini",//char * strBody,
//strFindMe "email="
char * CStrengur::find(const char * strSource, const char *strFindMe)
{
     int x=0,y,iFindLen;

     iFindLen=len(strFindMe);

     while(strSource[x]!='\0')
     {
        y=0;
        while((strSource[x+y]==strFindMe[y]) && (y<iFindLen) )
        {
            y++;
        }
        x+=y+1;
        if (y==iFindLen)
            return (char*)strSource+x-y-1;

     }
   return 0;
}
//return the index of the char in the string
//return -1 if char is not found

int CStrengur::pos(char cFindMe, unsigned int uiStartFrom)
{
     int x=uiStartFrom-1;

     if (x>Length()-1)
        return -1;

     while(m_strengur[++x]!='\0')
     {
        if (m_strengur[x]==cFindMe)
            return x;
     }
   return -1;
}

//return the index of the char in the string
//return -1 if char is not found
int CStrengur::posReverse(char cFindMe)
{
     int x=Length();

     while(--x>-1)
     {
        if (m_strengur[x]==cFindMe)
            return x;
     }
   return -1;
}
//return the index of the char in the string
//return -1 if char is not found
//return -2 if iIndexToSearchFrom is out of range
int CStrengur::posReverse(char cFindMe, int iIndexToSearchFrom)
{
     int x=iIndexToSearchFrom;
     if (x>Length())
        return -2;//Index out of range
     while(--x>-1)
     {
        if (m_strengur[x]==cFindMe)
            return x;
     }
   return -1;
}

//return the count of cFindMe in this string
int CStrengur::countChars(char cFindMe)
{
     int x=-1,
         iCount=0;
     while(m_strengur[++x]!='\0')
     {
        if (m_strengur[x]==cFindMe)
            iCount++;
     }
   return iCount;
}



//need insert and delete functions
int CStrengur::ncopy(char * strDestination, unsigned int uiStart, unsigned int uiCountToCopy)
{
        return ncopy(strDestination, m_strengur+uiStart, uiCountToCopy);
}
int CStrengur::ncopy(char * strSource, unsigned int uiCountToCopy)
{
    return  ncopy(m_strengur, strSource, uiCountToCopy);
}
//returns the number of bites copied
//note the function does not consern it self with '\0'
int CStrengur::ncopy(char * strDestination, char * strSource, unsigned int uiCountToCopy)
{
    if (!strDestination)
        return -1;
    if (!strSource)
    {
        strDestination[0]='\0';
        return 0;
    }

    unsigned int ui= 0;
    while (ui<uiCountToCopy && (strDestination[ui] = strSource[ui]) != '\0')
        ui++;

    return ui;
}

int CStrengur::ncat(char * strAddMe, unsigned int uiCountToCat)
{
    return  ncat(m_strengur, strAddMe, uiCountToCat);
}
//returns the number of bites cated
int CStrengur::ncat(char * strDestination, char * strAddMe, unsigned int uiCountToCat)
{
    if (!strDestination)
        return -1;
    if (!strAddMe)
        return 0;
    unsigned int ui = 0,
                 uj = 0;
    while (strDestination[ui] != '\0')
        ui++;

    while (uj<uiCountToCat && (strDestination[ui++] = strAddMe[uj++]) != '\0');

   if (uj>=uiCountToCat)
   {
        strDestination[ui]='\0';
        return ui;
   }
    else return len(strDestination);
}

void CStrengur::toLower()
{
    char *pStr=m_strengur;
    while(*pStr!='\0')
    {
        if (*pStr>('A'-1) && *pStr<('Z'+1))
            *pStr+=32;
        pStr++;
    }
}

void CStrengur::toUpper()
{
    char *pStr=m_strengur;
    while(*pStr!='\0')
    {
        if (*pStr>('a'-1) && *pStr<('z'+1))
            *pStr-=32;
        pStr++;
    }
}

//deletets all chars are right of iIndex;
bool CStrengur::left(int iIndex)
{
    if (iIndex>=MAX_STRLENGTH||iIndex<1 || iIndex>=Length())
        return false;
    m_strengur[iIndex]='\0';
    return true;
}
//deletets all chars are left of iIndex;
bool CStrengur::right(int iIndex)
{
    return del(0, iIndex);
}

//splits að path to a directory and filename
bool CStrengur::SplitPath( const char * strThePath,
                                 char * strDirectory,
                                 char * strFilename,
                                 char cSplit)
{
    CStrengur   cstr=strThePath,
                cstrDir,
                cstrFileName;


    int iPos=cstr.posReverse(cSplit);
    if (iPos<0)
        return false;

    cstrFileName=cstr;
    cstrFileName.del(0,iPos+1);
    cstrDir=cstr;
    cstrDir.left(iPos);
    int  iDir=copy(strDirectory, cstrDir.getString()),
         iFile=copy(strFilename,  cstrFileName.getString());


    return (iDir>0 && iFile>0);

}
//athugar hvort strengur hafi bara tolustafi
//ef strengur inniheldur bara númer þá er skilagildið true
//ef strengur er tómur þá er skilagildið false
//ef bMaVeraMinus er true þá leifir fallið tölunni að hafa '-' fremst í strengnum
//p.s. ekki er leift bil fremst í tölu
bool CStrengur::isNumber(bool bMaVeraMinus)
{
    return isNumber(m_strengur, bMaVeraMinus);
}
//athugar hvort strengur hafi bara tolustafi
//ef strengur inniheldur bara númer þá er skilagildið true
//ef strengur er tómur þá er skilagildið false
//ef bMaVeraMinus er true þá leifir fallið tölunni að hafa '-' fremst í strengnum
//p.s. ekki er leift bil fremst í tölu
bool CStrengur::isNumber(char *strNumer, bool bMaVeraMinus)
{

    if (!strNumer)
        return false;
    int i,
        iLen=len(strNumer);

    if (iLen<1)
        return false;
    if (bMaVeraMinus && strNumer[0]=='-')
        i=1;
    else
        i=0;
    for(i;i<iLen;i++)
    {
       if (strNumer[i]<'0' ||
            strNumer[i]>'9')
                return false;//það er að minstakosti 1 stafur í strengnum
    }
   return true;
}//bool CStrengur::ErNumer(char *strNumer, bool bMaVeraMinus)
//adds a char at the end.
int CStrengur::cat(char c)
{
	char Str[2]={c,'\0'};
	return cat(m_strengur, Str);
}
