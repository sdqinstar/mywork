#include "common.h"

int epoll_fd = 0;
struct fdtab fdtabs[MAXEPOLLSIZE];
struct list *task=NULL;
struct list *fdlist=NULL;
extern struct list* pllist=NULL;
extern struct pool* gpool=NULL;




