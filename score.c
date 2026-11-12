#include <stdio.h>
#include "score.h"

void saveHighestScore(Game *g)
{
    FILE *fp;

    int highestScore = 0;
    char highestName[30] = "None";

    fp = fopen("highestscore.txt", "r");

    if(fp != NULL)
    {
        fscanf(fp, "%29s %d", highestName, &highestScore);

        fclose(fp);
    }

    if(g->score > highestScore)
    {
        fp = fopen("highestscore.txt", "w");

        if(fp != NULL)
        {
            fprintf(fp, "%s %d", g->name, g->score);

            fclose(fp);
        }

        printf("\nNEW HIGHEST SCORE!\n");
        printf("Highest Score: %d\n", g->score);
    }
}

void displayHighestScore()
{
    FILE *fp;

    char name[30];
    int score;

    fp = fopen("highestscore.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Highest Score Available Yet!\n");
        return;
    }

    fscanf(fp, "%29s %d", name, &score);

    printf("\n========== HIGHEST SCORE ==========\n");

    printf("Player Name: %s\n", name);
    printf("Highest Score: %d\n", score);

    fclose(fp);
}