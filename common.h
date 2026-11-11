#ifndef COMMON_H
#define COMMON_H

#define SIZE 9

typedef struct
{
    char maze[SIZE][SIZE];

    int playerRow;
    int playerCol;

    int exitRow;
    int exitCol;

    int moves;
    int score;
    int lives;
    int level;

    char name[30];

} Game;

#endif