#include "2048.h"

int main()
{
    system("cls");
    srand(time(0));

    int **board;
    int size;
    char choice;
    user player;
    Stack undo, redo;

    fstream loadUser;
    loadUser.open(LIST_USER_FILE, ios::in);
    int numberOfUser = countNumberOfUser(loadUser);
    user *userList = new user[numberOfUser];
    loadFileUserList(loadUser, userList, numberOfUser);
    loadUser.close();

    fstream input, output;
    int bestScore;
    bestScore = getBestScore(input);

    startMenu(choice, size);
    while (choice != '2')
    {
        player.userName = enterUserName(userList, numberOfUser);
        initializeGame(undo, board, size, player, bestScore);
        playGame(undo, redo, board, size, player, bestScore, choice);
        saveBestScore(output, player.score, bestScore);
        if (choice == '2')
        {
            deleteMatrix(board, size);
            undo.clear();
            redo.clear();
            startMenu(choice, size);
        }
    }
    return 0;
}