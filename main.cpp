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

    fstream loadResume;
    int index;
    resume *r = new resume[5];
    loadResumeFile(r);

    // for (int i = 0; i < 5; i++)
    //     cout << r[i].player.userName << endl;

    // cout << r[0].size << endl;
    // size = r[0].size;
    // for (int i = 0; i < size; i++)
    //     for (int j = 0; j < size; j++)
    //     {
    //         int x = r[0].board[i][j];
    //         board[i][j] = x;
    //     }
    // player = r[0].player;
    // printUI(board, size, player, bestScore, isOpenUndo);
    // cout << r[0].size;
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //         cout << r[0].board[i][j] << " ";
    //     cout << endl;
    // }

    // #if (0)
    // playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo);

    startMenu(choice, size, player, userList, numberOfUser, isOpenUndo, r, index);
    board = allocateMatrix(size);
    initializeGame(undo, board, size, player, bestScore, isOpenUndo);

    while (choice != '5')
    {

        if (choice == '1' && index != 6)
        {
            deleteMatrix(board, size);
            // size = r[index - 1].size;
            board = allocateMatrix(r[index - 1].size);

            for (int i = 0; i < r[index - 1].size; i++)
                for (int j = 0; j < r[index - 1].size; j++)
                    board[i][j] = r[index - 1].board[i][j];
            player = r[index - 1].player;
            // undo = r[index - 1].undo;
            // redo = r[index - 1].redo;
            isOpenUndo = r[index - 1].isOpenUndo;
            // cout << size << endl;
            printUI(board, r[index - 1].size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, r[index - 1].size, player, bestScore, choice, isOpenUndo, r);
            saveResume(r);
            saveUserList(userList, numberOfUser, player);
            addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
        }

        if (choice == '2')
        {
            deleteMatrix(board, size);
            board = allocateMatrix(size);
            initializeGame(undo, board, size, player, bestScore, isOpenUndo);

            printUI(board, size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo, r);
            saveBestScore(output, player.score, bestScore);

            saveResume(r);

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

        if (choice == '3' || choice == '4' || index == 6)
        {
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo, r, index);
        }

        if (choice == '5')
        {
            // todo: neu bam exit thi xoa board
            // deleteMatrix(board, size);
            // undo.clear();
            // redo.clear();
            // todo: neu bam resume thi tiep tuc
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo, r, index);
        }
    }
    // delete[] userList;
    // #endif
    return 0;
}