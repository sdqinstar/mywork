#include "common.h"
#include "string.h"


void clean_up(int fd) {
  struct session *s=(struct session*)fdtabs[fd].qtask.context;
  delete s;
  close(fd);  
}

int stream_read(int fd) {
  int iRet;
  char *b = fdtabs[fd].cb[DIR_RD].buf;
  iRet = recv(fd, b, MAXBUFLEN, MSG_NOSIGNAL);
  if(iRet > 0) {
    printf("%s\n",b);
  } else if( iRet == 0) {
    printf("socket closed\n");
	clean_up(fd);
  } else if ( errno == EAGAIN) {
  
  } else {
    printf("r socket err:%d\n",errno);
	clean_up(fd);
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
	clean_up(fd);
  }
  
  fdtabs[fd].ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
  fdtabs[fd].ev.data.fd = fd;
  fdtabs[fd].pollflag = EPOLL_CTL_MOD;
  list_insert_head(fdlist,&fdtabs[fd].qlist);
  
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
  
  fdtabs[cfd].ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
  fdtabs[cfd].ev.data.fd = cfd;
  fdtabs[cfd].pollflag = EPOLL_CTL_ADD;
  list_insert_head(fdlist,&fdtabs[cfd].qlist);
 

  
  list_insert_head(task,&fdtabs[cfd].qtask.qlist);
  
}





