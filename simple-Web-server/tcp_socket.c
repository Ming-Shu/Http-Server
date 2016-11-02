/*****************************************
 * This is part of Web-server.  	 *                 
 * Author:Ming-Shu Wu                    *
 * Date:2016                        	 *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h> 
#include "tcp_socket.h"

int createTCP_listener(char *folder_path,int socket_port)
{
	int sock_fd,flags=1;
	struct sockaddr_in svr_addr;

	/* open a socket */
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("opening socket failed");
		exit(EXIT_FAILURE);
	}

	/* setting the address */
	if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(int))<0){
		perror("setsockopt set error\n"); 
		exit(EXIT_FAILURE);
	} 
	
	bzero(&svr_addr,sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(socket_port);//if http port,is set to  80
	svr_addr.sin_addr.s_addr = INADDR_ANY;
	//inet_aton("192.168.1.66", &svr_addr.sin_addr);

	/* bind socket with addr */
	if (bind(sock_fd, (struct sockaddr*)&svr_addr, sizeof(svr_addr)) < 0)
	{
		perror("binding socket failed");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}

	/* listen fd */
	if (listen(sock_fd,5) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	return sock_fd;
}


int getCli_fd(int svr_fd)
{
	int cli_fd;
	struct sockaddr_in cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	if((cli_fd=accept(svr_fd,(struct sockaddr *) &cli_addr, &cli_len))<0)
		exit(EXIT_FAILURE);
	return cli_fd;
}

