#ifndef LEVELS_H
#define LEVELS_H

typedef struct
{
    int rows;
    int cols;
    int groups;
} LevelConfig;

void displayLevels(void);
LevelConfig getLevelSettings(int choice);

#endif