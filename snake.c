#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

static Node *createNode(int x, int y)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

void initSnake(Snake *snake)
{
    Node *head = createNode(10, 8);
    Node *body = createNode(9, 8);
    Node *tail = createNode(8, 8);

    head->next = body;
    body->next = tail;

    snake->head = head;
    snake->tail = tail;
    snake->length = 3;
}

/* Returns 1 if the new head position is already occupied. */
int snakeContains(const Snake *snake, int x, int y)
{
    Node *current = snake->head;

    while (current != NULL) {
        if (current->x == x && current->y == y)
            return 1;

        current = current->next;
    }

    return 0;
}

/* Insert a new head. Remove the old tail unless food was eaten. */
int moveSnake(Snake *snake, int dx, int dy, int grow)
{
    int newX = snake->head->x + dx;
    int newY = snake->head->y + dy;
    Node *newHead = createNode(newX, newY);

    newHead->next = snake->head;
    snake->head = newHead;
    snake->length++;

    if (!grow) {
        Node *current = snake->head;

        while (current->next != snake->tail)
            current = current->next;

        free(snake->tail);
        snake->tail = current;
        snake->tail->next = NULL;
        snake->length--;
    }

    return 1;
}

void freeSnake(Snake *snake)
{
    Node *current = snake->head;

    while (current != NULL) {
        Node *nextNode = current->next;
        free(current);
        current = nextNode;
    }

    snake->head = NULL;
    snake->tail = NULL;
    snake->length = 0;
}
