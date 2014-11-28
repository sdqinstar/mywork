#include "common.h"
struct epoll_event epoll_events[MAXEPOLLSIZE];


int do_init() {
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
    
  status = epoll_wait(epoll_fd, epoll_events, 10, -1);
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







