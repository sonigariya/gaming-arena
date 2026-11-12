#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "levels.h"
#include "cards.h"
#include "game.h"

void cardmatchig()
{
    int choice;
    LevelConfig settings;

    char cards[25];

    srand((unsigned int)time(NULL));

    printf("\n================================\n");
    printf("       CARD MATCHING GAME\n");
    printf("================================\n");

    displayLevels();

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    settings = getLevelSettings(choice);

    if (settings.rows == 0)
    {
        printf("Invalid level selection!\n");
        return 1;
    }

    int totalCells = settings.rows * settings.cols;

    printf("\nStarting Game...\n");
    printf("Level: %s\n",
           choice == 1 ? "Easy" :
           choice == 2 ? "Medium" : "Hard");

    printf("Grid Size: %d x %d\n",
           settings.rows, settings.cols);

    printf("Matching Groups: %d\n", settings.groups);

    createCards(cards, totalCells, settings.groups);

    shuffleCards(cards, totalCells);

    playGame(cards, settings.rows, settings.cols,
             settings.groups);

    printf("\nThank you for playing!\n");

    return ;
}
