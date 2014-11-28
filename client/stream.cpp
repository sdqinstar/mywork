#include "common.h"
#include "string.h"


int stream_read(int fd) {
  int iRet;
  char *b = fdtabs[fd].cb[DIR_RD].buf;
  iRet = recv(fd, b, MAXBUFLEN, MSG_NOSIGNAL);
  if(iRet > 0) {
    printf("%s\n",b);
  } else if( iRet == 0) {
    printf("socket closed %d\n",errno);
	  fdtabs[fd].context->clean_up(fdtabs[fd].context);
	  return 0;
  } else if ( errno == EAGAIN) {
  	printf("what fuck!\n");
  } else {
    printf("r socket err:%d\n",errno);
    //shutdown(fd,SHUT_RDWR);
	  //close(fd);
  }
  struct epoll_event ev;
  ev.events = EPOLLOUT | EPOLLERR | EPOLLHUP;
  ev.data.fd = fd;

  iRet = epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&ev);
  if(iRet<0) {
    printf("err:%d\n",errno);
  return iRet;
}
  return 0;
}

int stream_write(int fd) {
  int iRet;
  char *b = fdtabs[fd].cb[DIR_WR].buf;
  strcpy(b,"hello dq\n");
  iRet = send(fd, b, strlen(b), MSG_DONTWAIT);
  if(iRet > 0) {
  
  } else if( iRet == 0 || errno == EAGAIN) {

  } else {
    printf("w socket err %d\n",errno);
  }
  struct epoll_event ev;
  ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
  ev.data.fd = fd;

  iRet = epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&ev);
  if(iRet<0) {
    printf("err:%d\n",errno);
  }
  return 0;

}
/*
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
*/





