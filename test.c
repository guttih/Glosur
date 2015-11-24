/* http server
  Group: gudjon02, jons13, snaevar13
  Please note that Marcel Kyas told us not to delete
  the debug print commands, because they will help the T.A's
*/

#include <assert.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <time.h> // For Date
#include <ctype.h> // For isdigit()
#include <stdio.h>
#include <time.h>
#include <string.h>  // For strstr()
#include <stdlib.h> // To quiet malloc and exit warnings warnings.

#include "glist.h"

#define LOGFILE             "http.log" /*The name of the file we will be logging to*/
#define MAX_NAMEVALUE_SIZE  512        /*Maximum value we will be allowing in a query url*/
#define MAX_CONNECTIONS     6          /*Maximum paraell connections we will be allowing*/
#define CONNECTION_TIMEOUT  30         /*If no data is sent to a keep-alive connetion then we close it after this time*/


typedef enum {
    HEAD, GET, POST, REQUEST_ERROR
} REQUEST_METHOD;

/*possible values for the getQueryValue function*/
typedef enum {
    FIRST_VALUE, NEXT_VALUE
} ENUMPARAM;




/*Possible pages we will be serving*/
typedef enum{
    PAGE_COLOR,
    PAGE_QUERY,
    PAGE_INDEX
} PAGES;


/*The url of the pages we will be searching for*/
static const char *PAGE_STRINGS[] = {
    "GET /color",
    "GET /query?",
    "GET /",
    "",
};

/*HTTP status codes, but we only use STATUS_OK*/
typedef enum{
    STATUS_OK         = 200, /*200's are used for successful requests.*/
    STATUS_REDIRECTION= 300, /*300's are for redirections.*/
    STATUS_PROBLEM    = 400, /*400's are used if there was a problem with the request.*/
    STATUS_NOTFOUND   = 404  /*500's are used if there was a problem with the server.*/
} HTTPStatusCode;

//responce functions
REQUEST_METHOD ParseHeader(const char *message);
int writeHeadRequest(int connfd, HTTPStatusCode statusCode, CONN_TYPE connType);
int writeRequestIndex(struct sockaddr_in address, int connfd, const char *message, int messageLength, HTTPStatusCode statusCode);
int writeRequestColor(int connfd, const char *message, int messageLength, HTTPStatusCode statusCode);
int writeRequestQuery(int connfd, const char *message, int messageLength, HTTPStatusCode statusCode);
int writePostRequest(int connfd, const char *message, int messageLength, HTTPStatusCode statusCode, const char *post_DATA);

//various functions
int portStrToInt(const char *str);
void help(char *argv[]);
void error(const char *msg);
int toInteger(const char *numStr);
int openSocket(struct sockaddr_in *server, int portNumber);
void logRequest(struct sockaddr_in address, const char *message, size_t lengthOfMessage, int responseCode);
void logLine(const char *message);
CONN_TYPE isKeepAlive(const char *message, int messageLength);
void closeConnection(int connfd);

//functions which allocate memory on the heap, and need free to free the memory again.
char *mallocNullTerminateAndCopy(const char *src, int srcLen);
char *mallocAndJoin2(const char *str1, const char *str2, unsigned int uiAllocateAdditionally);
char *mallocAndJoin3(const char *str1, const char *str2, const char *str3, unsigned int uiAllocateAdditionally);
char *mallocAndGetUrl(const char *message, int messageLength);
char *mallocMessage(const char *strHeader, const char *strData);
char *mallocPage(const char *strColor, const char *bodyPart);
char *mallocHead(HTTPStatusCode statusCode, size_t contentLength, const char *cookieName, const char *cookieValue, CONN_TYPE connType);
char* mallocParsePOST_DATA(const char *message);
char *mallocQueryTable(const char *strUrl);

//function for parsing strings
char *getTokenWithMultiEndTokens(const char *message, int messageLength, const char *startToken, const char *endToken, int *tokenLength);
char *getQueryValue(ENUMPARAM firstOrNext, const char *url, char *strName, int sizeOfName, char *strValue, int sizeOfValue);
char *getUrl(const char *message, int messageLength, int *urlLength);
char *getToken(const char *message, int messageLength, const char *startToken, const char *endToken, int *tokenLength);
char *getCookieValue(const char *message, const char *cookieName, char *cookieValue, int maxValueSize);
PAGES getPage(const char *message, int messageLength);

int main(int argc, char **argv)
{
    char *delMe;
    int sockfd;
    struct sockaddr_in server, client;
    char message[512];
    int serverPort;
    Node *pNode = NULL;
     if (argc < 2)
        help(argv);

    serverPort = portStrToInt(argv[1]);
    if (serverPort < 0)
        help(argv);

    printf("%d\n", serverPort);

    // Before we can accept messages, we have to listen to the port. We allow one connection to queue for simplicity.
    sockfd = openSocket(&server, serverPort);

    listen(sockfd, 1);

    for (;;)
    {
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Check whether there is data on the socket fd. */
        FD_ZERO(&rfds);
        FD_SET(sockfd, &rfds);

        /* Wait for five seconds. */
        tv.tv_sec = CONNECTION_TIMEOUT;
        tv.tv_usec = 0;

        int wait = listGetMax();
        if (sockfd > wait )
            wait = sockfd;
        printf("before select %d\n", wait);
        retval = select(wait + 1, &rfds, NULL, NULL, &tv);
        printf("after select\n");
        if (retval == -1)
        {   // select() failed.
            perror("select()");
        }
        else if (retval > 0)
        {   /* select() succeeded.
               Data is available, receive it. */
            assert(FD_ISSET(sockfd, &rfds));

            /* Copy to len, since recvfrom may change it. */
            socklen_t len = (socklen_t) sizeof(client);

            /* For TCP connectios, we first have to accept. */
            int connfd;
            printf("before accept\n");
            connfd = accept(sockfd, (struct sockaddr *) &client, &len);
            printf("after accept conn %d\n", connfd);
            pNode = listFindSecondsPassed(CONNECTION_TIMEOUT, connfd);
            while(pNode){
                //this connection has been idle for 30 seconds or more, let's close it.
                //To free up connections for other incomming connections
                closeConnection(pNode->connfd);
                listRemove(pNode);
                pNode = listFindSecondsPassed(CONNECTION_TIMEOUT, connfd);
            }

            if (listCount() >= MAX_CONNECTIONS)
            {   //closing all connections, because we will not server more at
                printf("listCount() >= MAX_CONNECTIONS : ");
                closeConnection(connfd);
            }
            else
            {
                //adds a new node to the connection list, and records the time of the add
                //if the connection was aready in the list then only current time is set in the node
                pNode = listAddOrSet(connfd);

                /* Receive one byte less than declared, because it will be zero-termianted below. */
                size_t n = read(connfd, message, sizeof(message) - 1);
                if (n < 1)
                    pNode->keepAlive = CONN_CLOSE;
                else
                    pNode->keepAlive = isKeepAlive(message, n);

                PAGES page = getPage(message, n);
                /* Handle requests. */
                if (n > 0)
                {
                    switch(ParseHeader(message))
                    {

                        case GET:
                            switch(page)
                            {
                                case PAGE_QUERY :
                                            if (writeRequestQuery(connfd, message, n, STATUS_OK) < 0)
                                                error("writeRequestQuery() error");
                                            break;

                                case PAGE_COLOR :
                                            printf("before PAGE_COLOR writeRequestColor\n");
                                            if (writeRequestColor(connfd, message, n, STATUS_OK) < 0)
                                                error("writeRequestColor() error");
                                            printf("after PAGE_COLOR writeRequestColor\n");
                                            break;

                                default :
                                            if (writeRequestIndex(client, connfd, message, n, STATUS_OK) < 0)
                                                error("writeRequestIndex() error");
                                            break;

                            }//switch(page)
                        break;
                        case POST:
                                if ((delMe = mallocParsePOST_DATA(message)) == NULL)
                                {
                                    error("mallocParsePOST_DATA() error");
                                }
                                if (writePostRequest(connfd, message, n, STATUS_OK, delMe) < 0)
                                {
                                    error("postRequest() error");
                                }
                                if (delMe)
                                {
                                    free(delMe);
                                }
                        break;
                        case HEAD:
                            if(writeHeadRequest(connfd, STATUS_OK, isKeepAlive(message, n)) < 0)
                            {
                                error("writeHeadRequest() error");
                            }
                        break;
                        default:

                        break;
                    }
                    logRequest(client, message, n, 200);
                }

                /* We should close the connection. */
                pNode = listFind(connfd);
                if (pNode->keepAlive == CONN_CLOSE)
                {
                    printf("pNode->keepAlive != 1: ");
                    closeConnection(connfd);
                    listDelete(connfd);
                }

                /* Zero terminate the message, otherwise printf may access memory outside of the string. */
                message[n] = '\0';

                /* Print the message to stdout and flush. */
                fprintf(stdout, "Received:\n%s\n", message);
                fflush(stdout);
            }//the else for  if (listCount() >= MAX_CONNECTIONS)
        }
        // If select() timeouts.
        else
        {   //close all open connections
            Node *curr = listHead;
            while(curr != NULL)
            {
                closeConnection(curr->connfd);
                listRemove(listHead);
                curr = listHead;
            }
            //fprintf(stdout, "No message in some seconds.\n",);fflush(stdout);
        }
    }
}

/* Parses the header of our request. */
REQUEST_METHOD ParseHeader(const char *message)
{
    char type[4] = "";
    strncpy(type, message, 4);

    /* GET request. */
    if (strncmp(type, "GET", 3) == 0)
    {
        return GET; //printf("GET \n");
    }
    /* POST request. */
    else if (strncmp(type, "POST", 4) == 0)
    {
        return POST;//printf("POST \n");
    }
    /* HEAD request. */
    else if (strncmp(type, "HEAD", 4) == 0)
    {
        return HEAD; //printf("HEAD \n");
    }

    return REQUEST_ERROR;
    //fflush(stdout);
}

//prints a descriptive error message to stderr. First the string str is printed, followed by a colon then a space.
void error(const char *msg){
    perror(msg);
    exit(1);
}

//opens a new local socket and returns the newly opened socked
//if an error occurs then the function returns the halts the program.
int openSocket(struct sockaddr_in *server, int portNumber)
{
    int sock, length;
    //socket(   : creates an endpoint for communication and returns a descriptor.
    //AF_INET   : the address family Internet Protocol address.
    //SOCK_DGRAM: Supports datagrams (connectionless, unreliable messages of a fixed maximum length). (UDP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        return sock;
    }

    length = sizeof(*server);
    memset(server, 0, length);
    //binding the server socket

    server->sin_family = AF_INET;            //internet protocol address
    server->sin_addr.s_addr=INADDR_ANY;    //the socket shall be bound to all local interfaces.
    server->sin_addr.s_addr = htonl(INADDR_ANY);
    server->sin_port=htons(portNumber); //htons converts the unsigned short integer hostshort from host byte order to network byte order.

    //bind - bind a name to a socket / assigning a name to a socket
    if(bind(sock, (struct sockaddr*)server, length) < 0)
    {
        error("Error when binding");
    }

    return sock;
}

//  converts a Ascii string number to an int number.
//  Higest possible number is 2147483647 and lowest is 0
//  returns -1 if numStr is not a positive string number.
int toInteger(const char *numStr)
{
    int len = (int) strlen(numStr), i, multiply = 1, number = 0;

    if(len > 10)
        return -1;  // invalid number

    for(i = len - 1; i > -1; i--)
    {
        if(!(numStr[i] >= '0' && numStr[i] <= '9'))
            return -1; // not a Askii number, input invalid

        number+= (multiply * (numStr[i] - 48)); // convert ascii char to digit.
        multiply *= 10; // up the multiplier by the power of
    }
    if (number < 0)
        return -1;

    return number;
}

void help(char *argv[])
{
    printf("Correct usage:\n   %s port_number\n", argv[0]);
    printf("Example:\n   %s 2000\n", argv[0]);
    exit(1);
}

//returns a port number if str contains a valid portnumber
int portStrToInt(const char *str)
{
    int port = toInteger(str);
    if (port > 1023 && port < 65536)
        return port;
    else
        return -1;
}

void logLine(const char *text){

    FILE *fp=stdout;
    fp = fopen(LOGFILE, "a");
    fprintf(fp, " %s\n", text);
    fclose(fp);
}

void logRequest(struct sockaddr_in address, const char *message, size_t lengthOfMessage, int responseCode)
{
    FILE *fp=stdout;
    int i, len;
    char *ptr;

    fp = fopen(LOGFILE, "a");

    if (fp == NULL)
    {
        printf("unable to write to LOGFILE");
        return;
    }

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    //timestamp : <client ip>:<client port> <request method> <requested URL> : <response code>
    fprintf(fp, "%d-%02d-%02dT%02d:%02d:%02d : ",
                timeinfo->tm_year + 1900,
                timeinfo->tm_mon + 1,
                timeinfo->tm_mday,
                timeinfo->tm_hour,
                timeinfo->tm_min,
                timeinfo->tm_sec);

    //ip address and port
    fprintf(fp, "%d.%d.%d.%d:%d ",
                  (int)(address.sin_addr.s_addr &0xFF),
                  (int)((address.sin_addr.s_addr&0xFF00)>>8),
                  (int)((address.sin_addr.s_addr&0xFF0000)>>16),
                  (int)((address.sin_addr.s_addr&0xFF000000)>>24),
                  htons(address.sin_port));

    //<request method>  print the request method
    switch(ParseHeader(message))
    {
        case GET : fprintf(fp,  "GET ");
                   break;
        case POST: fprintf(fp, "POST ");
                   break;
        case HEAD: fprintf(fp, "HEAD ");
                   break;
        default  : fprintf(fp, "Invalid request method ");
                   break;
    }

    ptr = getUrl(message, lengthOfMessage, &len);

    if (ptr != NULL)
    {
        for(i = 0; i<len; i++){
            fprintf(fp, "%c", ptr[i]);
        }
    }

    fprintf(fp, " %d\n", responseCode);
    fclose(fp);
}

//searches for where the url starts and returns a pointer to the location
//warning, this function does not return a null terminated string
char *getUrl(const char *message, int messageLength, int *urlLength)
{
    return getToken(message, messageLength, " ", " ", urlLength);
}

/*
 Searches for a url in a message, copies it to a new buffer and returns it
 returns:
    fail   : NULL
    success: An allocated buffer containing the url
 remember to free the allocated buffer after use.
 */
char *mallocAndGetUrl(const char *message, int messageLength){

    char *pUrl;
    int urlLength;
    pUrl = getUrl(message, messageLength, &urlLength);
    pUrl = mallocNullTerminateAndCopy(pUrl, urlLength);

    return pUrl;
}

//searches for string between startToken and endToken
//warning, this function does not return a null terminated string
//the function assumes that startToken and endTokens are nullterminated strings, so be warned.
char *getToken(const char *message, int messageLength, const char *startToken, const char *endToken, int *tokenLength){

    if (startToken == NULL || endToken == NULL || message == NULL )
        return NULL;

    char *ptr, *ptrEnd;
    int startTokenLen = strlen(startToken),
        endTokenLen   = strlen(endToken);

    if(startTokenLen < 1 || endTokenLen < 1)
     return NULL;
    //find the first token
    ptr = strstr(message, startToken);

    if (ptr == NULL)
        return NULL;

    ptr+=startTokenLen;

    if (ptr - message > messageLength)
        return NULL;//token out of bounds

    //find end token, but not search longer than messageLength.
    ptrEnd = strstr(ptr, endToken);

    if (ptrEnd == NULL )
        return NULL;

    if ((ptrEnd - message) > messageLength)
        return NULL; //out of message

    *tokenLength = ptrEnd - ptr;
    return ptr;
}

//searches for string between startToken and endToken, where endToken is an array of chars which are all candidates for a tokenEnd
//this function treats nullTermination as an endToken
//warning, this function does not return a null terminated string
//the function assumes that startToken and endTokens are nullterminated strings, so be warned.
char *getTokenWithMultiEndTokens(const char *message, int messageLength, const char *startToken, const char *endToken, int *tokenLength)
{
    if (startToken == NULL || endToken == NULL || message == NULL )
        return NULL;

    char *ptr;

    int i, t, len,
        startTokenLen = strlen(startToken),
        endTokenLen   = strlen(endToken);

    if(startTokenLen < 1 || endTokenLen < 1)
     return NULL;

    //find the first token
    ptr = strstr(message, startToken);

    if (ptr == NULL)
        return NULL;

    ptr+=startTokenLen;

    if (ptr - message > messageLength)
        return NULL;//token out of bounds

    //find end token, but not search longer than messageLength.
    len = messageLength - (ptr - message);
    for (i = 0; i < len+1; i++){

        if (ptr[i] == '\0'){ //todo: when time remove code dublication
                    //we found the terminator
                    *tokenLength = i;
                    return ptr;
        }
        for (t = 0; t < endTokenLen; t++){
            if (ptr[i] == endToken[t]){
                //we found the terminator
                *tokenLength = i;
                return ptr;
                }
        }
    }
    return NULL;
}

/*
mallocs a new buffer of the size srcLen + 1 and adds '\0' to the last char of the new buffer
remember to call free after using this new buffer.
Example:
    int len;
    char *ptr, *p;
    ptr = getUrl(message, lengthOfMessage, &len);
    p = mallocNullTerminateAndCopy(ptr, len);
    printf("\n%s\n", p);
    if (p != NULL)
        free(p);
*/
char *mallocNullTerminateAndCopy(const char *src, int srcLen)
{
    if (src == NULL)
    {
        return NULL;
    }

    int size = (sizeof(char) * srcLen);
    size +=sizeof(char) * src[srcLen]!='\0';  // If src is not nullterminated we will need to nullterminate and add an extra.

    char *ptr = (char *)(void *)malloc(size);
    if (ptr == NULL)
    {
        return NULL;  // No memory.
    }
    strncpy(ptr, src, srcLen);

    ptr[srcLen]='\0'; // To be sure.
    return ptr;
}

/* mallocAndJoin mallocs a new string and copies str1, str2 and str3
   Input:
   All provited strings must be null terminated.
   If str3 is NULL str3 will be ignored and str1 and str2 will be joined.
   uiAllocateAdditionally is usually 0.
   If you want to allocate more memory than is needed for for the joned and returned string
   you can spectify that number here.
   Returns:
            On fail: NULL
            On success: Pointer to a new allocated buffer, in wich input strings have been joined together.
   Remember to call free for the returned pointer
   Example: char *pp;
            pp = mallocAndJoin3("einn ", "tveir", " thrir", 0);
            int len = strlen(pp);
            pp[len]='X';
            pp[len+1]='\0';
            printf("\"%s\"\n", pp);
            free(pp);
            Output: "einn tveir thrir"
*/
char *mallocAndJoin3(const char *str1, const char *str2, const char *str3, unsigned int uiAllocateAdditionally)
{
    // We assume all is nullTerminated.
    if (str1 == NULL || str2 == NULL)
    {
        return NULL;
    }

    int str1Len = strlen(str1);
    int str2Len = strlen(str2);
    int str3Len = 0;
    if (str3)
    {
        str3Len = strlen(str3);
    }
    int strLen = str1Len + str2Len + str3Len + uiAllocateAdditionally + 1;

    int size = (sizeof(char) * strLen);
    char *ptr = (char *)malloc(size);
    if (ptr == NULL)
    {
        return NULL;  // No memory.
    }

    strcpy(ptr, str1);
    strcpy(ptr+str1Len, str2);
    if (str3)
    {
        strcpy(ptr + str1Len + str2Len, str3);
    }

    ptr[strLen]='\0'; // To be sure.
    return ptr;
}

/* example: char *pp;
            pp = mallocAndJoin2("fjorir ", "fimm",0);
            printf("\"%s\"\n", pp);
            free(pp);
            output: "fjorir fimm"
*/
char *mallocAndJoin2(const char *str1, const char *str2, unsigned int uiAllocateAdditionally)
{
    return mallocAndJoin3(str1, str2, NULL, uiAllocateAdditionally);
}

/* char * mallocHead(...) */
char * mallocMessage(const char *strHeader, const char *strData)
{
    return mallocAndJoin2(strHeader, strData, 0);
}

/* Creates the HTML page. */
char * mallocPage(const char *strColor, const char *bodyPart)
{
    char *pHead, *pMessage;

    pHead = mallocAndJoin3("<!doctype html>\n"
                           "<html lang=\"en\">\n"
                           "\t<head>\n"
                           "\t\t<meta charset=\"utf-8\">\n"
                           "\t\t<title>HTML 5</title>\n"
                           "\t</head>\n"
                           "\t<body style=\"background-color:",strColor,"\">\n\t\t", 0);
    pMessage = mallocAndJoin3(pHead, bodyPart,
                           "\n\t</body>\n"
                           "</html>\n", 0);
    if (pHead != NULL)
    {
        free(pHead);
    }

    return pMessage;
}

/* Creates the HTML head. */
char *mallocHead(HTTPStatusCode statusCode, size_t contentLength, const char *cookieName, const char *cookieValue, CONN_TYPE connType)
{
    char head[512];
    char strTime[80];
    char strConnType[]="keep-alive";
    time_t rawtime;
    struct tm * ti;
    time ( &rawtime );
    ti = localtime ( &rawtime );
    if (connType == CONN_CLOSE)
    {
        strcpy(strConnType, "close");
    }

    strftime(strTime,80,"%a, %d %b %Y %T %Z", ti);
    if (cookieName==NULL || cookieValue==NULL){
        sprintf(head,
               "HTTP / 1.1 %d OK\n"
               "Content-Type: text/html; charset=utf-8\n"
               "Date: %s\n"
               "Content-Length: %zu\n"
               "Connection: %s\r\n\r\n",
                statusCode,
                strTime,
                contentLength,
                strConnType);
    }
    else
    {
         sprintf(head,
               "HTTP / 1.1 %d OK\n"
               "Content-Type: text/html; charset=utf-8\n"
               "Date: %s\n"
               "Content-Length: %zu\n"
               "Set-Cookie: %s=%s\n"
               "Connection: %s\r\n\r\n",
                statusCode,
                strTime,
                contentLength,
                cookieName,
                cookieValue,
                strConnType);
    }

    return mallocNullTerminateAndCopy(head, strlen(head));
}

/* This function is run whenever we receive a GET request and it
 *  does not match /color or /query
 */
int writeRequestIndex(struct sockaddr_in address, int connfd, const char *message, int messageLength, HTTPStatusCode statusCode)
{   /*<|>*/
    char content[160],
        *pUrl=NULL,
        *ptr=NULL,
        *pHead=NULL,
        *pMessage=NULL;

    if (messageLength == 0 )
        return -1;

    pUrl = mallocAndGetUrl(message, messageLength);
    // Show the client ip address and port.
    sprintf(content, "%d.%d.%d.%d:%d", (int)( address.sin_addr.s_addr&0xFF),
                                       (int)((address.sin_addr.s_addr&0xFF00)>>8),
                                       (int)((address.sin_addr.s_addr&0xFF0000)>>16),
                                       (int)((address.sin_addr.s_addr&0xFF000000)>>24),
                                       htons( address.sin_port));

    // Adding the url to the content.
    ptr = mallocAndJoin2(content, pUrl, 0);
    if (pUrl)
    {
        free(pUrl);
        pUrl = NULL;
    }

    // Putting all the content to the htmlPage including a color attribute for the body.
    char *pPage;
    pPage = mallocPage("white", ptr);
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }

    // Creating a header with the 200 responce.
    pHead = mallocHead(statusCode, strlen(pPage), NULL, NULL, isKeepAlive(message, messageLength));
    pMessage = mallocMessage(pHead, pPage);
    if (pHead)
    {
        free(pHead);
        pHead = NULL;
    }
    if (pPage)
    {
        free(pPage);
        pPage = NULL;
    }

    int ret = write(connfd, pMessage, strlen(pMessage));
    if (pMessage)
    {
        free(pMessage);
        pMessage = NULL;
    }

    return ret;
}
//write response when page is GET /color
int writeRequestColor(int connfd, const char *message, int messageLength, HTTPStatusCode statusCode)
{   /*<|>*/
    char value[20],
         name[20],
         tmpValue[20],
        *pPage = NULL,
        *pHead = NULL,
        *pMessage = NULL,
        *pUrl = NULL,
        *pFind = NULL;

    if (messageLength == 0 )
        return -1;

    memset(name, 0, 20);
    memset(value, 0, 20);

    //default value
    strncpy(name, "bg", 2);
    strncpy(value, "white", 5);


    pUrl = mallocAndGetUrl(message, messageLength);

    if (pUrl == NULL)
        return -1;

        pFind = strstr(pUrl, "/color?bg=");

    if (pFind == pUrl)
    {
         // Does not copy an empty field.
        getQueryValue(FIRST_VALUE, pUrl,
                        name,     20,
                        value,    20);
    }
    else
    {
        if (getCookieValue(message, "bg", tmpValue, 20))
        {
            strcpy(value, tmpValue);
        }

    }

    // Putting all the content to the htmlPage including a color attribute for the body.
    pPage = mallocPage(value, "");
     if (pPage == NULL)
        return -1;

    // Creating a header with the 200 responce.
    pHead = mallocHead(statusCode, strlen(pPage), name, value, isKeepAlive(message, messageLength));
    if (pHead == NULL)
        return -1;

    pMessage = mallocMessage(pHead, pPage);

    if (pPage)
    {
        free(pPage);
        pPage = NULL;
    }

    if (pHead)
    {
        free(pHead);
        pHead = NULL;
    }

    int ret = write(connfd, pMessage, strlen(pMessage));
    if (pMessage)
    {
        free(pMessage);
    }

    return ret;
}

//write response when GET /query
int writeRequestQuery(int connfd, const char *message, int messageLength, HTTPStatusCode statusCode)
{   /*<|>*/
    char *pUrl,
         *pPage;

    if (message == NULL || messageLength == 0 )
        return -1;

    pUrl = mallocAndGetUrl(message, messageLength);

    // Extracting query from url and putting it into a html table
    char *ptr = mallocQueryTable(pUrl);
    if (pUrl)
    {
        free(pUrl);
    }

    // Putting all the content to the htmlPage including a color attribute for the body.
    pPage = mallocPage("white", ptr);
    if (ptr)
    {
        free(ptr);
    }

    // Creating a header with the 200 responce.
    char *pHead = mallocHead(statusCode, strlen(pPage), NULL, NULL, isKeepAlive(message, messageLength));
    char *pMessage = mallocMessage(pHead, pPage);

    if (pHead)
    {
        free(pHead);
    }
    if (pPage)
    {
        free(pPage);
    }

    int ret = write(connfd, pMessage, strlen(pMessage));
    if (pMessage)
    {
        free(pMessage);
    }

    return ret;
}

/* Fetches the data from a POST request. */
char *mallocParsePOST_DATA(const char *message)
{
    char *pFind = strstr(message, "Content-Length: ");
    size_t offset = strlen("Content-Length: ");
    if (pFind && strlen(pFind) > offset)
    {
        pFind += offset;

        int i = 0;
        while(isdigit(pFind[i]))
        {
            i++;
        }
        char retDataSize[i];

        i = 0;
        while(isdigit(pFind[i]))
        {
            retDataSize[i] = pFind[i];
            i++;
        }

        int size = toInteger(retDataSize);
        char retData[size];

        // Creating a pointer to where the DATA field starts.
        pFind = strstr(message, "\r\n\r\n");
        offset = strlen("\r\n\r\n");
        if (pFind && strlen(pFind) > offset)
        {   // Does not copy an empty field.
            pFind += offset;
            strncpy(retData, pFind, size);
        }

        return mallocNullTerminateAndCopy(retData, size);
    }

    return NULL;
}

/* This function is run whenever we receive a POST request. */
int writePostRequest(int connfd, const char* message, int messageLength, HTTPStatusCode statusCode, const char* post_DATA)
{   /*<|>*/
    char colorStr[20];

    memset(colorStr, 0, 20);
    strncpy(colorStr, "white", 7);

    char *pUrl = mallocAndGetUrl(message, messageLength);

    char *pFind = strstr(pUrl, "bg=");
    size_t offset = 3;
    if (pFind && strlen(pFind) > offset) // Does not copy an empty field.
    {
        pFind += offset;
        strncpy(colorStr, pFind, strlen(pFind)); // mallocAndGetUrl() returns a null terminated string.
    }

    // Putting all the content to the htmlPage including a color attribute for the body.
    char *pPage = mallocPage(colorStr, post_DATA);

    // Creating a header with the 200 response.
    char *pHead = mallocHead(statusCode, strlen(pPage), NULL, NULL, isKeepAlive(message, messageLength));
    char *pMessage = mallocMessage(pHead, pPage);

    if (pUrl)
    {
        free(pUrl);
        pUrl = NULL;
    }
    if (pHead)
    {
        free(pHead);
        pHead = NULL;
    }
    if (pPage)
    {
        free(pPage);
        pPage = NULL;
    }

    int retVal = write(connfd, pMessage, strlen(pMessage));
    if (pMessage)
    {
        free(pMessage);
        pMessage = NULL;
    }

    return retVal;
}

/* This function is run whenever we receive a HEAD request. */
int writeHeadRequest(int connfd, HTTPStatusCode statusCode, CONN_TYPE connType)
{
    char *pHead = mallocHead(statusCode, 0, NULL, NULL, connType); // Creating a header with the 200 responce.

    int ret = write(connfd, pHead, strlen(pHead));

    if(pHead)
    {
        free(pHead);
    }

    return ret;
}

/*  Searches for name and values in a query string
    returns a pointer to where we left off in the url,
    ready for the next call to getQueryValue
    url must be null terminated
    example on how to use:
            char name1[200],
                value1[200],
                *ptr,
                str[]="/?bg=xor&next=stuff&name3=val3&n4=v4&bull=buid";
            ptr = getQueryValue(FIRST_VALUE, str, name1, 3, value1, 4);
            while(ptr){
                printf("%s : %s\n", name1, value1);
                ptr = getQueryValue(NEXT_VALUE, ptr, name1, 200, value1, 200);
            }
*/
char* getQueryValue(ENUMPARAM firstOrNext, const char *url, char *strName, int sizeOfName, char *strValue, int sizeOfValue)
{
    char *ptrName, *ptrValue, *ptr;
    int lenName;
    int ptrLen, lenValue;
    int urlLen = strlen(url);

    if (firstOrNext == FIRST_VALUE)
        ptrName = getTokenWithMultiEndTokens(url, urlLen, "?", "=", &lenName);
    else
        ptrName = getTokenWithMultiEndTokens(url, urlLen, "&", "=", &lenName);


    if (!ptrName)
        return NULL; // No query string.

     if ( sizeOfName <= lenName)
        return NULL; // No space for the name in the destination buffer.

    // We got a name, let's get it's value.
    ptr = ptrName+lenName;
    ptrLen=strlen(ptr);

    ptrValue = getTokenWithMultiEndTokens(ptr, ptrLen, "=", "&", &lenValue);
    if (!ptrValue)
        return NULL; // No value in this name.

    if ( sizeOfValue <= lenValue)
        return NULL; // No space for the name in the destination buffer.


    strncpy(strName, ptrName, lenName);
    strName[lenName]='\0';

    strncpy(strValue, ptrValue, lenValue);
    strValue[lenValue]='\0';

    return ptrValue+lenValue;
}

//returns a html table which contains all names and values in a query string
char *mallocQueryTable(const char *strUrl)
{
    char name[MAX_NAMEVALUE_SIZE],
        value[MAX_NAMEVALUE_SIZE],
        head[] = "<table border=\"1\"><tr><th>Name</th><th>Value</th></tr>\n",
        foot[] = "</table>",
        row[MAX_NAMEVALUE_SIZE*2+(27+3)],
    *ptr,
    *ptrMalloc;
    int pairSize = 0,
        pairCount = 0,
        mallocSize;

    ptr = getQueryValue(FIRST_VALUE,strUrl,
                        name,       MAX_NAMEVALUE_SIZE,
                        value,      MAX_NAMEVALUE_SIZE);

    if (ptr == NULL)
        return NULL; //NOTHING TO DO, NOW PARAMS

    //get the data size and count of variables
    while(ptr){
        pairCount++;//how many pairs
        pairSize += strlen(name);
        pairSize += strlen(value);
        ptr = getQueryValue(NEXT_VALUE,ptr,
                            name,      MAX_NAMEVALUE_SIZE,
                            value,     MAX_NAMEVALUE_SIZE);
    }

    if (pairCount < 1)
        return NULL; //NOTHING TO DO, NOW PARAMS

    mallocSize = (28+2)*pairCount; //overhead for each pair
    mallocSize+=strlen(head)+strlen(foot);
    mallocSize+=pairSize;

    int size =sizeof(char) * mallocSize;  // If src is not nullterminated we will need to nullterminate and add an extra.

    ptrMalloc = (char *)(void *)malloc(size);
    if (ptrMalloc == NULL)
    {
        return NULL;  // No memory.
    }
    memset(ptrMalloc, 0, mallocSize);
    strcpy(ptrMalloc, head);

    ptr = getQueryValue(FIRST_VALUE,strUrl,
                        name,       MAX_NAMEVALUE_SIZE,
                        value,      MAX_NAMEVALUE_SIZE);


    while(ptr){
        sprintf(row, "<tr><td>%s</td><td>%s</td></tr>\n", name, value);
        strcat(ptrMalloc, row);
        ptr = getQueryValue(NEXT_VALUE,ptr,
                            name,      MAX_NAMEVALUE_SIZE,
                            value,     MAX_NAMEVALUE_SIZE);
    }

    strcat(ptrMalloc, foot);
    return ptrMalloc;
}

// Finds which page is being asked for.
PAGES getPage(const char *message, int messageLength)
{
    if (message == NULL || messageLength < 4 )
    {
        return PAGE_INDEX;
    }
    char *ptr;

    ptr = strstr(message, PAGE_STRINGS[PAGE_QUERY]);
    if (ptr == message) // Check if this is at start of the message.
    {
        return PAGE_QUERY;
    }

    ptr = strstr(message, PAGE_STRINGS[PAGE_COLOR]);
    if (ptr == message) // Check if this is at start of the message.
    {
        return PAGE_COLOR;
    }

    return PAGE_INDEX;
}

/* Returns CONN_KEEPALIVE when the HTTP Header contains no Connection field or when it contains Connection: keep-alive
   Returns CONN_CLOSE     when the HTTP Header contains Connection: close */
CONN_TYPE isKeepAlive(const char *message, int messageLength)
{
    char *pFind;
    int len;

    pFind = getTokenWithMultiEndTokens(message, messageLength, "Connection: ", " \r\n", &len);
    if (!pFind)
    {
        return CONN_KEEPALIVE;
    }
    if((strncmp(pFind, "close", 5)) == 0)
    {
        return CONN_CLOSE;
    }

    return CONN_KEEPALIVE;
}

//searches for a cookieName and returns it's value
char *getCookieValue(const char *message, const char *cookieName, char *cookieValue, int maxValueSize)
{
    int i,
        iLen = 0;
    char *pFind;

    pFind = strstr(message, "Cookie: ");
    if (!pFind)
    {
        return NULL;
    }
    pFind += strlen("Cookie: ");

    pFind = strstr(pFind, cookieName);
    if (!pFind)
    {
        return NULL;
    }
    pFind += strlen(cookieName);

    pFind = strstr(pFind, "=");
    if (!pFind)
    {
        return NULL;
    }
    pFind +=1;

    i = 0;
    while(i < maxValueSize)
    {
        if (pFind[i] == '\0' || pFind[i] == ' ' || pFind[i] == '\r' || pFind[i] == '\n')
        {
            iLen = i;
            break;
        }

        i++;
    }

    if (iLen +1 > maxValueSize)
    {
        return NULL;
    }

    if (iLen > 0)
    {
        for(i=0; i<iLen; i++){
            cookieValue[i]=pFind[i];
        }

        cookieValue[iLen]='\0';
        return cookieValue;
    }

    return NULL;
}

void closeConnection(int connfd)
{   printf("closing connection %d\n", connfd);
    shutdown(connfd, SHUT_RDWR);
    close(connfd);
}
