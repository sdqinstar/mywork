#include "common.h"

int epoll_fd = 0;
queue *fd_queue = NULL;
struct fdtab fdtabs[MAXEPOLLSIZE];




