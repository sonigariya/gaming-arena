#include <stdio.h>

void mazesolver();
void playsnamke();
void cardmatching();
void playtetris();

int main()
{
    int choice;

    do
    {
        printf("\n===== GAMING ARENA =====\n");
        printf("1. Maze Solver\n");
        printf("2. Snake Game\n");
        printf("3. Card Matching\n");
        printf("4. tetris\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                mazesolve();
                break;

            case 2:
                playsnamke();
                break;

            case 3:
                cardmatching();
                break;
          case 4:
                playtetris();
                break;

            case 5:
                printf("Exiting Gaming Arena...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 5);

    return 0;
}
