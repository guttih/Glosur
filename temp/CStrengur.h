//strengur.h
//fyrir Visual Studio 8
//if you want the MAX_STRING LENGTH to be more than
//1024 then #define MAX_STRLENGTH nnnn and then include the .h file


//To use this class in a .Net Environment you could do it like this:
//CStrengur cstr="Hello .net world";
//String^ str = gcnew String(cstr.getString());
#ifndef CSTRENGUR
#define CSTRENGUR
#ifndef MAX_STRLENGTH
#define MAX_STRLENGTH 1024
#endif

//#include <iostream.h>  //if you are not using iostream operators << and >> and not using operator = (int i) comment this line out

class CStrengur
{
public:
                 CStrengur  ();
                 CStrengur  (const char *pStrengur);
    void         set        (unsigned long ul);
    int          Length     ()      {return len(m_strengur);}
    bool         left       (int iIndex);
    bool         right      (int iIndex);
    bool         del        (int iStart, int iLength);
    int          insert     (int iStart, const char *strInsertMe);
    unsigned int replace    (const char * strDeleteMe, const char * strInsertMe, unsigned int uiHowManyReplacements=-1);
    unsigned int replace(char * strSource, const char * strDeleteMe, const char * strInsertMe, unsigned int uHowManyReplacements=-1);    
    char *       find       (const char * strSource, const char *strFindMe);
    int          countChars (char cCountMe);
    int          pos        (char cFindMe, unsigned int uiStartFrom=0);
    int          posReverse (char cFindMe);
    int          posReverse(char cFindMe, int iIndexToSearchFrom);
    char *       getString  ()      {return m_strengur;};
    int          ncopy      (char * strSource, unsigned int uiCountToCopy);
    int          ncopy      (char * strDestination, unsigned int uiStart, unsigned int uiCountToCopy);
    int          ncat       (char * strAddMe, unsigned int uiCountToCat);
    unsigned long toULong   ();
    long         toLong    ();
    double       toDouble   ();
    void         toLower();
    void         toUpper();
    CStrengur    operator = (const CStrengur a);
    CStrengur    operator = (const char *pStr);
    CStrengur    operator+= (const CStrengur a);
    CStrengur    operator+= (const char *pStr);
    CStrengur    operator+= (unsigned long ul);
    CStrengur    operator= (unsigned long ul);
    CStrengur    operator = (int i);
    CStrengur    operator = (unsigned int  ui);
    CStrengur    operator = (double d);

    int          operator== (const CStrengur a);
    int          operator >(const CStrengur a);
    int          operator <(const CStrengur a);
    int          operator== (const char *pStr);
    int         operator != (const char *pStr);

    CStrengur    operator-= (const CStrengur a);
    CStrengur    operator-= (const char *pStr);

    CStrengur    operator - (const CStrengur a);
    CStrengur    operator - (const char *pStr);

    CStrengur    operator + (const CStrengur a);
    CStrengur    operator + (const char *pStr);
    bool         SplitPath( const char * strThePath,
                          char * strDirectory,
                          char * strFilename,
                          char cSplit='\\');
    int          find(const char * strFindMe);
    bool         isNumber(bool bMaVeraMinus);
	int			cat(char c);
private:
    char         m_strengur[MAX_STRLENGTH];
    int          set     (const char *pStrengur);
    int          copy    (char *pStrDest, const char *pStrSource);
    int          cat     (char * pStr1, const char * pStrAddMe);
    int          compare (const CStrengur a, const CStrengur b);
    int          len     (const char * pStr);
    int          insert  (char * strSource, int iStart, const char *strInsertMe);
    bool         del     (char * strSource, int iStart, int iLength);
    int          ncopy   (char * strDestination, char * strSource, unsigned int uiCountToCopy);
    int          ncat    (char * strDestination, char * strAddMe, unsigned int uiCountToCat);
    bool         isNumber(char *strNumer, bool bMaVeraMinus);

};

#endif
