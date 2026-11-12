#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "score.h"

#define MAX_CELLS 25

void displayBoard(char cards[], int rows, int cols,
                  int matched[], int revealed[])
{
    printf("\n");

    for (int i = 0; i < rows * cols; i++)
    {
        if (cards[i] == '\0')
            printf(" [] ");

        else if (matched[i] || revealed[i])
            printf(" %2c ", cards[i]);

        else
            printf(" %2d ", i + 1);

        if ((i + 1) % cols == 0)
            printf("\n");
    }
}

void clearInputLine(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF);
}

int getPosition(int totalCells, int matched[],
                char cards[], int excluded1, int excluded2,
                const char *message)
{
    int choice;

    while (1)
    {
        printf("%s", message);

        if (scanf("%d", &choice) != 1)
        {
            clearInputLine();
            printf("Invalid input! Enter a number.\n");
            continue;
        }

        clearInputLine();

        if (choice < 1 || choice > totalCells)
        {
            printf("Invalid position! Try again.\n");
            continue;
        }

        int index = choice - 1;

        if (matched[index])
        {
            printf("This card is already matched!\n");
            continue;
        }

        if (cards[index] == '\0')
        {
            printf("This is a closed box! Choose another position.\n");
            continue;
        }

        if (index == excluded1 || index == excluded2)
        {
            printf("Choose a different position!\n");
            continue;
        }

        return index;
    }
}

void playGame(char cards[], int rows, int cols, int groups)
{
    int totalCells = rows * cols;

    if (totalCells > MAX_CELLS || groups <= 0 ||
        groups * 3 > totalCells)
    {
        printf("Invalid game configuration!\n");
        return;
    }

    int matched[MAX_CELLS] = {0};
    int revealed[MAX_CELLS] = {0};

    int foundGroups = 0;
    int attempts = 0;

    while (foundGroups < groups)
    {
        displayBoard(cards, rows, cols, matched, revealed);

        int first, second, third;

        first = getPosition(
            totalCells, matched, cards, -1, -1,
            "\nChoose first card: "
        );

        second = getPosition(
            totalCells, matched, cards, first, -1,
            "Choose second card: "
        );

        third = getPosition(
            totalCells, matched, cards, first, second,
            "Choose third card: "
        );

        attempts++;

        revealed[first] = 1;
        revealed[second] = 1;
        revealed[third] = 1;

        printf("\n========== REVEALED CARDS ==========\n");

        displayBoard(cards, rows, cols, matched, revealed);

        if (cards[first] == cards[second] &&
            cards[second] == cards[third])
        {
            matched[first] = 1;
            matched[second] = 1;
            matched[third] = 1;

            foundGroups++;

            printf("\n\033[1;32mIT'S A MATCH!\033[0m\n");
            printf("One group successfully matched!\n");
        }
        else
        {
            printf("\n\033[1;31mNO MATCH! TRY AGAIN!\033[0m\n");
        }

        revealed[first] = 0;
        revealed[second] = 0;
        revealed[third] = 0;

        if (foundGroups < groups)
        {
            printf("\nPress Enter to continue...");
            getchar();

            system("cls");
        }
    }

    int xp = calculateXP(groups, attempts);

    printf("\n================================\n");
    printf("        GAME COMPLETED!\n");
    printf("================================\n");

    printf("\nYou solved the grid in %d attempts!\n", attempts);

    printf("\nXP Earned: %d\n", xp);

    printf("Your Rank: %s\n", calculateRank(xp));

    printf("\nThank you for playing!\n");
}