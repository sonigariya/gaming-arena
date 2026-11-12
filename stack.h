/* stack.h - array stack (undo) and linked stack (rows to clear) */
#ifndef STACK_H
#define STACK_H

#include "common.h"
#include "piece.h"

/* ---- array representation: undo history of the falling piece ---- */
typedef struct {
    Piece items[UCAP];
    int top;                          /* -1 when empty */
} AStack;

void as_init(AStack *s);
int  as_is_empty(const AStack *s);
int  as_is_full(const AStack *s);
int  as_push(AStack *s, const Piece *p);
int  as_pop(AStack *s, Piece *out);   /* returns 0 on underflow */

/* ---- linked representation: full rows waiting to be cleared ---- */
typedef struct SNode {
    int row;
    struct SNode *next;
} SNode;
typedef struct { SNode *top; } LStack;

void ls_init(LStack *s);
int  ls_is_empty(const LStack *s);
void ls_push(LStack *s, int row);
int  ls_pop(LStack *s);               /* returns -1 on underflow */

#endif