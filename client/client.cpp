#include<string.h>
#include <fcntl.h>
#include <stdlib.h>
#include<sys/wait.h>
#include "common.h"

bool daemon_init()
{
	pid_t pid;
	if( (pid = fork() ) < 0 )
		return false;
	else if(pid > 0 ) {
		waitpid(-1,NULL,0);
	}	
	setsid();

	chdir(".");
	umask(0);
	
	return true;
}


struct iocont* cli_cont=NULL;
const int one = 1;

int cli_connect(const char * addr, int port) {
  int cfd;  
  struct sockaddr_in remote_addr; //服务器端网络地址结构体  
  memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零  
  remote_addr.sin_family=AF_INET; //设置为IP通信  
  remote_addr.sin_addr.s_addr=inet_addr(addr);//服务器IP地址  
  remote_addr.sin_port=htons(port); //服务器端口号  
	
/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
  if((cfd=socket(PF_INET,SOCK_STREAM,0))<0) {  
    perror("socket");
    return 1;
  }
  
  if((fcntl(cfd, F_SETFL, O_NONBLOCK)==-1) || (setsockopt(cfd, IPPROTO_TCP, 1, (char *) &one, sizeof(one)) == -1)) {
    printf("Cannot set client socket to non blocking mode.\n");
    close(cfd);
    return 1;
  }
 

    /*将套接字绑定到服务器的网络地址上*/  
  if(connect(cfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)  
  {  
	  if((errno != EINPROGRESS) && (errno != EALREADY) && (errno != EISCONN)) {
	
	    if (errno == EAGAIN || errno == EADDRINUSE) {
	         char *msg;
	         if (errno == EAGAIN) /* no free ports left, try again later */
	              msg = "no free ports";
	         else
	              msg = "local address already in use";
	
	         printf("Cannot connect: %s.\n",msg);
	         close(cfd);
	         return 1;
	    } else if (errno == ETIMEDOUT) {
	         //qfprintf(stderr,"Connect(): ETIMEDOUT");
	         close(cfd);
	         return 1;
	    } else {
	         // (errno == ECONNREFUSED || errno == ENETUNREACH || errno == EACCES || errno == EPERM)
	         //qfprintf(stderr,"Connect(): %d", errno);
	         close(cfd);
	         return 1;
	    }
	  }
  }  

  cli_cont->stat = SC_CONN;
  cli_cont->clean_up = clean;
  cli_cont->fd=cfd;

  fdtabs[cfd].context = cli_cont;
  fdtabs[cfd].cb[DIR_RD].f = stream_read;
  fdtabs[cfd].cb[DIR_WR].f = stream_write;
  
  
  struct epoll_event ev;
  ev.events = EPOLLOUT | EPOLLERR | EPOLLHUP;
  ev.data.fd = cfd;
 
  int iRet = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,cfd,&ev);
  if(iRet<0) {
    printf("err:%d\n",errno);
  }  
  return 0;
      	
}

void check() {
  if(cli_cont->stat != SC_CONN)
    cli_connect("127.0.0.1",9000);
}

int main(int argc, char *argv[]) {
	do_init();
	
	cli_cont = new iocont;
	
	int iRet;
  iRet = cli_connect("127.0.0.1",9000);
  if(iRet!=0) {
    return 1;
  }	
  daemon_init();
  while(1) {
    check();
    usleep(100);
	  do_poll();
  }
	
}






