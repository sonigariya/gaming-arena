
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cards.h"
#include "game.h"
#include "score.h"

/* Global Variables */

char playerName[30];
int totalXP = 0;
char playerRank[20];

/* Function Declarations */

void displayMenu();
void getPlayerName();  
void selectLevel();
void displayInstructions();

/* Main Function */


int main()
{
    int choice;

    srand(time(NULL));

    printf("====================================\n");
    printf("         CARD MATCHING GAME         \n");
    printf("====================================\n");

    getPlayerName();

    do
    {
        displayMenu();

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                selectLevel();
                break;

            case 2:
                printf("\n========== PLAYER SCORE ==========\n");
                printf("\nPlayer Name: %s", playerName);
                printf("\nTotal XP: %d", totalXP);
                printf("\nPlayer Rank: %s\n", playerRank);
                break;

            case 3:
                displayInstructions();
                break;

            case 4:
                printf("\nThank you for playing!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while(choice != 4);

    return 0;
}

/* Get Player Name */

void getPlayerName()
{
    printf("\nEnter Player Name: ");
    scanf("%29s", playerName);
}

/* Display Main Menu */

void displayMenu()
{
    printf("\n====================================\n");
    printf("         CARD MATCHING GAME         \n");
    printf("====================================\n");

    printf("\nWelcome, %s!\n", playerName);

    printf("\nRank: %s", playerRank);
    printf("\nTotal XP: %d", totalXP);

    printf("\n\n1. Play Game");
    printf("\n2. View My Score");
    printf("\n3. Instructions");
    printf("\n4. Exit");

    printf("\n====================================\n");
}

/* Select Game Level */

void selectLevel()
{
    int level;
    int rows, cols, totalCards, sets;

    char cards[MAX_CARDS];

    printf("\n========== SELECT LEVEL ==========\n");

    printf("\n1. Easy Level (3 x 3)");
    printf("\n2. Medium Level (3 x 4)");

    printf("\n\nEnter level: ");
    scanf("%d", &level);

    if(level == 1)
    {
        rows = 3;
        cols = 3;
        totalCards = 9;
        sets = 3;

        printf("\nEasy Level Selected!\n");
    }

    else if(level == 2)
    {
        rows = 3;
        cols = 4;
        totalCards = 12;
        sets = 4;

        printf("\nMedium Level Selected!\n");
    }

    else
    {
        printf("\nInvalid Level!\n");
        return;
    }

    initializeCards(cards, totalCards, sets);

    shuffleCards(cards, totalCards);

    playGame(cards, rows, cols, sets);
}

/* Game Instructions */

void displayInstructions()
{
    printf("\n========== INSTRUCTIONS ==========\n");

    printf("\n1. Match three identical symbols.");
    printf("\n2. Easy Level contains 9 cards.");
    printf("\n3. Medium Level contains 12 cards.");
    printf("\n4. Complete the game within the given attempts.");
    printf("\n5. Earn XP by completing levels.");
    printf("\n6. Spend XP to purchase extra chances.");
    printf("\n7. Improve your rank by earning more XP.");

    printf("\n==================================\n");
}
