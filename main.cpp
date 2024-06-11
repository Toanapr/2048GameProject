#include "headers/2048.h"


int main()
{


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

    fstream loadResume;
    int index;
    resume *resumeList = new resume[5];
    loadResumeFile(resumeList);


// #if (0)

    startMenu(choice, size, player, userList, numberOfUser, isOpenUndo, resumeList, index);

    while (choice != '5')
    {

        if (choice == '1' && index != 6)
        {
            board = allocateMatrix(resumeList[index - 1].size);

            for (int i = 0; i < resumeList[index - 1].size; i++)
                for (int j = 0; j < resumeList[index - 1].size; j++)
                    board[i][j] = resumeList[index - 1].board[i][j];
            player = resumeList[index - 1].player;
           
            int timeBefore = player.playingTime;

            printUI(board, resumeList[index - 1].size, player, bestScore, false);
            playGame(undo, redo, board, resumeList[index - 1].size, player, bestScore, choice, false, resumeList);

            player.playingTime += timeBefore;
            resumeList[index - 1].player = player;
            saveResume(resumeList);

            bool isExist = isExistUserName(userList, numberOfUser, player.userName);
            
            if (!isExist)
            {
                saveUserList(userList, numberOfUser, player);
                addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
            }
            else
            {
                int cnt = (numberOfUser > 20) ? 20 : numberOfUser;
                for (int i = 0; i < cnt; i++)
                    if (strcmp(userList[i].userName, player.userName) == 0)
                    {
                        userList[i] = player;
                    }
            
                addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
            }

            deleteMatrix(board, resumeList[index - 1].size);
        }

        if (choice == '2')
        {
            board = allocateMatrix(size);
            undo.clear();
            redo.clear();
            initializeGame(undo, board, size, player, bestScore, isOpenUndo);

            printUI(board, size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo, resumeList);
            saveBestScore(output, player.score, bestScore);

            saveResume(resumeList);

            saveUserList(userList, numberOfUser, player);
            addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);

            deleteMatrix(board, size);
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
    delete[] resumeList;
    undo.clear();
    redo.clear();

// #endif
    return 0;
}