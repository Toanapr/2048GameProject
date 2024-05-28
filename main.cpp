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

    player.userName = "thaitoan";
    player.score = 20;
    player.playingTime = 100;

    fstream loadUser;

    loadUser.open(LIST_USER_FILE, ios::out | ios::binary);
    loadUser.write((char *) &player, sizeof(user));
    loadUser.close();

    // loadUser.open("user_list.bin", ios::in | ios::binary);
    // loadUser.read((char*) &player, sizeof(user));
    // loadUser.close();

    // std::cout << player.score;
    // int numberOfUser = countNumberOfUser(loadUser);

    // cout << numberOfUser;
    user *userList = new user[1];
    loadFileUserList(loadUser, userList, 1);

    cout << userList[0].userName;

#if (0)

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

            input.open(LIST_USER_FILE, ios::app | ios::binary);
            input.write((char *)&player, sizeof(user));
            input.close();

            // numberOfUser++;
            // delete[] userList;
            // userList = new user[numberOfUser];
            // userList[numberOfUser] = player;
            // sortScore(userList, numberOfUser);
            // addUserInFile(loadUser, userList);
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
#endif
    return 0;
}