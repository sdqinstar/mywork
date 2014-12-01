#include "common.h"

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
  
  fdtabs[s->fd].epoll = EPOLLOUT | EPOLLERR | EPOLLHUP;
  fdtabs[s->fd].pollflag = EPOLL_CTL_MOD;
  list_insert_head(fdlist,&fdtabs[s->fd].qlist);
  
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





