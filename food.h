#ifndef FOOD_H
#define FOOD_H

#include "snake.h"

typedef struct {
    int x;
    int y;
} Food;

void placeFood(Food *food, const Snake *snake, int width, int height);

#endif
