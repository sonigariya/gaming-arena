#ifndef SNAKE_H
#define SNAKE_H

typedef struct Node {
    int x;
    int y;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int length;
} Snake;

void initSnake(Snake *snake);
int moveSnake(Snake *snake, int dx, int dy, int grow);
int snakeContains(const Snake *snake, int x, int y);
void freeSnake(Snake *snake);

#endif
