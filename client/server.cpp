#include<string.h>
#include "common.h"

int main(int argc, char *argv[]) {
  int sfd;//服务器端套接字
  struct sockaddr_in my_addr;   //服务器网络地址结构体

  memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零
  my_addr.sin_family=AF_INET; //设置为IP通信
  my_addr.sin_addr.s_addr=INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上
  my_addr.sin_port=htons(9000); //服务器端口号

/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
  if((sfd=socket(PF_INET,SOCK_STREAM,0))<0) {  
    perror("socket");
    return 1;
  }

/*将套接字绑定到服务器的网络地址上*/
  if (bind(sfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0) {
    perror("bind");
    return 1;
  }

  listen(sfd,5);

  fdtabs[sfd].fd = sfd;
  fdtabs[sfd].status = SC_CONN;
  fdtabs[sfd].cb[DIR_RD].f = stream_accept;
  fdtabs[sfd].cb[DIR_WR].f = NULL;
  
  do_init();
  do_set(sfd);
  
  while(1) {
    do_poll();
  }
	
}






