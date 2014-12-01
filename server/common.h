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
#include <stddef.h>
#include <stdlib.h>
#include "string.h"

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
	IDLE=0,
	RUNNING=1,
	OTHER
};


enum {
	DIR_RD=0,
	DIR_WR=1,
	DIR_SIZE
};

struct list
{
struct list* pre; 
struct list* next;
};


struct session {
  char* req;
  char* rep;
  int fd;
};

struct task {
	struct list qlist;              /* chaining in the same queue; bidirectionnal but not circular */
	int state;			/* task state : IDLE or RUNNING */
	struct timeval expire;		/* next expiration time for this task, use only for fast sorting */
	void (*process)(struct task *t, int time);	/* the function which processes the task */
	void *context;			/* the task's context */
};

struct cmd {
  int cmd;
};



struct fdtab {
  struct list qlist;
  struct {
	int (*f)(int fd);            /* read/write function */
	char* buf;            /* read/write buffer */
  } cb[DIR_SIZE];
  int fd;//socket
  int epoll;
  int pollflag;
  int status;//socket status
  struct task qtask;
};

struct pool {
  struct list qlist;
  void  **freelist;
  int size;
  int used;
  int capacity;
  char name[12];
};





extern int epoll_fd;
extern struct list *task;
extern struct list *fdlist;
extern struct fdtab fdtabs[MAXEPOLLSIZE];
extern struct list* pllist;
extern struct pool* gpool;


extern int do_poll();
extern int do_init();
extern int do_set(int fd);
extern int stream_accept(int fd);
extern int stream_write(int fd);
extern int stream_read(int fd);
extern void process_session(struct task *t, int time) ;

void list_init(list* h);
void list_insert_head(list* h,list* x);
bool list_empty(list* h);
void list_insert_tail(list* h,list* x);
void list_remove(list* x) ;

extern struct pool* pool_create(char* name, int size);
extern void* pool_alloc(struct pool* pool);
extern void pool_free(struct pool* pool,void* ptr);


#endif



