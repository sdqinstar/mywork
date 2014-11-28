#include "common.h"


void list_init(list* h){
  h->pre=h->next=NULL;
}

bool list_empty(list* h){
  if(h->pre == NULL && h->next == NULL)
    return true;
  return false;
}

void list_insert_head(list* h,list* x){
  list* tmp=h->next;
  if(!list_empty(h)) {
  h->next=x;
  x->pre=h;
  x->next=tmp;
  tmp->pre=x;
  } else {
  h->next=x;
  x->pre=h;
  x->next=NULL;
  }
}

void list_insert_tail(list* h,list* x){
  list* tmp=h;
  while(tmp->next){
    tmp=tmp->next;
  }
  tmp->next=x;
  x->pre=tmp;
  x->next=NULL;
}

void list_remove(list* x) {
  if(x->pre == NULL)
    return;
  if(x->next == NULL) {
    x->pre->next = x->next;
	return;
  }
  x->pre->next = x->next;
  x->next->pre=x->pre;
}

/*
void list_print(list* h) {
  list* tmp=h;
  while(tmp->next){
    testNode_* Node = (testNode_*)((unsigned char*)tmp->next -offsetof(testNode_,q));  
	printf("%s,%d\n",Node->str,Node->num);
	tmp=tmp->next;
  }
}
*/






