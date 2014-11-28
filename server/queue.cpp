#include "common.h"



void push(int fd, queue *q) {
  struct Node* node = new Node;
  node->fd = fd;
  node->next = NULL;
  
  if(q->head == NULL) {
    q->head=q->tail=node;
  } else {
    q->tail->next = node;
	q->tail = node;
  }	
  return;
}

int pop(queue *q) {
  int fd;
  if(q->head == NULL) {
    return -1;
  } else {
    fd=q->head->fd;
	if(q->head == q->tail) {
	  delete q->head;  
	  q->head=q->tail=NULL;
	} else {
	  struct Node* node = q->head;
	  q->head=q->head->next;
      delete node;	  
	}
  }
  return fd;
}






