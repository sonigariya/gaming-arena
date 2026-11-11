#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "game.h"
#include "snake.h"
#include "food.h"
#include "graphics.h"

#define WIDTH 30
#define HEIGHT 16

static int loadHighScore(void)
{
    FILE *file = fopen("highscore.txt", "r");
    int value = 0;

    if (file != NULL) {
        fscanf(file, "%d", &value);
        fclose(file);
    }

    return value;
}

static void saveHighScore(int value)
{
    FILE *file = fopen("highscore.txt", "w");

    if (file != NULL) {
        fprintf(file, "%d", value);
        fclose(file);
    }
}

static void soundStart(void)
{
    Beep(700, 100);
    Beep(900, 120);
}

static void soundEat(void)
{
    Beep(1100, 70);
}

static void soundGameOver(void)
{
    Beep(450, 180);
    Beep(300, 250);
}

void startGame(void)
{
    Snake snake;
    Food food;
    int dx = 1, dy = 0;
    int score = 0;
    int highScore = loadHighScore();
    int gameOver = 0;
    int paused = 0;
    int exitGame = 0;
    int grow;
    int key;

    srand((unsigned int)time(NULL));
    setupConsole();
    initSnake(&snake);
    placeFood(&food, &snake, WIDTH, HEIGHT);
    soundStart();

    while (!gameOver && !exitGame) {
        if (_kbhit()) {
            key = _getch();

            if (key == 0 || key == 224) {
                key = _getch();

                if (key == 72 && dy != 1) { dx = 0; dy = -1; }
                else if (key == 80 && dy != -1) { dx = 0; dy = 1; }
                else if (key == 75 && dx != 1) { dx = -1; dy = 0; }
                else if (key == 77 && dx != -1) { dx = 1; dy = 0; }
            } else if (key == 'p' || key == 'P') {
                paused = !paused;
            } else if (key == 'x' || key == 'X') {
                exitGame = 1;
            }
        }

        if (exitGame)
            break;

        if (paused) {
            drawBoard(&snake, &food, WIDTH, HEIGHT, score, highScore, paused);
            Sleep(100);
            continue;
        }

        grow = (snake.head->x + dx == food.x &&
                snake.head->y + dy == food.y);

        moveSnake(&snake, dx, dy, grow);

        if (snake.head->x <= 0 || snake.head->x > WIDTH ||
            snake.head->y <= 0 || snake.head->y > HEIGHT) {
            gameOver = 1;
        }

        /* Ignore the tail during collision checking when it is about to move away. */
        if (!gameOver) {
            Node *current = snake.head->next;

            while (current != NULL) {
                if (current->x == snake.head->x &&
                    current->y == snake.head->y) {
                    gameOver = 1;
                    break;
                }
                current = current->next;
            }
        }

        if (grow && !gameOver) {
            score += 10;
            soundEat();
            placeFood(&food, &snake, WIDTH, HEIGHT);
        }

        if (score > highScore) {
            highScore = score;
            saveHighScore(highScore);
        }

        drawBoard(&snake, &food, WIDTH, HEIGHT, score, highScore, paused);
        Sleep(140);
    }

    if (gameOver) {
        soundGameOver();
        printf("\n       💥 GAME OVER! Final Score: %d\n", score);
    } else {
        printf("\n       👋 Game exited. Final Score: %d\n", score);
    }

    printf("       🏆 High Score: %d\n", highScore);
    freeSnake(&snake);
    printf("\nPress any key to close...");
    _getch();
}
