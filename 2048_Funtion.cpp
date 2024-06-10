#include "2048.h"

int randomTwoFour()
{
    int x = rand() % 10 + 1;
    if (x <= 8)
        return 2;
    else
        return 4;
}

int getBestScore(fstream &input)
{
    int hi;
    input.open(fileBestScore, ios::in | ios::binary);
    input.read((char *)&hi, sizeof(hi));
    input.close();
    return hi;
}

void saveBestScore(fstream &output, int score, int bestScore)
{
    output.open(fileBestScore, ios::out | ios::binary);

    if (score >= bestScore)
        output.write((char *)&score, sizeof(int));
    else
        output.write((char *)&bestScore, sizeof(int));

    output.close();
}

bool isWinGame(int **board, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == 2048)
                return true;

    return false;
}

void placeRandomValueOnEmptyCell(int **board, int size)
{
    int pos1 = rand() % size;
    int pos2 = rand() % size;

    while (board[pos1][pos2] != 0 && countEmptyPosition(board, size) > 0)
    {
        pos1 = rand() % size;
        pos2 = rand() % size;
    }

    board[pos1][pos2] = randomTwoFour();
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void moveLeft(int **board, int size, bool &canMove, int &score)
{
    canMove = false;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int temp = j + 1;

            while (temp < size && board[i][temp] == 0)
            {
                temp++;
            }

            if (temp >= size)
                break;

            if (board[i][j] == 0)
            {
                swap(&board[i][j], &board[i][temp]);
                j--;
                canMove = true;
            }
            else if (board[i][j] == board[i][temp])
            {
                board[i][j] *= 2;
                board[i][temp] = 0;
                canMove = true;
                score += board[i][j];
            }
        }
    }
}

void moveRight(int **board, int size, bool &canMove, int &score)
{
    canMove = false;

    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j >= 0; j--)
        {
            int temp = j - 1;

            while (temp >= 0 && board[i][temp] == 0)
            {
                temp--;
            }

            if (temp < 0)
                break;

            if (board[i][j] == 0)
            {
                swap(&board[i][j], &board[i][temp]);
                j++;
                canMove = true;
            }
            else if (board[i][j] == board[i][temp])
            {
                board[i][j] *= 2;
                board[i][temp] = 0;
                canMove = true;
                score += board[i][j];
            }
        }
    }
}

void moveDown(int **board, int size, bool &canMove, int &score)
{
    canMove = false;

    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j >= 0; j--)
        {
            int temp = j - 1;

            while (temp >= 0 && board[temp][i] == 0)
            {
                temp--;
            }

            if (temp < 0)
                break;

            if (board[j][i] == 0)
            {
                swap(&board[j][i], &board[temp][i]);
                j++;
                canMove = true;
            }
            else if (board[j][i] == board[temp][i])
            {
                board[j][i] *= 2;
                board[temp][i] = 0;
                canMove = true;
                score += board[j][i];
            }
        }
    }
}

void moveUp(int **board, int size, bool &canMove, int &score)
{
    canMove = false;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int temp = j + 1;
            while (temp < size && board[temp][i] == 0)
            {
                temp++;
            }
            if (temp >= size)
                break;
            if (board[j][i] == 0)
            {
                swap(&board[j][i], &board[temp][i]);
                j--;
                canMove = true;
            }
            else if (board[j][i] == board[temp][i])
            {
                board[j][i] *= 2;
                board[temp][i] = 0;
                canMove = true;
                score += board[j][i];
            }
        }
    }
}

void printUI(int **board, int size, user player, int &bestScore, bool isOpenUndo)
{
    if (board == NULL)
        return;

    if (bestScore < player.score)
        bestScore = player.score;

    // Define color codes
    // const string RESET = "\033[0m";
    const char BOARD = 196;
    const string BORDER_COLOR = "\033[33m";
    const string COLORS[] = {
        "\033[30;47m", // Black on White for 2
        "\033[30;43m", // Black on Yellow for 4
        "\033[30;42m", // Black on Green for 8
        "\033[30;46m", // Black on Cyan for 16
        "\033[30;44m", // Black on Blue for 32
        "\033[30;45m", // Black on Magenta for 64
        "\033[37;41m", // White on Red for 128
        "\033[37;43m", // White on Yellow for 256
        "\033[37;42m", // White on Green for 512
        "\033[37;44m", // White on Blue for 1024
        "\033[37;45m", // White on Magenta for 2048
        "\033[33;41m",
    };

    cout << BOLD << "Score: " << RESET << GREEN << player.score << RESET;
    cout << BOLD << "\t Best: " << YELLOW << bestScore << RESET << endl;
    cout << BOLD << "Name: " << BLUE << player.userName << RESET << endl;
    cout << BORDER_COLOR;
    cout << char(218);
    for (int k = 0; k < size - 1; k++)
        cout << BOARD << BOARD << BOARD << BOARD << BOARD << BOARD << char(194);
    cout << BOARD << BOARD << BOARD << BOARD << BOARD << BOARD << char(191) << RESET << endl;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int value = board[i][j];
            string color = RESET;
            if (value > 2048)
                color = COLORS[11];
            else
            {
                switch (value)
                {
                case 2:
                    color = COLORS[0];
                    break;
                case 4:
                    color = COLORS[1];
                    break;
                case 8:
                    color = COLORS[2];
                    break;
                case 16:
                    color = COLORS[3];
                    break;
                case 32:
                    color = COLORS[4];
                    break;
                case 64:
                    color = COLORS[5];
                    break;
                case 128:
                    color = COLORS[6];
                    break;
                case 256:
                    color = COLORS[7];
                    break;
                case 512:
                    color = COLORS[8];
                    break;
                case 1024:
                    color = COLORS[9];
                    break;
                case 2048:
                    color = COLORS[10];
                    break;
                default:
                    color = RESET;
                    break;
                }
            }
            cout << BORDER_COLOR << char(179) << RESET << color << setw(5) << (value != 0 ? to_string(value) : " ") << setw(5) << RESET;
        }

        if (i < size - 1)
        {
            cout << BORDER_COLOR << char(179) << endl
                 << char(195);
            for (int k = 0; k < size - 1; k++)
            {
                cout << BOARD << BOARD << BOARD << BOARD << BOARD << BOARD << char(197);
            }
            cout << BOARD << BOARD << BOARD << BOARD << BOARD << BOARD << char(180) << endl;
        }
        else
        {
            cout << BORDER_COLOR << char(179) << endl
                 << char(192);

            for (int k = 0; k < size - 1; k++)
            {
                cout << BOARD << BOARD << BOARD << BOARD << BOARD << BOARD << char(193);
            }
            cout << BOARD << BOARD << BOARD << BOARD << BOARD << BOARD << char(217) << endl;
        }
    }

    cout << RESET;
    if (isOpenUndo == true)
    {
        cout << "\033[1;36m  w \033[0m : Up   \033[1;36m a \033[0m : Left \n \033[1;36m s \033[0m : Down \033[1;36m d \033[0m : Right \n \033[1;36m e \033[0m: exit \033[1;36m  u \033[0m : undo \n \033[1;36m r \033[0m : redo\n" << RESET;
        cout << "\nPress the key to play and continue.";
    }
    else
    {
        cout << "\033[1;36m  w \033[0m : Up   \033[1;36m a \033[0m : Left \n \033[1;36m s \033[0m : Down \033[1;36m d \033[0m : Right \n \033[1;36m e \033[0m: exit" << RESET;
        cout << "\nPress the key to play and continue.\n";
    }
}

int countEmptyPosition(int **board, int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == 0)
                count++;

    return count;
}

bool isGameEnded(int **board, int size)
{
    if (countEmptyPosition(board, size) > 0)
        return false;
    else
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - 1; j++)
                if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i])
                    return false;
    }

    return true;
}

void initializeGame(Stack &undo, int **&board, int &size, user &player, int bestScore, bool isOpenUndo)
{
    player.score = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = 0;

    placeRandomValueOnEmptyCell(board, size);
    placeRandomValueOnEmptyCell(board, size);

    dataOfNode data = {board, player.score, size};
    undo.push(data);
}

void undoProcess(Stack &undo, Stack &redo, int **&board, int size, int &score)
{
    if (undo.top()->pNext == NULL)
        return;

    redo.push(undo.top()->data);
    undo.pop();
    Node *temp = undo.top();
    copyValueMatrix(temp->data.matrix, board, size);
    score = temp->data.score;
}

void redoProcess(Stack &undo, Stack &redo, int **&board, int size, int &score)
{
    Node *temp = redo.top();
    undo.push(temp->data);
    copyValueMatrix(temp->data.matrix, board, size);
    score = temp->data.score;
    redo.pop();
}

bool isHaveAlpha(string s)
{
    bool check = true;
    for (int i = 0; i < s.size(); i++)
        if (isdigit(s[i]) == 0)
            check = false;
    return check;
}

void endGameProcess(int **board, int size, user player, user *userList, int numberOfUser, int bestScore, char &choice, bool &isOpenUndo, bool &continuePlayLose)
{
    system("cls");
    cout << RED << "GameOver" << RESET << endl;

    // TODO: THONG BAO THU HANG CUA NGUOI CHOI NEU DAT TOP 20
    saveUserList(userList, numberOfUser, player);
    for (int i = 0; i < numberOfUser; i++)
    {
        if (strcmp(userList[i].userName, player.userName) == 0 && i < 20)
        {
            cout << CYAN << "Your rank: " << i + 1 << RESET << endl;
            break;
        }
    }

    if (isOpenUndo == false)
    {
        cout << GREEN << "You don't open the undo and redo mode so you can't continue play.\n";
        cout << RESET;
        choice = '0';
        system("pause");
        return;
    }

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
        // TODO: LUU TRU THONG TIN NEU NGUOI CHOI DAT TOP 20

        choice = '0';
        return;
    }
}

void winGameProcess(int **board, int size, user player, user *userList, int numberOfUser, int bestScore, char &choice, bool &isOpenUndo, bool &continuePlayWin)
{
    system("cls");
    cout << YELLOW << "Congratulation! You Win!!" << RESET << endl;

    // TODO: THONG BAO THU HANG CUA NGUOI CHOI NEU DAT TOP 20
    saveUserList(userList, numberOfUser, player);
    for (int i = 0; i < numberOfUser; i++)
    {
        if (strcmp(userList[i].userName, player.userName) == 0 && i < 20)
        {
            cout << CYAN << "Your rank: " << i + 1 << RESET << endl;
            break;
        }
    }

    cout << GREEN << "Do you want to continue? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)" << RESET << endl;
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
        continuePlayWin = true;
        system("cls");
        printUI(board, size, player, bestScore, isOpenUndo);
    }
    else
    {
        // TODO: LUU TRU THONG TIN NGUOI CHOI NEU DAT TOP 20

        choice = '0';
        return;
    }
}

void exitProcess(int **board, int size, user player, user *userList, int numberOfUser, int bestScore, char &choice, bool isOpenUndo, resume *&resumeList, int index)
{
    bool isResumed = false;
    char temp;
    char doSave;

    cout << GREEN << "Do you want to exit the game? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)" << RESET << endl;
    doSave = getch();

    while (doSave != 'y' && doSave != 'n')
    {
        cout << RED << "\nInvalid, please enter choice again (press\033[1;33m y\033[1;31m : yes or\033[1;33m n\033[1;31m : no):  " << RESET;
        doSave = getch();
    }

    if (doSave == 'y')
    {
            for (int i = 0; i < 5; i++)
            {
                if (strcmp(resumeList[i].player.userName, player.userName) == 0)
                    isResumed = true;
            }

        if (isResumed == false)
        {
            cout << GREEN << "\nDo you want to save the game to resume later? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)" << RESET << endl;
            temp = getch();
            while (temp != 'y' && temp != 'n')
            {
                // system("cls");
                cout << RED << "Invalid, please enter choice again (press\033[1;33m y\033[1;31m : yes or\033[1;33m n\033[1;31m : no):  \n"
                     << RESET;
                temp = getch();
            }
        }
        else
            temp = 'y';

        if (temp == 'y')
        {
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
            else
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

        if (x == 'w')
            moveUp(board, size, canMove, player.score);

        if (x == 's')
            moveDown(board, size, canMove, player.score);

        if (x == 'a')
            moveLeft(board, size, canMove, player.score);

        if (x == 'd')
            moveRight(board, size, canMove, player.score);

        if (x == 'u' && isOpenUndo == true)
        {
            undoProcess(undo, redo, board, size, player.score);
            
            system("cls");
            printUI(board, size, player, bestScore, isOpenUndo);
            continue;
        }

        if (x == 'r' && isOpenUndo == true)
        {
            if (redo.empty())
                continue;
            else
                redoProcess(undo, redo, board, size, player.score);
        }

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

        if (isWinGame(board, size) == true && continuePlayWin == false)
        {
            winGameProcess(board, size, player, userList, numberOfUser, bestScore, choice, isOpenUndo, continuePlayWin);
            if (choice == '0')
            {
                if (index != -1)
                    changeResume(resumeList, index + 1, board, size, player);
                break;
            }
        }

        if (isGameEnded(board, size) == true && continuePlayLose == false)
        {
            endGameProcess(board, size, player, userList, numberOfUser, bestScore, choice, isOpenUndo, continuePlayLose);
            if (choice == '0')
            {
                if (index != -1)
                {
                    changeResume(resumeList, index + 1, board, size, player);
                }
                break;
            }
        }
    }

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    player.playingTime = duration.count();
}

void startMenu(char &choice, int &size, user &player, user *userList, int numberOfUser, bool &isOpenUndo, resume *&resumeList, int &index)
{
    system("cls");
    cout << YELLOW << "WELCOME TO 2048!!!" << RESET << endl;
    cout << "   1. Resume" << endl;
    cout << "   2. Play a New Game" << endl;
    cout << "   3. Top 20" << endl;
    cout << "   4. Setting" << endl;
    cout << "   5. Exit" << endl;
    cout << "Enter Choice (press number and enter): ";

    // enter again when press another

    choice = getch();
    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5')

    {
        system("cls");
        cout << YELLOW << "WELCOME TO 2048!!!" << RESET << endl;
        cout << "   1. Resume" << endl;
        cout << "   2. Play a New Game" << endl;
        cout << "   3. Top 20" << endl;
        cout << "   4. Setting" << endl;
        cout << "   5. Exit" << endl;
        cout << RED << "Invalid, please enter choice again: " << RESET;
        choice = getch();
    }

    // exit game
    if (choice == '5')
    {
        system("cls");
        cout << YELLOW << "Thank you and have a good day!!!\n"
             << RESET;
        return;
    }

    // new game
    if (choice == '2')
    {
        system("cls");
        enterUserName(userList, numberOfUser, player.userName);
    }

    // top 20
    if (choice == '3')
    {
        system("cls");
        printTop20Score(userList, numberOfUser);
        system("pause");
    }

    if (choice == '4')
    {
        system("cls");
        settingGame(size, isOpenUndo);
    }

    // resume
    if (choice == '1')
    {
        system("cls");

        printResume(resumeList);
        cout << "Enter the number of the game you want to resume: ";

        string m;
        m = getch();
        resumeList[5].size = -1;
        // while (m != '1' && m != '2' && m != '3' && m != '4' && m != '5' && m != '6' && resumeList[m - '0' - 1].size == 0)
        while (isHaveAlpha(m) == false || stoi(m) < 1 || stoi(m) > 7 || resumeList[stoi(m) - 1].size == 0)
        {
            system("cls");
            printResume(resumeList);
            cout << RED << "Invalid, please enter the number of the game you want to resume again: " << RESET;
            m = getch();
        }

        index = stoi(m);

        system("cls");
        if (index != 6)
        {
            cout << BLUE << "Resume the game successfully " << RESET;
            Sleep(1200);
        }
        system("cls");
    }

    system("cls");
}

void settingGame(int &size, bool &isOpenUndo)
{
    cout << YELLOW << "Settings Game.\n" << RESET;
    cout << "1. Change the size game board.\n";
    cout << "2. Open the undo and redo.\n";
    cout << "3. Exit.\n";
    cout << "\n Enter choice: ";

    char choice;
    while (true)
    {
        choice = getch();
        while (choice != '1' && choice != '2' && choice != '3')
        {
            system("cls");
            cout << YELLOW << "Settings Game.\n" << RESET;
            cout << "1. Change the size game board.\n";
            cout << "2. Open the undo and redo.\n";
            cout << "3. Exit.\n\n";
            cout << RED << "Invalid! Please choice again: " << RESET;
            choice = getch();
        }

        if (choice == '3')
            break;

        if (choice == '1')
        {
            system("cls");
            cout << GREEN << "Enter gameboard size (from 4x4 to 10x10): " << RESET;
            string size_s;
            cin >> size_s;

            while (isHaveAlpha(size_s) == false || stoi(size_s) < 4 || stoi(size_s) > 10)
            {
                system("cls");
                cout << RED << "Invalid, please enter gameboard (from 4x4 to 10x10) size again: " << RESET;
                cin >> size_s;
            }

            size = stoi(size_s);
            cout << BLUE << "The gameboard size has been changed " << RESET;
            Sleep(1200);

            system("cls");
            cout << YELLOW << "Settings Game.\n" << RESET;
            cout << "1. Change the size game board.\n";
            cout << "2. Open the undo and redo.\n";
            cout << "3. Exit.\n";
            cout << "\n Enter choice: ";
        }

        if (choice == '2')
        {
            system("cls");
            cout << GREEN << "Do you want to open undo and redo mode? (press\033[1;33m y\033[1;32m : yes or\033[1;33m n\033[1;32m : no)\n"
                 << RESET;
            char tmp;
            tmp = getch();
            while (tmp != 'y' && tmp != 'n')
            {
                system("cls");
                cout << RED << "Invalid, please enter the undo and redo mode again (press\033[1;33m y\033[1;31m : yes or\033[1;33m n\033[1;31m : no): " << RESET;
                tmp = getch();
            }

            if (tmp == 'y')
            {
                isOpenUndo = true;
                system("cls");
                cout << BLUE << "Undo and Redo was opened " << RESET;
                Sleep(1200);
            }
            else
            {
                isOpenUndo = false;
                system("cls");
                cout << BLUE << "Undo and Redo was closed " << RESET;
                Sleep(1200);
            }
            system("cls");
            cout << YELLOW << "Settings Game.\n" << RESET;
            cout << "1. Change the size game board.\n";
            cout << "2. Open the undo and redo.\n";
            cout << "3. Exit.\n";
            cout << "\n Enter choice: ";
        }
    }
}