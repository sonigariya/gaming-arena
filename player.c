#include <stdio.h>
#include "player.h"

int movePlayer(Game *g, char direction)
{
    int newRow = g->playerRow;
    int newCol = g->playerCol;

    if(direction == 'W' || direction == 'w')
        newRow--;

    else if(direction == 'S' || direction == 's')
        newRow++;

    else if(direction == 'A' || direction == 'a')
        newCol--;

    else if(direction == 'D' || direction == 'd')
        newCol++;

    else
    {
        printf("Invalid direction!\n");
        return 0;
    }

    if(g->maze[newRow][newCol] == '#')
    {
        printf("You cannot move through walls!\n");
        return 0;
    }

    g->playerRow = newRow;
    g->playerCol = newCol;

    g->moves++;

    /* Score increases for successful movement */
    g->score += 10;

    /* Trap system */
    if(g->maze[newRow][newCol] == 'T')
    {
        g->lives--;

        g->score -= 30;

        if(g->score < 0)
            g->score = 0;

        g->maze[newRow][newCol] = '.';

        printf("\nYou stepped on a TRAP!\n");
        printf("1 Life Lost!\n");
        printf("Lives Remaining: %d\n", g->lives);
    }

    if(newRow == g->exitRow && newCol == g->exitCol)
    {
        return 1;
    }

    return 0;
}