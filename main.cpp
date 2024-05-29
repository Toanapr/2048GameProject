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

    // strcpy(player.userName, "thaitoan");
    // player.score = 20;
    // player.playingTime = 100;

    fstream loadUser;

    // loadUser.open(LIST_USER_FILE, ios::out | ios::binary);
    // loadUser.write((char *)&player, sizeof(user));
    // loadUser.close();

    // strcpy(player.userName, "thanhthanh");
    // player.score = 20;
    // player.playingTime = 120;

    // loadUser.open(LIST_USER_FILE, ios::app | ios::binary);
    // loadUser.write((char *)&player, sizeof(user));
    // loadUser.close();

    int numberOfUser = countNumberOfUser(loadUser);

    // cout << numberOfUser;

    
    user *userList = new user[numberOfUser];
    loadFileUserList(loadUser, userList, numberOfUser);
    // for (int i = 0; i < numberOfUser; i++)
    //     cout << userList[i].userName << endl;

// #if (0)

    fstream input, output;
    int bestScore;
    bestScore = getBestScore(input);

    // initializeGame(undo, board, size, player, bestScore, isOpenUndo);
    // playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo);

    startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);

    while (choice != '5')
    {
        if (choice == '2')
        {
            initializeGame(undo, board, size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo);
            saveBestScore(output, player.score, bestScore);

            loadUser.open(LIST_USER_FILE, ios::app | ios::binary);
            loadUser.write((char *)&player, sizeof(user));
            loadUser.close();

            // numberOfUser++;
            // delete[] userList;
            // userList = new user[numberOfUser];
            // userList[numberOfUser] = player;
            // sortScore(userList, numberOfUser);
            // addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
        }

        if (choice == '3' || choice == '4')
        {
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);
        }

        if (choice == '5')
        {
            deleteMatrix(board, size);
            undo.clear();
            redo.clear();
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);
        }
    }
// #endif
    return 0;
}