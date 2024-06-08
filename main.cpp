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
    resume *resumeList = new resume[5];
    loadResumeFile(resumeList);

    // for (int i = 0; i < 5; i++)
    //     cout << resumeList[i].player.userName << endl;

    // cout << resumeList[0].size << endl;
    // size = resumeList[0].size;

    // board = allocateMatrix(size);
    // for (int i = 0; i < size; i++)
    //     for (int j = 0; j < size; j++)
    //     {
    //         int x = resumeList[0].board[i][j];
    //         board[i][j] = x;
    //     }
    // player = resumeList[0].player;
    // printUI(board, size, player, bestScore, isOpenUndo);
    
    // cout << resumeList[0].size;
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //         cout << resumeList[0].board[i][j] << " ";
    //     cout << endl;
    // }

    // #if (0)
    // playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo);

    startMenu(choice, size, player, userList, numberOfUser, isOpenUndo, resumeList, index);
    board = allocateMatrix(size);
    initializeGame(undo, board, size, player, bestScore, isOpenUndo);

    while (choice != '5')
    {

        if (choice == '1' && index != 6)
        {
            deleteMatrix(board, size);
            // size = resumeList[index - 1].size;
            board = allocateMatrix(resumeList[index - 1].size);

            for (int i = 0; i < resumeList[index - 1].size; i++)
                for (int j = 0; j < resumeList[index - 1].size; j++)
                    board[i][j] = resumeList[index - 1].board[i][j];
            player = resumeList[index - 1].player;
            int timeBefore = player.playingTime;
            // undo = resumeList[index - 1].undo;
            // redo = resumeList[index - 1].redo;
            isOpenUndo = false;

            printUI(board, resumeList[index - 1].size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, resumeList[index - 1].size, player, bestScore, choice, isOpenUndo, resumeList);
            player.playingTime += timeBefore;
            saveResume(resumeList);

            bool isExist = false;
            for (int i = 0; i < numberOfUser; i++)
                if (strcmp(userList[i].userName, player.userName) == 0)
                {
                    userList[i] = player;
                    isExist = true;
                    break;
                }
        
            if (!isExist)
            {
                saveUserList(userList, numberOfUser, player);
                addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
            }
            else
            {
                addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
            }
        }

        if (choice == '2')
        {
            deleteMatrix(board, size);
            board = allocateMatrix(size);
            initializeGame(undo, board, size, player, bestScore, isOpenUndo);

            printUI(board, size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo, resumeList);
            saveBestScore(output, player.score, bestScore);

            saveResume(resumeList);

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
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo, resumeList, index);
        }

        if (choice == '0')
        {
            startMenu(choice, size, player, userList, numberOfUser, isOpenUndo, resumeList, index);
        }
    }

    // giai phong bo nho
    delete[] userList;
    deleteMatrix(board, size);
    delete[] resumeList;
    undo.clear();
    redo.clear();

    // #endif
    return 0;
}