#include <stdlib.h>
#include "cards.h"

void createCards(char cards[], int totalCells, int groups)
{
    char symbols[] = {'#', '$', '*', '@'};

    int index = 0;

    for (int i = 0; i < groups; i++)
    {
        char symbol = symbols[i % 4];

        // Create three identical symbols
        for (int j = 0; j < 3; j++)
        {
            cards[index++] = symbol;
        }
    }

    // Fill remaining cells with closed boxes
    while (index < totalCells)
    {
        cards[index++] = '\0';
    }
}

void shuffleCards(char cards[], int totalCells)
{
    for (int i = totalCells - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        char temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}