/* list.c - linked lists
 * Syllabus (Unit 2): singly linked list, doubly linked list, traversal,
 * insertion and deletion, recursion on a list (Unit 1) */
#include "common.h"
#include "list.h"
#include "piece.h"

/* ================= singly linked list ================= */
void ll_init(LList *l) { l->head = l->tail = NULL; l->size = 0; }

void ll_append(LList *l, int type, int cleared) {     /* O(1) with tail */
    LNode *n = xcalloc(1, sizeof *n);
    n->type = type;
    n->cleared = cleared;
    if (l->tail) l->tail->next = n; else l->head = n;
    l->tail = n;
    l->size++;
}

void ll_free(LList *l) {
    LNode *cur = l->head, *nx;
    while (cur != NULL) { nx = cur->next; free(cur); cur = nx; }
    l->head = l->tail = NULL;
    l->size = 0;
}

/* RECURSION on a linked list: print the pieces in order. O(n) */
void print_log(const LNode *n) {
    if (n == NULL) return;                            /* base case */
    printf("%c", LETTERS[n->type]);
    print_log(n->next);                               /* tail call */
}

/* ================= doubly linked list ================= */
void hl_init(HList *l) { l->head = l->tail = NULL; l->size = 0; }

/* Sorted insertion (highest score first). O(n) */
void hl_insert(HList *l, int score, int lines) {
    HNode *n = xcalloc(1, sizeof *n);
    HNode *cur = l->head;
    n->score = score;
    n->lines = lines;

    while (cur != NULL && cur->score >= score) cur = cur->next;   /* traverse */

    if (cur == NULL) {                    /* insert at the end (or empty list) */
        n->prev = l->tail;
        if (l->tail) l->tail->next = n; else l->head = n;
        l->tail = n;
    } else {                              /* insert before cur */
        n->next = cur;
        n->prev = cur->prev;
        if (cur->prev) cur->prev->next = n; else l->head = n;
        cur->prev = n;
    }
    l->size++;

    if (l->size > MAX_SCORES) {           /* delete the last node */
        HNode *t = l->tail;
        l->tail = t->prev;
        l->tail->next = NULL;
        free(t);
        l->size--;
    }
}

void hl_free(HList *l) {
    HNode *cur = l->head, *nx;
    while (cur != NULL) { nx = cur->next; free(cur); cur = nx; }
    l->head = l->tail = NULL;
    l->size = 0;
}