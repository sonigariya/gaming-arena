#include <stdio.h>
#include "maze.h"

void createMaze(Game *g)
{
    char maze[SIZE][SIZE] =
    {
        "#########",
        "#...#...#",
        "#.#.#.#.#",
        "#.#...#.#",
        "#.###.#.#",
        "#.....#.#",
        "###.###.#",
        "#.......#",
        "#########"
    };

    int i, j;

    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            g->maze[i][j] = maze[i][j];
        }
    }

    g->playerRow = 1;
    g->playerCol = 1;

    g->exitRow = 7;
    g->exitCol = 7;

    g->maze[g->exitRow][g->exitCol] = 'E';
}

void displayMaze(Game *g)
{
    int i, j;

    printf("\n");

    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            if(i == g->playerRow && j == g->playerCol)
                printf("P ");
            else
                printf("%c ", g->maze[i][j]);
        }

        printf("\n");
    }

    printf("\nP = Player");
    printf("\n# = Wall");
    printf("\n. = Path");
    printf("\nE = Exit");
    printf("\nT = Trap\n");
}