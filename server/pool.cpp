#include "common.h"

struct pool* pool_create(char* name, int size) {
  struct pool* pool=(struct pool*)malloc(sizeof(struct pool));
  pool->size=size;
  pool->freelist=NULL;
  pool->capacity=0;
  pool->used=0;
  strncpy(pool->name, name, 11);
  list_insert_head(pllist,&pool->qlist);
  return pool;
}

void* pool_refill(struct pool* pool) {
	void* p = malloc(pool->size);
	if (!p) {
	  return NULL;
	}
	pool->capacity++;
	pool->used++;
	return p;
}

void* pool_alloc(struct pool* pool){
  void* ptr = (void*)pool->freelist;
  if(NULL==ptr){
    ptr = pool_refill(pool);
  } else {
    pool->freelist=(void**)*(void**)(pool->freelist);
  }
  return ptr;

}

void pool_free(struct pool* pool,void* ptr) {
  *(void**)ptr=(void*)pool->freelist;
  pool->freelist=(void**)ptr;
  pool->used--;
}








