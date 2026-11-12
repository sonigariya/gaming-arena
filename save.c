#include <stdio.h>
#include "save.h"

void saveGame(Game *g)
{
    FILE *fp;

    int i;

    fp = fopen("savegame.txt", "w");

    if(fp == NULL)
    {
        printf("Unable to save game!\n");
        return;
    }

    fprintf(fp, "%d %d %d %d %d %d %d %d %s\n",
            g->playerRow,
            g->playerCol,
            g->exitRow,
            g->exitCol,
            g->moves,
            g->score,
            g->lives,
            g->level,
            g->name);

    for(i = 0; i < SIZE; i++)
    {
        fprintf(fp, "%s\n", g->maze[i]);
    }

    fclose(fp);

    printf("\nGame Progress Saved Successfully!\n");
}

int loadGame(Game *g)
{
    FILE *fp;

    int i;

    fp = fopen("savegame.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Saved Game Found!\n");
        return 0;
    }

    fscanf(fp, "%d %d %d %d %d %d %d %d %29s",
           &g->playerRow,
           &g->playerCol,
           &g->exitRow,
           &g->exitCol,
           &g->moves,
           &g->score,
           &g->lives,
           &g->level,
           g->name);

    for(i = 0; i < SIZE; i++)
    {
        fscanf(fp, "%8s", g->maze[i]);
    }

    fclose(fp);

    printf("\nGame Progress Loaded Successfully!\n");

    return 1;
}