#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define FD_POLL_IN	0x01
#define FD_POLL_PRI	0x02
#define FD_POLL_OUT	0x04
#define FD_POLL_ERR	0x08
#define FD_POLL_HUP	0x10

#define MAXBUFLEN 16566
#define MAXEPOLLSIZE 65565


enum {
	SC_CONN=0,
	SC_CLOSED=1,
	SC_ERR
};


enum {
	DIR_RD=0,
	DIR_WR=1,
	DIR_SIZE
};



struct fdtab {
struct {
	int (*f)(int fd);            /* read/write function */
	char buf[MAXBUFLEN];            /* read/write buffer */
} cb[DIR_SIZE];
int fd;//socket
int status;//socket status
};



struct Node {
  int fd;
  struct Node* next;
};


typedef struct queue{
 struct Node * head, * tail; // 每个队列维护头/尾指针
}queue;


extern int epoll_fd;
extern queue *fd_queue;
extern struct fdtab fdtabs[MAXEPOLLSIZE];


extern int do_poll();
extern int do_init();
extern int do_set(int fd);
extern int stream_accept(int fd);
extern int stream_write(int fd);
extern int stream_read(int fd);
extern void push(int fd, queue *q);
extern int pop(queue *q);


#endif



