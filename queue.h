/* queue.h - circular queue (array representation, dynamic) */
#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    int *data;
    int front, rear, count, cap;
} CQueue;

CQueue *cq_create(int cap);
int  cq_is_empty(const CQueue *q);
int  cq_is_full(const CQueue *q);
int  cq_add(CQueue *q, int v);      /* returns 0 on overflow  */
int  cq_delete(CQueue *q);          /* returns -1 on underflow */
int  cq_front(const CQueue *q);
void cq_destroy(CQueue *q);

#endif