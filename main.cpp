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
            // cap phat vung nho cho board
            board = allocateMatrix(resumeList[index - 1].size);

            // cap nhat lai board khi nguoi choi chon resume muon choi tiep
            for (int i = 0; i < resumeList[index - 1].size; i++)
                for (int j = 0; j < resumeList[index - 1].size; j++)
                    board[i][j] = resumeList[index - 1].board[i][j];
            player = resumeList[index - 1].player;

            int timeBefore = player.playingTime; // luu tru thoi gian luc truoc khi resume

            // choi game
            printUI(board, resumeList[index - 1].size, player, bestScore, false);
            playGame(undo, redo, board, resumeList[index - 1].size, player, bestScore, choice, false, resumeList);

            // cap nhat lai thong tin resume sau khi choi xong
            player.playingTime += timeBefore; // cong vao thoi gian da choi truoc do
            resumeList[index - 1].player = player;
            saveResume(resumeList);

            bool isExist = isExistUserName(userList, numberOfUser, player.userName);

            // neu player resume chua ton tai trong top 20
            if (!isExist)
            {
                saveUserList(userList, numberOfUser, player);
                addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
            }
            else // neu player resume da ton tai trong top 20
            {
                // cap nhat lai thong tin player resume trong userList
                int cnt = (numberOfUser > 20) ? 20 : numberOfUser;
                for (int i = 0; i < cnt; i++)
                    if (strcmp(userList[i].userName, player.userName) == 0)
                    {
                        userList[i] = player;
                    }

                addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);
            }

            // giai phong vung nho
            deleteMatrix(board, resumeList[index - 1].size);
        }

        if (choice == '2')
        {
            // khoi tao lai new game
            board = allocateMatrix(size);
            undo.clear();
            redo.clear();
            initializeGame(undo, board, size, player, bestScore, isOpenUndo);

            // choi game
            printUI(board, size, player, bestScore, isOpenUndo);
            playGame(undo, redo, board, size, player, bestScore, choice, isOpenUndo, resumeList);

            saveBestScore(output, player.score, bestScore); // cap nhat lai bestScore len file

            saveResume(resumeList); // cap nhat lai mang resumeList len file

            // cap nhat lai userList len file
            saveUserList(userList, numberOfUser, player);
            addUserInFile(loadUser, userList, (numberOfUser > 20) ? 20 : numberOfUser);

            // xoa vung nho board
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

    // giai phong vung nho
    delete[] userList;
    delete[] resumeList;
    undo.clear();
    redo.clear();

    // #endif
    return 0;
}