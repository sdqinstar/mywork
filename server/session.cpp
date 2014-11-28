#include "common.h"
#include "string.h"

int parse_cmd(char* buf, struct cmd *c) {
  char *p=NULL;
  p=strchr(buf,':');
  if(NULL == p)
    return 1;
  if(0==strcasecmp(p,"GET")) {
    c->cmd=1;
  } else if(0==strcasecmp(p,"SET")) {
    c->cmd=2;
  } else {
    c->cmd=-1;
  }
  return 0;
}


void process_session(struct task *t, int time) {
  int iRet;
  struct session *s = (struct session *)t->context;
  t->state = IDLE;
  struct epoll_event ev;
  ev.events = EPOLLOUT | EPOLLERR | EPOLLHUP;
  ev.data.fd = s->fd;

  iRet = epoll_ctl(epoll_fd,EPOLL_CTL_MOD, s->fd,&ev);
  if(iRet<0) {
    printf("err:%d\n",errno);
  }
  
  struct cmd c;
  iRet = parse_cmd(s->req,&c);
  if(iRet!=0) {
    goto ERR; 
  }
  
  switch(c.cmd) {
   case 1:
    strcpy(s->rep,"Get CMD\n");
	break;
   case 2:
    strcpy(s->rep,"SET CMD\n");
	break;
   default:
    strcpy(s->rep,"UNKNOWN CMD\n");
	break;
  }
  
ERR:
    strcpy(s->rep,"ERR CMD\n");
  
}





