#include "Tree.h"

using namespace std;

void MyTree::setcmp(int (*f)(void *s,void *o)) {
  comp = f;
}

struct tree* MyTree::data() {
  return root;
}

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

int MyTree::tree_insert(void* node) {
  struct tree* t = tree_alloc(node);
  int type=ROOT;
  if(root==NULL) {
	root=t;
	t->type=type;
	return 0;
  } else {
    struct tree* tmp = root;
	struct tree* tnode = root;
	while(tmp) {
	  int iRet = comp(tmp->value, node);
	  tnode=tmp;
      if(0 < iRet) {
	    tmp=tmp->lf;
		type=LEFT;
	  } else if(iRet <0) {
	    tmp=tmp->rt;
		type=RIGHT;
	  } else {
	    delete t;
	    return -1;
	  }
	}
    if(type==RIGHT) {
	  tnode->rt=t;
	} else {
	  tnode->lf=t;
	}
	t->type=type;
	return 0;
  }
  return 0;
  
}

struct tree*  MyTree::tree_find(void* node) {
  struct tree* tmp = root;
  while(tmp) {
    int iRet = comp(tmp->value, node);
    if(0 < iRet) {
	  tmp=tmp->lf;
    } else if(iRet > 0) {
	  tmp=tmp->rt;
    } else {
	  break;
    }
  }
  return tmp;
}

int MyTree::tree_delete(void* node) {
  struct tree* t = root;
  struct tree* tmp=NULL;
  
  while(t) {
    int iRet = comp(t->value, node);
    if(0 < iRet) {
	  tmp=t;
	  t=t->lf;
    } else if(iRet < 0) {
	  tmp=t;
	  t=t->rt;
    } else {
	  break;
    }
  }
  
  if(!t) {
    return -1;
  }
  
  if(t->type==LEFT) {
    if (t->lf == NULL) {
	  tmp->lf=t->rt;
	  if(t->rt)
	    t->rt->type=LEFT;
	} else if (t->rt == NULL) {
	  tmp->lf=t->lf;
	} else {
	  struct tree* rtmp=NULL;
	  t->rt->type=LEFT;
	  tmp->lf = t->rt;
	  rtmp=t->rt->lf;
	  t->rt->lf=t->lf;
	  if(rtmp) {
	    struct tree* rltmp = t->lf;
	    while(rltmp->rt) {
	      rltmp=rltmp->rt;
	    }
	    rtmp->type=RIGHT;
	    rltmp->rt=rtmp;
	  }
	}
  } else if(t->type==RIGHT){
    if (t->lf == NULL) {
	  tmp->rt=t->rt;
	} else if (t->rt == NULL) {
	  tmp->rt=t->lf;
	  if(t->lf)
	    t->lf->type=RIGHT;
	} else {
	  struct tree* ltmp=NULL;
	  tmp->rt = t->lf;
	  t->lf->type=RIGHT;
	  ltmp=t->lf->rt;
	  t->lf->rt=t->rt;
	  if(ltmp) {
	    struct tree* rltmp = t->rt;
	    while(rltmp->lf) {
	      rltmp=rltmp->lf;
	    }
	    ltmp->type=LEFT;
	    rltmp->lf=ltmp;
      }		
	}   
  } else {
	if (t->lf == NULL) {
	  root=t->rt;
	  if(t->rt)
	    t->rt->type=ROOT;
	} else if (t->rt == NULL) {
      root=t->lf;
	  if(t->lf)
	    t->lf->type=ROOT;
	} else {
      struct tree* ltmp=NULL;
	  root = t->lf;
	  t->lf->type=ROOT;
	  ltmp=t->lf->rt;
	  t->lf->rt=t->rt;
	  if(ltmp) {
	    struct tree* rltmp = t->rt;
	    while(rltmp->lf) {
	      rltmp=rltmp->lf;
	    }
	    ltmp->type=LEFT;
	    rltmp->lf=ltmp;
      }	  
	}	
  }
  delete t;
  
}











