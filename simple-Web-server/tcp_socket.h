#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

int createTCP_listener(char *folder_path,int socket_port);
int getCli_fd(int svr_fd);

#endif
