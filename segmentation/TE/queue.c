# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
#include "matrix.h"
#include "SDL_rotozoom.h"

struct list {
  struct list *next;
  struct matrixBW *data;
};
 
/*
 * queue container: replace sentinel and add abstraction
 */
struct queue {
  struct list *store;
  size_t       size;
};

void queue_init(struct queue *queue){
  queue->store = NULL;
  queue->size = 0;
}

int queue_is_empty(struct queue *queue){
  return queue->store == NULL;
}

void queue_push(struct queue *queue, struct matrixBW *elm){
  if (queue_is_empty(queue)){
    struct list *felm = malloc(sizeof(struct list));
    felm->data = elm;
    felm->next = felm;
    queue->store = felm;
  }
  else{
    struct list *nelm = malloc(sizeof(struct list));
    nelm->data = elm;
    struct list *lelm = queue->store;
    nelm->next = lelm->next;
    lelm->next = nelm;
    queue->store = nelm;
  }
  queue->size ++;
}

struct matrixBW* queue_pop(struct queue *queue){
  if (queue_is_empty(queue))
    return NULL;
  struct list *felm;
  felm = queue->store->next;
  struct matrixBW *elm = felm->data;
  if (felm->next == felm){
    queue->store = NULL;
    free(felm);
  }
  else{
    queue->store->next = felm->next;
    free(felm);
  }
  queue->size--;
  return elm;
}
