/* stack.c - both stack representations
 * Syllabus (Unit 1): array representation of stack, linked representation
 * of stack, push and pop, overflow and underflow */
#include "common.h"
#include "stack.h"

/* ================= array stack ================= */
void as_init(AStack *s)           { s->top = -1; }
int  as_is_empty(const AStack *s) { return s->top == -1; }
int  as_is_full(const AStack *s)  { return s->top == UCAP - 1; }

int as_push(AStack *s, const Piece *p) {              /* O(1); O(UCAP) when full */
    int i;
    if (as_is_full(s)) {                              /* overflow: drop the oldest */
        for (i = 1; i <= s->top; i++) s->items[i - 1] = s->items[i];
        s->top--;
    }
    s->items[++s->top] = *p;
    return 1;
}

int as_pop(AStack *s, Piece *out) {                   /* O(1) */
    if (as_is_empty(s)) return 0;                     /* underflow */
    *out = s->items[s->top--];
    return 1;
}

/* ================= linked stack ================= */
void ls_init(LStack *s) { s->top = NULL; }
int  ls_is_empty(const LStack *s) { return s->top == NULL; }

void ls_push(LStack *s, int row) {                    /* O(1) */
    SNode *n = xcalloc(1, sizeof *n);
    n->row = row;
    n->next = s->top;
    s->top = n;
}

int ls_pop(LStack *s) {                               /* O(1) */
    SNode *n = s->top;
    int row;
    if (n == NULL) return -1;                         /* underflow */
    row = n->row;
    s->top = n->next;
    free(n);
    return row;
}