#ifndef __TREE_H
#define __TREE_H

enum Type{
  ROOT=0,
  LEFT,
  RIGHT
};


struct tree {
  struct tree* lf;
  struct test* rt;
  int type;
  void *value;
};

class MyTree{
public:
  MyTree();
  ~MyTree();
  void* tree_init(struct tree* t);

private:
  struct tree* root;
  int (*comp)(void *s,void *o); 

friend void tree_traversal(struct tree* t, void(*func)(struct tree* t));
}





#endif











