#include <stdio.h>
#include "game.h"

#define MAX_CARDS 12

void displayBoard(char cards[], int rows, int cols,
                  int matched[], int reveal[])
{
    int i, j, k = 0;

    printf("\n========== CARD BOARD ==========\n\n");

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(matched[k] || reveal[k])
                printf("  [%c] ", cards[k]);
            else
                printf("  [%d] ", k + 1);

            k++;
        }

        printf("\n\n");
    }
}

void playGame(char cards[], int rows, int cols, int sets)
{
    int totalCards = rows * cols;
    int matched[MAX_CARDS] = {0};
    int reveal[MAX_CARDS] = {0};

    int first, second, third;
    int matchedSets = 0;
    int attempts = 0;

    while(matchedSets < sets)
    {
        int i;

        for(i = 0; i < totalCards; i++)
            reveal[i] = 0;

        displayBoard(cards, rows, cols, matched, reveal);

        printf("\nSelect three cards (1-%d)\n", totalCards);

        printf("Enter first card: ");
        scanf("%d", &first);

        printf("Enter second card: ");
        scanf("%d", &second);

        printf("Enter third card: ");
        scanf("%d", &third);

        if(first < 1 || first > totalCards ||
           second < 1 || second > totalCards ||
           third < 1 || third > totalCards ||
           first == second || first == third ||
           second == third ||
           matched[first - 1] ||
           matched[second - 1] ||
           matched[third - 1])
        {
            printf("\nInvalid selection! Try again.\n");
            continue;
        }

        first--;
        second--;
        third--;

        reveal[first] = 1;
        reveal[second] = 1;
        reveal[third] = 1;

        attempts++;

        displayBoard(cards, rows, cols, matched, reveal);

        if(cards[first] == cards[second] &&
           cards[second] == cards[third])
        {
            printf("\nExcellent! You found a matching set!\n");

            matched[first] = 1;
            matched[second] = 1;
            matched[third] = 1;

            matchedSets++;
        }
        else
        {
            printf("\nNot a match! Try again.\n");
        }

        printf("\nAttempts used: %d\n", attempts);

        if(matchedSets < sets)
        {
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
        }
    }

    printf("\n================================\n");
    printf("       CONGRATULATIONS!\n");
    printf("       YOU WON THE GAME!\n");
    printf("================================\n");

    printf("Total attempts: %d\n", attempts);
}