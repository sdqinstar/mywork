#include <stdio.h>
#include "Tree.h"
#include <string.h>


void print(struct tree* t) {
  printf("%s:%d\n",(char*)t->value,t->type);
}

int mystrcmp(void*a,void*o) {
  return strcmp((char*) a, (char*)o);
}

int main(int argc, char **argv) {
  MyTree t;
  t.setcmp(mystrcmp);
  t.tree_insert((void*)"50");
  t.tree_insert((void*)"30");
  t.tree_insert((void*)"14");
  t.tree_insert((void*)"40");
  t.tree_insert((void*)"34");
  t.tree_insert((void*)"43");
  t.tree_insert((void*)"70");
  t.tree_insert((void*)"60");
  t.tree_insert((void*)"65");
  t.tree_insert((void*)"55");
  t.tree_insert((void*)"80");
  t.tree_insert((void*)"75");
  t.tree_insert((void*)"75");
  t.tree_traversal(t.data(),print);
  printf("\n");
  //t.tree_delete((void*)"70");
  //t.tree_traversal(t.data(),print);
  printf("\n");
  t.tree_delete((void*)"30");
  t.tree_traversal(t.data(),print);
  printf("\n");
  t.tree_delete((void*)"50");
  t.tree_traversal(t.data(),print);
  return 0;
}














