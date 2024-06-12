#include "headers/2048.h"

// random 2, 4 voi ti le 20%, 80%
int randomTwoFour()
{
    int x = rand() % 10 + 1;
    if (x <= 8)
        return 2;
    else
        return 4;
}

// lay bestScore tu file
int getBestScore(fstream &input)
{
    int hi;
    input.open(fileBestScore, ios::in | ios::binary);
    input.read((char *)&hi, sizeof(hi));
    input.close();
    return hi;
}

// luu bestScore lai vo file
void saveBestScore(fstream &output, int score, int bestScore)
{
    output.open(fileBestScore, ios::out | ios::binary);

    if (score >= bestScore)
        output.write((char *)&score, sizeof(int));
    else
        output.write((char *)&bestScore, sizeof(int));

    output.close();
}

// random 2,4 vao o trong trong bang
void placeRandomValueOnEmptyCell(int **board, int size)
{
    int pos1 = rand() % size;
    int pos2 = rand() % size;

    while (board[pos1][pos2] != 0 && countEmptyPosition(board, size) > 0) // neu o do da ton tai thi random lai
    {
        pos1 = rand() % size;
        pos2 = rand() % size;
    }

    board[pos1][pos2] = randomTwoFour();
}

// in bang choi
void printUI(int **board, int size, user player, int &bestScore, bool isOpenUndo)
{
    if (board == NULL)
        return;

    if (bestScore < player.score) // cap nhat lai bestScore neu nguoi choi lon diem hon
        bestScore = player.score;

    // Define color codes
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

    // in thong tin
    cout << BOLD << "Score: " << RESET << GREEN << player.score << RESET;
    cout << BOLD << "\t Best: " << YELLOW << bestScore << RESET << endl;
    cout << BOLD << "Name: " << BLUE << player.userName << RESET << endl;

    // ve bang
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

    // in huong dan cac phim choi
    if (isOpenUndo == true)
    {
        cout << "\033[1;36m  w \033[0m : Up   \033[1;36m a \033[0m : Left \n \033[1;36m s \033[0m : Down \033[1;36m d \033[0m : Right \n \033[1;36m e \033[0m : exit \033[1;36m u \033[0m : undo \n \033[1;36m r \033[0m : redo\n" << RESET;
        cout << "\nPress the key to play and continue.\n";
    }
    else
    {
        cout << "\033[1;36m  w \033[0m : Up   \033[1;36m a \033[0m : Left \n \033[1;36m s \033[0m : Down \033[1;36m d \033[0m : Right \n \033[1;36m e \033[0m: exit" << RESET;
        cout << "\nPress the key to play and continue.\n";
    }
}

// khoi tao mot new game
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

// xu ly undo
void undoProcess(Stack &undo, Stack &redo, int **&board, int size, int &score)
{
    if (undo.top()->pNext == NULL)
        return;

    redo.push(undo.top()->data);
    undo.pop();
    Node *temp = undo.top();
    copyValueMatrix(temp->data.matrix, board, size); // sao chep value cua matrix vao board
    score = temp->data.score;
}

// xu ly redo
void redoProcess(Stack &undo, Stack &redo, int **&board, int size, int &score)
{
    Node *temp = redo.top();
    undo.push(temp->data);
    copyValueMatrix(temp->data.matrix, board, size); // sao chep value cua matrix vao board
    score = temp->data.score;
    redo.pop();
}

// ham kiem tra co ki tu la chu cai khong
bool isHaveAlpha(string s)
{
    bool check = true;
    for (int i = 0; i < s.size(); i++)
        if (isdigit(s[i]) == 0)
            check = false;
    return check;
}

// in menu bat dau
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

    // setting game
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

// chuc nang setting game
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