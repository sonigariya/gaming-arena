#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "maze.h"
#include "player.h"
#include "bfs.h"
#include "score.h"
#include "save.h"

void instructions()
{
    printf("\n========== INSTRUCTIONS ==========\n");

    printf("W = UP\n");
    printf("A = LEFT\n");
    printf("S = DOWN\n");
    printf("D = RIGHT\n");

    printf("H = Hint\n");
    printf("V = Auto Solver\n");
    printf("R = Restart\n");
    printf("G = Save Game\n");
    printf("Q = Main Menu\n");

    printf("Reach E to win the game.\n");
    printf("Avoid traps T.\n");

    printf("=================================\n");
}

void addTraps(Game *g)
{
    if(g->level == 1)
    {
        g->maze[3][3] = 'T';
    }

    else if(g->level == 2)
    {
        g->maze[3][3] = 'T';
        g->maze[5][4] = 'T';
        g->maze[7][5] = 'T';
    }

    else
    {
        g->maze[3][3] = 'T';
        g->maze[5][4] = 'T';
        g->maze[5][5] = 'T';
        g->maze[7][5] = 'T';
        g->maze[3][5] = 'T';
    }
}

void startGame(Game *g)
{
    char choice;

    time_t startTime = time(NULL);

    int won = 0;

    while(g->lives > 0)
    {
        displayMaze(g);

        printf("\nMoves: %d", g->moves);
        printf("\nScore: %d", g->score);
        printf("\nLives: %d", g->lives);

        printf("\nTime: %d seconds",
               (int)(time(NULL) - startTime));

        printf("\n\nEnter Command: ");

        scanf(" %c", &choice);

        if(choice == 'H' || choice == 'h')
        {
            showHint(g);
        }

        else if(choice == 'V' || choice == 'v')
        {
            autoSolve(g);
        }

        else if(choice == 'G' || choice == 'g')
        {
            saveGame(g);
            return;
        }

        else if(choice == 'Q' || choice == 'q')
        {
            return;
        }

        else if(choice == 'R' || choice == 'r')
        {
            createMaze(g);

            addTraps(g);

            g->moves = 0;
            g->score = 0;
            g->lives = 3;

            startTime = time(NULL);

            printf("\nMaze Restarted!\n");
        }

        else
        {
            won = movePlayer(g, choice);

            if(won == 1)
            {
                break;
            }
        }
    }

    if(won == 1)
    {
        int timeTaken = (int)(time(NULL) - startTime);

        int bonus = 0;

        if(timeTaken < 60)
            bonus = 200;

        else if(timeTaken < 120)
            bonus = 100;

        g->score += 100;

        g->score += bonus;

        printf("\n=================================\n");

        printf("          YOU WIN!\n");

        printf("=================================\n");

        printf("Total Moves: %d\n", g->moves);

        printf("Time Taken: %d Seconds\n", timeTaken);

        printf("Final Score: %d\n", g->score);

        saveHighestScore(g);
    }

    else
    {
        printf("\nGAME OVER!\n");
        printf("Your Lives Are Over!\n");
        printf("Final Score: %d\n", g->score);
    }
}

int main()
{
    Game g;

    int choice;

    srand(time(NULL));

    do
    {
        printf("\n=================================\n");

        printf("          GAMING ARENA\n");

        printf("           MAZE SOLVER\n");

        printf("=================================\n");

        printf("1. New Game\n");
        printf("2. Resume Game\n");
        printf("3. Highest Score\n");
        printf("4. Instructions\n");
        printf("5. Exit\n");

        printf("\nEnter Choice: ");

        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("\nSelect Difficulty:\n");

            printf("1. Easy\n");
            printf("2. Medium\n");
            printf("3. Hard\n");

            printf("Enter Level: ");

            scanf("%d", &g.level);

            if(g.level < 1 || g.level > 3)
            {
                printf("Invalid Level!\n");
                continue;
            }

            printf("\nEnter Player Name: ");

            scanf("%29s", g.name);

            createMaze(&g);

            addTraps(&g);

            g.moves = 0;
            g.score = 0;
            g.lives = 3;

            startGame(&g);
        }

        else if(choice == 2)
        {
            if(loadGame(&g))
            {
                startGame(&g);
            }
        }

        else if(choice == 3)
        {
            displayHighestScore();
        }

        else if(choice == 4)
        {
            instructions();
        }

        else if(choice == 5)
        {
            printf("\nThanks For Playing!\n");
        }

        else
        {
            printf("\nInvalid Choice!\n");
        }

    } while(choice != 5);

    return 0;
}
