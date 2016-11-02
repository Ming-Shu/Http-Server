/* Copyright (c) 2016,Ming-Shu Wu
 * 
 * This is a sample code to implementations of Web server in C.
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation
 * (Software) available for public use and benefit with the expectation
 * that others will use, modify and enhance the Software and contribute
 * those enhancements back to the community. However, since we would
 * like to make the Software available for broadest use, with as few
 * restrictions as possible permission is hereby granted, free of
 * charge, to any person obtaining a copy of this Software to deal in
 * the Software under the copyrights without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>	/*for open*/
#include <unistd.h>	/*for close*/
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include "tcp_socket.h"
#include "simple_WebServer.h"

int http_Check(char *msg)
{
	char tmp[5]={0};
	int a;
	for(a=0;a<5;a++,msg++)
		tmp[a]=*msg;
	if((strncmp(tmp,"GET /",5)==0)||(strncmp(tmp,"POST ",5)==0))
		return HTTP_CONNECT;
	return TCP_CONNECT;
}//http_check

char *StringAddr(char *msg)
{
	while(*msg++ !=' ');
	return (msg+1);/*msg is empty of next,+1 is the next after next*/
} 

void http_Msghandle(int fd,char* homepage,char* httpMsg)
{
	char response[] = RESPONSE;		
	char tmp[20]={0};
	char * ptr1,*ptr2;
	int read_len,file_fd,len,a;
		//printf("httpMsg:%s\n",httpMsg);
	ptr1 = StringAddr(httpMsg);
	ptr2 = StringAddr(ptr1);
	len = ptr2-ptr1-2;
		//printf("ptr1:%c,ptr2:%c,len:%d\n",*ptr1,*ptr2,len);
	for(a=0;a<len;a++,ptr1++)
		tmp[a]=*ptr1;
	if(a=write(fd,response,strlen(response))<0)
		exit(1);

	if(strcmp(tmp,"")!=0)
		homepage = tmp ;
	
	if((file_fd=open(homepage,O_RDONLY))==-1)
		exit(1);

	while ((read_len=read(file_fd,httpMsg, WEBSIZE))>0) 
		write(fd,httpMsg,read_len);
}

int main(void)
{
	int tcp_fd,tcp_clifd;
	unsigned char tcpbuf[WEBSIZE]={0};
	size_t tcpbuf_len=sizeof(tcpbuf);

	tcp_fd = createTCP_listener("home/pi/simple-Web-server",80);
	while(1)
	{
		tcp_clifd = getCli_fd(tcp_fd);
		if(recv(tcp_clifd,tcpbuf,tcpbuf_len, 0)<0)
			exit(1);
		if(http_Check(tcpbuf)==HTTP_CONNECT)
			 http_Msghandle(tcp_clifd,"index.html",tcpbuf);
		else
			printf("Receive Message from tcp:%s\n",tcpbuf);

	//	close(tcp_fd);
	}
	return 0;
}
