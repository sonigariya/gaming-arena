#include <stdio.h>
#include "levels.h"

void displayLevels(void)
{
    printf("\n===== SELECT DIFFICULTY =====\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice: ");
}

LevelConfig getLevelSettings(int choice)
{
    LevelConfig settings;

    switch (choice)
    {
        case 1:
            settings.rows = 3;
            settings.cols = 3;
            settings.groups = 3;
            break;

        case 2:
            settings.rows = 4;
            settings.cols = 4;
            settings.groups = 5;
            break;

        case 3:
            settings.rows = 5;
            settings.cols = 4;
            settings.groups = 6;
            break;

        default:
            settings.rows = 0;
            settings.cols = 0;
            settings.groups = 0;
            break;
    }

    return settings;
}