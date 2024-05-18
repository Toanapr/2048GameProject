#include "2048.h"

int main()
{
    system("cls");
    srand(time(0));

    int **board;
    int size = 0;
    char choice;
    user player;
    Stack undo, redo;

    fstream loadUser;
    int numberOfUser = countNumberOfUser(loadUser);
    user *userList = new user[numberOfUser];
    loadFileUserList(loadUser, userList, numberOfUser);

    fstream input, output;
    int bestScore;
    bestScore = getBestScore(input);

    startMenu(choice, size, player, userList, numberOfUser);

    while (choice != '4')
    {
        if (choice == '2')

        {
            initializeGame(undo, board, size, player, bestScore);
            playGame(undo, redo, board, size, player, bestScore, choice);
            saveBestScore(output, player.score, bestScore);
            addUserInFile(loadUser, player);

            numberOfUser++;
            delete[] userList;
            userList = new user[numberOfUser];
            loadFileUserList(loadUser, userList, numberOfUser);
        }

        if (choice == '3')
        {
            startMenu(choice, size, player, userList, numberOfUser);
        }

        if (choice == '4' && size != 0)
        {

            deleteMatrix(board, size);
            undo.clear();
            redo.clear();
            startMenu(choice, size, player, userList, numberOfUser);
        }
    }
    return 0;
}