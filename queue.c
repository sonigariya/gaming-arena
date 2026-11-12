/* queue.c - circular queue holding the upcoming pieces
 * Syllabus (Unit 2): circular queue, create / add / delete / full / empty */
#include "common.h"
#include "queue.h"

CQueue *cq_create(int cap) {
    CQueue *q = xcalloc(1, sizeof *q);
    q->data = xcalloc((size_t)cap, sizeof(int));
    q->cap = cap;
    q->rear = -1;
    return q;
}

int cq_is_empty(const CQueue *q) { return q->count == 0; }
int cq_is_full(const CQueue *q)  { return q->count == q->cap; }

int cq_add(CQueue *q, int v) {                        /* O(1) */
    if (cq_is_full(q)) return 0;                      /* overflow */
    q->rear = (q->rear + 1) % q->cap;
    q->data[q->rear] = v;
    q->count++;
    return 1;
}

int cq_delete(CQueue *q) {                            /* O(1) */
    int v;
    if (cq_is_empty(q)) return -1;                    /* underflow */
    v = q->data[q->front];
    q->front = (q->front + 1) % q->cap;
    q->count--;
    return v;
}

int cq_front(const CQueue *q) { return q->data[q->front]; }

void cq_destroy(CQueue *q) { free(q->data); free(q); }