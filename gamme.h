/* game.h - board, rules and game state */
#ifndef GAME_H
#define GAME_H

#include "commonn.h"
#include "piece.h"
#include "queue.h"
#include "stack.h"
#include "list.h"

typedef struct {
    int **board;          /* H x W dynamic array: 0 empty, 1..7 locked piece */
    Piece *cur;           /* falling piece */
    CQueue *next;         /* upcoming pieces (circular queue) */
    AStack undo;          /* undo history (array stack) */
    LList log;            /* every piece placed (singly linked list) */
    int bag[7], bag_idx;  /* shuffled 7-bag */
    int score, lines, level;
    int over;
} Game;

Game *game_create(void);
void  game_destroy(Game *g);

void game_spawn(Game *g);                   /* take next piece from the queue */
int  game_move(Game *g, int dx, int dy);    /* returns 1 if the piece moved   */
void game_rotate(Game *g);
void game_lock(Game *g);                    /* fix piece, clear rows, spawn   */
void game_hard_drop(Game *g);
int  game_fall_delay_ms(const Game *g);     /* gravity speed for this level   */

#endif
