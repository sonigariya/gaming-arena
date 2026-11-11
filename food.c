#include <stdlib.h>
#include "food.h"

void placeFood(Food *food, const Snake *snake, int width, int height)
{
    do {
        food->x = 1 + rand() % width;
        food->y = 1 + rand() % height;
    } while (snakeContains(snake, food->x, food->y));
}
