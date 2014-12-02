#include "common.h"


int stream_read(int fd) {
  int iRet;
  char *b = fdtabs[fd].cb[DIR_RD].buf;
  iRet = recv(fd, b, MAXBUFLEN, MSG_NOSIGNAL);
  if(iRet > 0) {
    printf("%s\n",b);
  } else if( iRet == 0) {
    printf("socket closed\n");
	close(fd);
  } else if ( errno == EAGAIN) {
  
  } else {
    printf("r socket err:%d\n",errno);
	close(fd);
  }
  return 0;
}

int stream_write(int fd) {
  int iRet;
  char *b = fdtabs[fd].cb[DIR_WR].buf;
  iRet = send(fd, b, MAXBUFLEN, MSG_DONTWAIT);
  if(iRet > 0) {
  
  } else if( iRet == 0 || errno == EAGAIN) {

  } else {
    printf("w socket err %d\n",errno);
  }

}

int stream_accept(int fd) {
  int iRet;
  int cfd;
  struct sockaddr_storage addr;
  socklen_t laddr = sizeof(addr);
  
  cfd = accept(fd, (struct sockaddr *)&addr, &laddr);
  fdtabs[cfd].fd = cfd;
  fdtabs[cfd].status = SC_CONN;
  fdtabs[cfd].cb[DIR_RD].f = stream_read;
  fdtabs[cfd].cb[DIR_WR].f = stream_write;
  do_set(cfd);
  
}





