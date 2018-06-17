//matrix.c


#include "matrix.h"


struct matrixBW* newMatrix(size_t l, size_t c)
{
    struct matrixBW *result = calloc(1,sizeof(struct matrixBW));
    result->line = l;
    result->cols = c;
    result->data = calloc(l*c,sizeof(double));
    return result;
}

void freeMatrix(struct matrixBW *matrix)
{
    free(matrix->data);
    free(matrix);
}


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

struct matrixBW* resizeMatrix(struct matrixBW *matrix)
{
    int bound = 28;

    struct matrixBW *result = newMatrix(bound, bound);
    double yRatio = (float)matrix->line / (float)bound;
    double xRatio = (float)matrix->cols / (float)bound;
    double px, py;
    for (int i = 0; i < bound; ++i)
    {
        for (int j = 0; j < bound; ++j)
        {
            px = floor((float)j * xRatio);
            py = floor((float)i * yRatio);
            *(result->data+j + i * bound) = *(matrix->data+(int)(px + (float)matrix->cols*py));
        }
    }
    freeMatrix(matrix);
    return result;
}

