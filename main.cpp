#include "2048.h"

int main()
{
    system("cls");
    srand(time(0));

    int **board;
    int size = 4;
    char choice;
    user player;
    Stack undo, redo;
    bool isOpenUndo = false;

    fstream loadUser;
    int numberOfUser = countNumberOfUser(loadUser);
    user *userList = new user[numberOfUser];
    loadFileUserList(loadUser, userList, numberOfUser);

    fstream input, output;
    int bestScore;
    bestScore = getBestScore(input);

    startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);

    while (choice != '5')
    {
        if (choice == '2')
        {
            initializeGame(undo, board, size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo);
            saveBestScore(output, player.score, bestScore);
            addUserInFile(loadUser, player);

            numberOfUser++;
            delete[] userList;
            userList = new user[numberOfUser];
            loadFileUserList(loadUser, userList, numberOfUser);
        }

        if (choice == '3' || choice == '4')
        {
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);
        }

        if (choice == '5' && size != 4)
        {
            deleteMatrix(board, size);
            undo.clear();
            redo.clear();
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);
        }
    }
    return 0;
}