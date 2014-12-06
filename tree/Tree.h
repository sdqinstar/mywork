#ifndef __TREE_H
#define __TREE_H
#include <stdio.h>

enum Type{
  ROOT=0,
  LEFT,
  RIGHT
};


struct tree {
  struct tree* lf;
  struct tree* rt;
  int type;
  void *value;
};

class MyTree{
public:
  MyTree():root(NULL){};
  ~MyTree(){};
  struct tree* tree_alloc(void* node);
  void tree_traversal(struct tree* t, void(*func)(struct tree* t));
  int tree_insert(void* node);
  struct tree* tree_find(void* node);
  int tree_delete(void* node);
  void setcmp(int (*f)(void *s,void *o));
  struct tree* data();

private:
  struct tree* root;
  int (*comp)(void *s,void *o); 
  void (*deloc)(void *data);
};





#endif











