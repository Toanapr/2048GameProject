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
    // for (int i = 0; i < numberOfUser; i++)
    //     cout << userList[i].userName << endl;

    fstream input, output;
    int bestScore;
    bestScore = getBestScore(input);


// #if (0)
    // playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo);

    startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);

    while (choice != '5')
    {
        if (choice == '2')
        {
            initializeGame(undo, board, size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo);
            saveBestScore(output, player.score, bestScore);

            // loadUser.open(LIST_USER_FILE, ios::app | ios::binary);
            // loadUser.write((char *)&player, sizeof(user));
            // loadUser.close();

            saveUserList(userList, numberOfUser, player);
            addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);


            // numberOfUser++;
            // delete[] userList;
            // userList = new user[numberOfUser];
            // loadFileUserList(loadUser, userList, numberOfUser);
            // userList[numberOfUser - 1] = player;

            // !sortScore(userList, numberOfUser);
            // !addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
        }

        if (choice == '3' || choice == '4')
        {
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);
        }

        if (choice == '5')
        {
            // todo: neu bam exit thi xoa board
                deleteMatrix(board, size);
                undo.clear();
                redo.clear();
            // todo: neu bam resume thi tiep tuc 
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo);
        }
    }
    // delete[] userList;
// #endif
    return 0;
}