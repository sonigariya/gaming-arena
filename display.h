/* display.h - drawing the board and the game-over screen */
#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include "list.h"

void print_board(const Game *g, const HList *hs);
void show_summary(const Game *g, const HList *hs);

#endif