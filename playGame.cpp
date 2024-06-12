#include "headers/2048.h"

// kiem tra neu xuat hien 2048 thi win
bool isWinGame(int **board, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == 2048)
                return true;

    return false;
}

// dem so o con trong
int countEmptyPosition(int **board, int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == 0)
                count++;

    return count;
}

// kiem tra lose game
bool isGameEnded(int **board, int size)
{
    if (countEmptyPosition(board, size) > 0) // neu van con o trong thi chua thua
        return false;
    else
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
                if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i]) // neu da het o trong nhung con nhung o co the hop nhat duoc
                    return false;
    }

    return true;
}

// ham xu ly thua game
void endGameProcess(int **board, int size, user player, user *userList, int numberOfUser, int bestScore, char &choice, bool &isOpenUndo, bool &continuePlayLose)
{
    system("cls");
    cout << RED << "GameOver" << RESET << endl;

    // thong bao thu hang cua nguoi choi neu dat top 20
    saveUserList(userList, numberOfUser, player);
    for (int i = 0; i < numberOfUser; i++)
    {
        if (strcmp(userList[i].userName, player.userName) == 0 && i < 20)
        {
            cout << CYAN << "Your rank: " << i + 1 << RESET << endl;
            break;
        }
    }

    // neu nguoi choi khong mo tinh nang undo redo trong setting thi nguoi choi buoc phai dung game
    if (isOpenUndo == false)
    {
        cout << GREEN << "You don't open the undo and redo mode so you can't continue play.\n";
        cout << RESET;
        choice = '0';
        system("pause");
        return;
    }

    // neu nguoi choi co bat tinh nang undo redo thi hoi nguoi choi co muon tiep tuc choi khong
    cout << GREEN << "Do you want to continue (use Undo to continue play)? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)" << RESET << endl;
    char m;
    m = getch();
    while (m != 'y' && m != 'n')
    {
        system("cls");
        cout << RED << "Invalid, please enter choice again (press\033[1;33m y\033[1;31m : yes or\033[1;33m n\033[1;31m : no):  " << RESET;
        m = getch();
    }

    if (m == 'y')
    {
        system("cls");
        isOpenUndo = true;
        continuePlayLose = true;
        printUI(board, size, player, bestScore, isOpenUndo);
    }
    else
    {
        choice = '0';
        return;
    }
}

// xu ly win game
void winGameProcess(int **board, int size, user player, user *userList, int numberOfUser, int bestScore, char &choice, bool &isOpenUndo, bool &continuePlayWin)
{
    system("cls");
    cout << YELLOW << "Congratulation! You Win!!" << RESET << endl;

    // thong bao thu hang cua nguoi choi neu dat top 20
    saveUserList(userList, numberOfUser, player);
    for (int i = 0; i < numberOfUser; i++)
    {
        if (strcmp(userList[i].userName, player.userName) == 0 && i < 20)
        {
            cout << CYAN << "Your rank: " << i + 1 << RESET << endl;
            break;
        }
    }

    // hoi nguoi choi co muon tiep tuc choi khong
    cout << GREEN << "Do you want to continue? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)" << RESET << endl;
    char m;
    m = getch();
    while (m != 'y' && m != 'n')
    {
        system("cls");
        cout << RED << "Invalid, please enter choice again (press\033[1;33m y\033[1;31m : yes or\033[1;33m n\033[1;31m : no):  " << RESET;
        m = getch();
    }

    // neu dong y thi choi tiep
    if (m == 'y')
    {
        continuePlayWin = true;
        system("cls");
        printUI(board, size, player, bestScore, isOpenUndo);
    }
    else
    {
        choice = '0';
        return;
    }
}

// xu ly exit
void exitProcess(int **board, int size, user player, user *userList, int numberOfUser, int bestScore, char &choice, bool isOpenUndo, resume *&resumeList, int index)
{
    bool isResumed = false;
    char doSave;
    char doExit;

    // hoi nguoi choi co muon thoat tro choi dang choi khong
    cout << GREEN << "Do you want to exit the game? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)" << RESET << endl;
    doExit = getch();

    while (doExit != 'y' && doExit != 'n')
    {
        cout << RED << "\nInvalid, please enter choice again (press\033[1;33m y\033[1;31m : yes or\033[1;33m n\033[1;31m : no):  " << RESET;
        doExit = getch();
    }

    if (doExit == 'y') // neu muon thoat
    {
        // kiem tra nguoi choi nay co luu resume truoc do chua
        for (int i = 0; i < 5; i++)
        {
            if (strcmp(resumeList[i].player.userName, player.userName) == 0)
                isResumed = true;
        }

        // neu chua luu resume truoc do
        if (isResumed == false)
        {
            // hoi nguoi choi co muon luu lai de resume
            cout << GREEN << "\nDo you want to save the game to resume later? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)" << RESET << endl;
            doSave = getch();
            while (doSave != 'y' && doSave != 'n')
            {
                // system("cls");
                cout << RED << "Invalid, please enter choice again (press\033[1;33m y\033[1;31m : yes or\033[1;33m n\033[1;31m : no):  \n"
                     << RESET;
                doSave = getch();
            }
        }
        else
            doSave = 'y';

        // neu nguoi choi muon luu resume
        if (doSave == 'y')
        {
            // neu resume da full thi yeu cau nguoi choi phai thay doi nguoi muon luu
            if (index == -1)
            {
                system("cls");
                printResume(resumeList);
                cout << GREEN << "\nThe resume is full. Please delete one to save the game: " << RESET;
                char n;
                n = getch();
                while (n != '1' && n != '2' && n != '3' && n != '4' && n != '5')
                {
                    system("cls");
                    printResume(resumeList);
                    cout << RED << "Invalid, please enter the number of the game you want to delete: " << RESET;
                    n = getch();
                }
                changeResume(resumeList, n - '0', board, size, player);
                system("cls");
                cout << BLUE << "\nChange the user's resume successfully." << RESET;
                Sleep(1200);
                choice = '0';
                return;
            }
            else // nguoc lai thi luu nguoi choi vao resume con trong
            {
                changeResume(resumeList, index + 1, board, size, player);
                cout << BLUE << "\nThe game has been saved successfully." << RESET;
                Sleep(1200);
                choice = '0';
                return;
            }
        }
        else
        {
            choice = '0';
            return;
        }
    }
}

// ham xu ly viec choi game
void playGame(Stack &undo, Stack &redo, int **board, int size, user &player, int &bestScore, char &choice, bool isOpenUndo, resume *&resumeList)
{
    char x;
    bool canMove = false;
    bool continuePlayWin = false;
    bool continuePlayLose = false;
    chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    chrono::high_resolution_clock::time_point end_time;
    chrono::seconds duration;

    fstream input;
    int numberOfUser = countNumberOfUser(input);
    user *userList = new user[numberOfUser];
    loadFileUserList(input, userList, numberOfUser);
    int index = getResumeEmpty(resumeList, player.userName);

    while (true)
    {
        x = getch();
        canMove = false;

        if (x == 'e')
        {
            exitProcess(board, size, player, userList, numberOfUser, bestScore, choice, isOpenUndo, resumeList, index);

            if (choice == '0')
                break;
        }

        // xu ly len xuonng trai phai
        if (x == 'w')
            moveUp(board, size, canMove, player.score);

        if (x == 's')
            moveDown(board, size, canMove, player.score);

        if (x == 'a')
            moveLeft(board, size, canMove, player.score);

        if (x == 'd')
            moveRight(board, size, canMove, player.score);

        // xu ly neu chon undo
        if (x == 'u' && isOpenUndo == true)
        {
            undoProcess(undo, redo, board, size, player.score);
            
            system("cls");
            printUI(board, size, player, bestScore, isOpenUndo);
            continue;
        }

        // xu ly neu chon redo
        if (x == 'r' && isOpenUndo == true)
        {
            if (redo.empty())
                continue;
            else
                redoProcess(undo, redo, board, size, player.score);
        }

        // neu bang co thay doi trang thai thi moi random va luu
        if (canMove == true)
        {
            placeRandomValueOnEmptyCell(board, size);
            dataOfNode data = {board, player.score, size};
            undo.push(data);
            redo.clear();
        }

        system("cls");
        printUI(board, size, player, bestScore, isOpenUndo);
        cout << endl;

        // xu ly khi win game
        if (isWinGame(board, size) == true && continuePlayWin == false)
        {
            winGameProcess(board, size, player, userList, numberOfUser, bestScore, choice, isOpenUndo, continuePlayWin);

            // neu nguoi choi khong tiep tuc choi khi da win game
            if (choice == '0')
            {
                // cap nhat lai resume neu nguoi choi dung resume
                if (index != -1)
                    changeResume(resumeList, index + 1, board, size, player);
                break;
            }
        }

        if (isGameEnded(board, size) == true && continuePlayLose == false)
        {
            endGameProcess(board, size, player, userList, numberOfUser, bestScore, choice, isOpenUndo, continuePlayLose);

            // neu nguoi choi khong tiep tuc choi khi da lose game
            if (choice == '0')
            {
                // cap nhat lai resume neu nguoi choi dung resume
                if (index != -1)
                {
                    changeResume(resumeList, index + 1, board, size, player);
                }
                break;
            }
        }
    }

    // lay thoi gian choi
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    player.playingTime = duration.count();
}