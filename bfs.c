#include <stdio.h>
#include "bfs.h"

int findPath(Game *g, int pathRow[], int pathCol[], int *pathLength)
{
    int queueRow[SIZE * SIZE];
    int queueCol[SIZE * SIZE];

    int visited[SIZE][SIZE] = {0};

    int parentRow[SIZE][SIZE];
    int parentCol[SIZE][SIZE];

    int front = 0;
    int rear = 0;

    int row, col;
    int newRow, newCol;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    int i;

    queueRow[rear] = g->playerRow;
    queueCol[rear] = g->playerCol;

    rear++;

    visited[g->playerRow][g->playerCol] = 1;

    while(front < rear)
    {
        row = queueRow[front];
        col = queueCol[front];

        front++;

        if(row == g->exitRow && col == g->exitCol)
            break;

        for(i = 0; i < 4; i++)
        {
            newRow = row + dr[i];
            newCol = col + dc[i];

            if(newRow >= 0 && newRow < SIZE &&
               newCol >= 0 && newCol < SIZE &&
               g->maze[newRow][newCol] != '#' &&
               visited[newRow][newCol] == 0)
            {
                visited[newRow][newCol] = 1;

                parentRow[newRow][newCol] = row;
                parentCol[newRow][newCol] = col;

                queueRow[rear] = newRow;
                queueCol[rear] = newCol;

                rear++;
            }
        }
    }

    if(visited[g->exitRow][g->exitCol] == 0)
        return 0;

    row = g->exitRow;
    col = g->exitCol;

    *pathLength = 0;

    while(row != g->playerRow || col != g->playerCol)
    {
        pathRow[*pathLength] = row;
        pathCol[*pathLength] = col;

        (*pathLength)++;

        i = parentRow[row][col];

        col = parentCol[row][col];
        row = i;
    }

    pathRow[*pathLength] = g->playerRow;
    pathCol[*pathLength] = g->playerCol;

    (*pathLength)++;

    return 1;
}

void showHint(Game *g)
{
    int pathRow[SIZE * SIZE];
    int pathCol[SIZE * SIZE];

    int pathLength = 0;

    if(findPath(g, pathRow, pathCol, &pathLength) == 0)
    {
        printf("No path found!\n");
        return;
    }

    if(pathLength < 2)
    {
        printf("You are already at the exit!\n");
        return;
    }

    int rowDifference =
        pathRow[pathLength - 2] - g->playerRow;

    int colDifference =
        pathCol[pathLength - 2] - g->playerCol;

    if(rowDifference == -1)
        printf("Hint: Move UP (W)\n");

    else if(rowDifference == 1)
        printf("Hint: Move DOWN (S)\n");

    else if(colDifference == -1)
        printf("Hint: Move LEFT (A)\n");

    else if(colDifference == 1)
        printf("Hint: Move RIGHT (D)\n");

    g->score -= 20;

    if(g->score < 0)
        g->score = 0;
}

void autoSolve(Game *g)
{
    int pathRow[SIZE * SIZE];
    int pathCol[SIZE * SIZE];

    int pathLength = 0;
    int i;

    if(findPath(g, pathRow, pathCol, &pathLength) == 0)
    {
        printf("No path found!\n");
        return;
    }

    printf("\nShortest Path:\n");

    for(i = pathLength - 2; i >= 0; i--)
    {
        int rowDifference =
            pathRow[i] - pathRow[i + 1];

        int colDifference =
            pathCol[i] - pathCol[i + 1];

        if(rowDifference == -1)
            printf("UP ");

        else if(rowDifference == 1)
            printf("DOWN ");

        else if(colDifference == -1)
            printf("LEFT ");

        else if(colDifference == 1)
            printf("RIGHT ");
    }

    printf("\n");
}