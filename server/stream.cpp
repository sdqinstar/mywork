#include "common.h"
#include "string.h"


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
	return 0;
  }
  fdtabs[fd].qtask.state=RUNNING;
  return 0;
}

int stream_write(int fd) {
  int iRet;
  char *b = fdtabs[fd].cb[DIR_WR].buf;
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

int stream_accept(int fd) {
  int iRet;
  int cfd;
  struct sockaddr_storage addr;
  socklen_t laddr = sizeof(addr);
  printf("accpet\n");
  
  cfd = accept(fd, (struct sockaddr *)&addr, &laddr);
  fdtabs[cfd].fd = cfd;
  fdtabs[cfd].status = SC_CONN;
  fdtabs[cfd].cb[DIR_RD].f = stream_read;
  fdtabs[cfd].cb[DIR_WR].f = stream_write;
  
  struct session *s = new session;
  fdtabs[cfd].cb[DIR_RD].buf = s->req;
  fdtabs[cfd].cb[DIR_WR].buf = s->rep;
  s->fd=cfd;
  
  fdtabs[cfd].qtask.process = process_session;
  fdtabs[cfd].qtask.context = s;
  
  struct epoll_event ev;
  ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
  ev.data.fd = cfd;
 
  iRet = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,cfd,&ev);
  if(iRet<0) {
    printf("err:%d\n",errno);
	return iRet;
  }
  
  list_insert_head(task,&fdtabs[cfd].qtask.qlist);
  
}





