#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "graphics.h"

// Setup Console
void setupConsole(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("title Snake Game - DSA with C PBL");

    // Hide Cursor
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(console, &cursorInfo);
}

// Clear Screen Without Flickering
void clearScreen(void)
{
    static int firstTime = 1;

    COORD position = {0, 0};
    DWORD written;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Clear screen only once
    if (firstTime)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;

        if (GetConsoleScreenBufferInfo(console, &info))
        {
            DWORD cells = info.dwSize.X * info.dwSize.Y;

            FillConsoleOutputCharacterA(
                console, ' ', cells, position, &written
            );

            FillConsoleOutputAttribute(
                console, info.wAttributes, cells, position, &written
            );
        }

        firstTime = 0;
    }

    // Move cursor to starting position
    SetConsoleCursorPosition(console, position);
}

// Draw Game Board
void drawBoard(const Snake *snake, const Food *food,
               int width, int height,
               int score, int highScore, int paused)
{
    int x, y;
    Node *current;

    clearScreen();

    printf("          🐍 SNAKE GAME - DSA WITH C 🐍\n\n");

    printf("  Score: %d       High Score: %d\n",
           score, highScore);

    printf("  Controls: Arrow Keys = Move | P = Pause | X = Exit\n\n");

    // Draw Board
    for (y = 0; y <= height + 1; y++)
    {
        for (x = 0; x <= width + 1; x++)
        {
            // Wall
            if (y == 0 || y == height + 1 ||
                x == 0 || x == width + 1)
            {
                printf("##");
            }

            // Snake Head
            else if (x == snake->head->x &&
                     y == snake->head->y)
            {
                printf("🐍");
            }

            // Food
            else if (x == food->x &&
                     y == food->y)
            {
                printf("🍎");
            }

            // Snake Body
            else
            {
                int found = 0;

                current = snake->head->next;

                while (current != NULL)
                {
                    if (current->x == x &&
                        current->y == y)
                    {
                        printf("🟩");
                        found = 1;
                        break;
                    }

                    current = current->next;
                }

                if (!found)
                {
                    printf("  ");
                }
            }
        }

        printf("\n");
    }

    // Pause Message
    if (paused)
    {
        printf("\n       ⏸️ GAME PAUSED - Press P to Resume\n");
    }

    fflush(stdout);
}