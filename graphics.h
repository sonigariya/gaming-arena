#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "snake.h"
#include "food.h"

void setupConsole(void);
void clearScreen(void);
void drawBoard(const Snake *snake, const Food *food, int width, int height,
               int score, int highScore, int paused);

#endif
