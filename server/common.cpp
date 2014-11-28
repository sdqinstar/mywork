#include "common.h"

int epoll_fd = 0;
struct fdtab fdtabs[MAXEPOLLSIZE];
struct list *task=NULL;




