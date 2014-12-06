#include "Tree.h"

using namespace std;

struct tree* MyTree::tree_alloc(void* node) {
  struct tree* t=new struct tree;
  t->rt=t->lf=NULL;
  t->value=node;
  return t;
}

void MyTree::tree_traversal(struct tree* t, void(*func)(struct tree* t)) {
  if(!t)
    return;
   func(t);	
   tree_traversal(t->lf, func);
   tree_traversal(t->rt, func);
}

void MyTree::tree_insert(void* node) {
  struct tree* t = tree_alloc(node);
  int type=ROOT;
  if(root==NULL) {
	root=t;
	t->type=type;
	return;
  } else {
    struct tree* tmp = root;
	while(tmp) {
      if(0 < cmp(tmp->value, node)) {
	    tmp=root->lf;
		type=LEFT;
	  } else {
	    tmp=root->rt;
		type=RIGHT;
	  }
	}
	tmp=t;
	t->type=type;
	return;
  }
  return;
  
}

void MyTree::tree_find(void* node) {
  struct tree* tmp = root;
  while(tmp) {
    int iRet = cmp(tmp->value, node);
	if(0 < cmp(tmp->value, node)) {
      tmp=root->lf;
	  type=LEFT;
    } else {
      tmp=root->rt;
	  type=RIGHT;
    }
  }
}

void MyTree::tree_insert(void* node) {

}











