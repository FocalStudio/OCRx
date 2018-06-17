/*
 * queue.h: dynamic queue
 */
 
# ifndef EPITA_S3_QUEUE_H_
# define EPITA_S3_QUEUE_H_
 
/* standard linked lists */
struct list {
  struct list *next;
  matrixBW        *data;
};
 
/*
 * queue container: replace sentinel and add abstraction
 */
struct queue {
  struct list *store;
  size_t       size;
};
 
/*
 * queue_init(queue) initialize an empty queue container
 * allocation of the container is kept external for more flexibility
 */
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
 
# endif /* EPITA_S3_QUEUE_H_ */
