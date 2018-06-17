//matrix.h
# pragma once

#include <stdlib.h>
# include <assert.h>
#include <SDL.h>
# include <stdio.h>
#include <math.h>


struct queue {
  struct list *store;
  size_t       size;
};

struct matrixBW
{
    size_t line, cols;
    double *data;
};

struct list {
  struct list *next;
  struct matrixBW	*data;
};

struct matrixBW* newMatrix(size_t, size_t );

void freeMatrix(struct matrixBW*);


void queue_init(struct queue *queue);
 
/*
 * queue_is_empty(queue) test for emptyness
 */
int queue_is_empty(struct queue *queue);
 
/*
 * queue_push(queue, elm) push elm
 */
void queue_push(struct queue *queue, struct matrixBW *elm);
 
/*
 * queue_pop(queue) pop the next element (FIFO order)
 * returns NULL if the queue is empty
 */
struct matrixBW* queue_pop(struct queue *queue);

struct matrixBW* resizeMatrix(struct matrixBW *matrix);
