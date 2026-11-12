/* list.h - singly linked list (piece log) and doubly linked list (high scores) */
#ifndef LIST_H
#define LIST_H

#include "common.h"

/* ---- singly linked list: log of every piece placed ---- */
typedef struct LNode {
    int type;
    int cleared;                 /* lines cleared when this piece locked */
    struct LNode *next;
} LNode;
typedef struct { LNode *head, *tail; int size; } LList;

void ll_init(LList *l);
void ll_append(LList *l, int type, int cleared);
void ll_free(LList *l);
void print_log(const LNode *n);       /* recursion */

/* ---- doubly linked list: sorted high-score table ---- */
typedef struct HNode {
    int score, lines;
    struct HNode *prev, *next;
} HNode;
typedef struct { HNode *head, *tail; int size; } HList;

void hl_init(HList *l);
void hl_insert(HList *l, int score, int lines);
void hl_free(HList *l);

#endif