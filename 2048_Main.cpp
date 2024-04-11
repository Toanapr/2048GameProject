#include "2048.h"

int main()
{
    int **board;
    int size;
    char choice;
    int score;
    int bestScore;
    fstream input, output;
    srand(time(0));
    List undo;
    system("cls");
    bestScore = getBestScore(input);

    startMenu(choice, size);
    while (choice != '2')
    {
        initializeGame(undo, board, size, score, bestScore);
        playGame(undo, board, size, score, bestScore, choice);
        saveBestScore(output, score, bestScore);
        if (choice == '2')
        {
            deleteMatrix(board, size);
            deleteList(undo, size);
            startMenu(choice, size);
        }
    }
    return 0;
}