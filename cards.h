#ifndef CARDS_H
#define CARDS_H

#define MAX_CARDS 12

void initializeCards(char cards[], int totalCards, int sets);

void shuffleCards(char cards[], int totalCards);

void displayCards(char cards[], int rows, int cols);

#endif