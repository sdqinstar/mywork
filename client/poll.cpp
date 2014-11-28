#include "common.h"
struct epoll_event epoll_events[MAXEPOLLSIZE];


int do_init() {
  fd_queue = new queue;
  fd_queue->tail=fd_queue->head = NULL;
  epoll_fd = epoll_create(MAXEPOLLSIZE);
  if(epoll_fd < 0) {
    printf("err:%d\n",errno);
    return -1;
  }
  return 0 ;  
}

int do_poll() {
  int status = 0;
  int count = 0;
  int fd;
  
  while(-1!=(fd=pop(fd_queue))) {
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
    ev.data.fd = fd;
 
    int iRet = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev);
    if(iRet<0) {
      printf("err:%d\n",errno);
	  return iRet;
	}
  }
    
  status = epoll_wait(epoll_fd, epoll_events, 10, 10000);
  for(count=0; count < status; count++ ) {
    int e = epoll_events[count].events;
    fd = epoll_events[count].data.fd;
	
	if (e & (FD_POLL_IN|FD_POLL_HUP|FD_POLL_ERR)) {
	  fdtabs[fd].cb[DIR_RD].f(fd);
	} else if(e & (FD_POLL_OUT|FD_POLL_ERR)) {
	  fdtabs[fd].cb[DIR_WR].f(fd);
	}
  }  
  
}

int do_set(int fd) {
  push(fd, fd_queue);
}






