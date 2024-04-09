#include "2048.h"

int main()
{
    int **board;
    int size;
    char choice;
    int score;
    srand(time(0));
    List undo;
    system("cls");
    startMenu(choice, size);
    while (choice != '2')
    {
        initializeGame(undo, board, size, score);
        playGame(undo, board, size, score, choice);
        if (choice == '2')
        {
            deleteMatrix(board, size);
            deleteList(undo, size);
            startMenu(choice, size);
        }
    }
    return 0;
}