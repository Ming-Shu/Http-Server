#define WEBSIZE 1024
#define RESPONSE "HTTP/1.0 200 OK\r\nContent-Type:text/html\r\n\r\n"
enum _CONNECT_CALSS{
	TCP_CONNECT=0,
	HTTP_CONNECT
};

int http_Check(char *msg);
char *StringAddr(char *msg);
void http_Msghandle(int fd,char* homepage,char* httpMsg);/*A homepage is first page name*/
