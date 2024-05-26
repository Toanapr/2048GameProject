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
        // output << score;
        output.write((char *)&score, sizeof(int));
    else
        // output << bestScore;
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
int **allocateMatrix(int size)
{
    int **board = new int *[size];
    for (int i = 0; i < size; i++)
        board[i] = new int[size];
    return board;
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
    cout << "Score: " << player.score;
    cout << "\t Best: " << bestScore << endl;
    cout << "Name: " << player.userName << endl;
    for (int k = 0; k < size; k++)
        cout << "+-------";
    cout << "+" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] != 0)
                cout << "|" << setw(4) << board[i][j] << setw(4);
            else
                cout << "|" << setw(4) << ' ' << setw(4);
        }
        cout << "|" << endl;
        for (int k = 0; k < size; k++)
        {
            cout << "+-------";
        }
        cout << "+" << endl;
    }
    if (isOpenUndo == true)
    {
        cout << " w : Up    a : Left \n s : Down  d : Right \n q : exit  z : undo  y : redo\n";
        cout << "\nPress the key to play and continue.";
    }
    else
    {
        cout << " w : Up    a : Left \n s : Down  d : Right \n q : exit";
        cout << "\nPress the key to play and continue.";
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
    board = allocateMatrix(size);

    player.score = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = 0;

    placeRandomValueOnEmptyCell(board, size);
    placeRandomValueOnEmptyCell(board, size);

    printUI(board, size, player, bestScore, isOpenUndo);

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
void playGame(Stack &undo, Stack &redo, int **board, int size, user &player, int &bestScore, char &choice, bool isOpenUndo)
{
    char x;
    bool canMove = false;
    chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

    while (true)
    {
        x = getch();
        canMove = false;

        if (x == 'q')
        {
            choice = '5';
            system("cls");

            chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
            chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
            player.playingTime = duration.count();

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
            
        if (x == 'z' && isOpenUndo == true)
        {
            undoProcess(undo, redo, board, size, player.score);
            system("cls");
            printUI(board, size, player, bestScore, isOpenUndo);
            continue;
        }

        if (x == 'y' && isOpenUndo == true)
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

        if (isWinGame(board, size) == true)
        {
            system("cls");
            cout << "You Win!!" << endl;
            system("pause");
            // cout << "Do you want to continue? (press y: yes or n: no)" << endl;
            // char m;
            // cin >> m;
            // if (m == 'y')
            // continue;
            // else
            choice = '5';
            break;
        }

        if (isGameEnded(board, size) == true)
        {
            system("cls");
            cout << "GameOver" << endl;
            system("pause");
            choice = '5';

            chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
            chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
            player.playingTime = duration.count();
            
            break;
        }
    }
}
void startMenu(char &choice, int &size, user &player, user *userList, int numberOfUser, bool &isOpenUndo)
{
    system("cls");
    cout << "" << endl;
    cout << "WELCOME TO 2048!!!" << endl;
    cout << "   1. Resume" << endl;
    cout << "   2. Play a New Game" << endl;
    cout << "   3. Top 20" << endl;
    cout << "   4. Setting" << endl;
    cout << "   5. Exit" << endl;
    cout << "Enter Choice (press number and enter): ";

    // enter again when press another
    cin >> choice;
    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5')
    {
        system("cls");
        cout << "WELCOME TO 2048!!!" << endl;
        cout << "   1. Resume" << endl;
        cout << "   2. Play a New Game" << endl;
        cout << "   3. Top 20" << endl;
        cout << "   4. Setting" << endl;
        cout << "   5. Exit" << endl;
        cout << "Invalid, please enter choice again: ";
        cin >> choice;
    }

    // exit game
    if (choice == '5')
    {
        system("cls");
        cout << "Thank you and have a good day!!!\n";
        return;
    }

    // new game
    if (choice == '2')
    {
        system("cls");
        player.userName = enterUserName(userList, numberOfUser);
    }

    // top 20
    if (choice == '3')
    {
        system("cls");
        printTop10Score(userList, numberOfUser);
        system("pause");
    }

    if (choice == '4')
    {
        system("cls");
        settingGame(size, isOpenUndo);
    }

    system("cls");
}

bool isHaveAlpha(string s)
{
    bool check = true;
    for (int i = 0; i < s.size(); i++)
        if (isdigit(s[i]) == 0)
            check = false;     
    return check;
}
void settingGame(int &size, bool &isOpenUndo)
{
    cout << "Settings Game.\n";
    cout << "1. Change the size game board.\n";
    cout << "2. Open the undo and redo.\n";
    cout << "3. Exit.\n";

    char choice;
    while (true)
    {
        cin >> choice;
        while (choice != '1' && choice != '2' && choice != '3')
        {
            system("cls");
            cout << "Invalid! Please choice again: ";
            cin >> choice;
        }

        if (choice == '3')
            break;

        if (choice == '1')
        {
            system("cls");
            cout << "Enter gameboard size (from 4x4 to 10x10): ";
            string size_s;
            cin >> size_s;

            while (isHaveAlpha(size_s) == false || stoi(size_s) < 4 || stoi(size_s) > 10)
            {
                system("cls");
                cout << "Invalid, please enter gameboard size again: ";
                cin >> size_s;
            }

            size = stoi(size_s);
            cout << "The gameboard size has been changed ";
            Sleep(1200);

            system("cls");
            cout << "Settings Game.\n";
            cout << "1. Change the size game board.\n";
            cout << "2. Open the undo and redo.\n";
            cout << "3. Exit.\n";
        }

        if (choice == '2')
        {
            system("cls");
            cout << "Do you want to open undo and redo mode? (press y : yes or n : no)\n";
            char tmp;
            cin >> tmp;
            while (tmp != 'y' && tmp != 'n')
            {
                system("cls");
                cout << "Invalid, please enter again: ";
                cin >> tmp;
            }

            if (tmp == 'y')
            {
                isOpenUndo = true;
                system("cls");
                cout << "Undo and Redo was opened ";
                Sleep(1200);
            }
            else
            {
                isOpenUndo = false;
                system("cls");
                cout << "Undo and Redo was closed ";
                Sleep(1200);
            }
            system("cls");
            cout << "Settings Game.\n";
            cout << "1. Change the size game board.\n";
            cout << "2. Open the undo and redo.\n";
            cout << "3. Exit.\n";
        }
    }
}