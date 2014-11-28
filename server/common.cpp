#include "common.h"

int epoll_fd = 0;
queue *fd_queue = NULL;
struct fdtab fdtabs[MAXEPOLLSIZE];

void clean(struct iocont *p) {
  close(p->fd);
  p->stat = SC_CLOSED;
  printf("clean over\n");
}




