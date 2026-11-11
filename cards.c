#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

/* Initialize Cards */

void initializeCards(char cards[], int totalCards, int sets)
{
    int i, j = 0;

    char symbols[] = {'#', '@', '*', '$'};

    for(i = 0; i < sets; i++)
    {
        cards[j++] = symbols[i];
        cards[j++] = symbols[i];
        cards[j++] = symbols[i];
    }
}

/* Shuffle Cards */

void shuffleCards(char cards[], int totalCards)
{
    int i, j;
    char temp;

    for(i = totalCards - 1; i > 0; i--)
    {
        j = rand() % (i + 1);

        temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

/* Display Shuffled Cards */

void displayCards(char cards[], int rows, int cols)
{
    int i, j, k = 0;

    printf("\n========== SHUFFLED CARDS ==========\n");

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            printf("  %c  ", cards[k++]);
        }

        printf("\n\n");
    }
}