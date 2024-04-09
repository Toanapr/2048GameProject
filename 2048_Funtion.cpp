#include "2048.h"

void placeRandomValueOnEmptyCell(int **board, int size)
{
    int pos1 = rand() % size;
    int pos2 = rand() % size;

    while (board[pos1][pos2] != 0 && countEmptyPosition(board, size) > 0)
    {
        pos1 = rand() % size;
        pos2 = rand() % size;
    }

    board[pos1][pos2] = 2;
}
int **allocateMatrix(int size)
{
    int **board = new int *[size];
    for (int i = 0; i < size; i++)
        board[i] = new int[size];
    return board;
}
void creatNewGame(int **&board, int &size, int &score)
{
    board = allocateMatrix(size);
    score = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = 0;
    placeRandomValueOnEmptyCell(board, size);
    placeRandomValueOnEmptyCell(board, size);
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
void printUI(int **board, int size, int score)
{
    Sleep(150);
    if (board == NULL)
        return;
    cout << "Score: " << score << endl;
    for (int k = 0; k < size; k++)
    {
        cout << "+-----";
    }
    cout << "+" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] != 0)
                cout << "|" << setw(3) << board[i][j] << "  ";
            else
                cout << "|" << setw(3) << '.' << "  ";
        }
        cout << "|" << endl;
        for (int k = 0; k < size; k++)
        {
            cout << "+-----";
        }
        cout << "+" << endl;
    }
    cout << " w : Up    a : Left \n s : Down  d : Right \n q : exit  z : undo\n ";
    cout << "\nPress the key to play and continue.";
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

void initializeGame(List &undo, int **&board, int &size, int &score)
{
    creatNewGame(board, size, score);
    printUI(board, size, score);
    createList(undo);
    Node *temp = createNode(board, size, score);
    addHead(undo, temp);
}
void undoProcess(List &undo, int **&board, int size, int &score)
{
    if (undo.pHead->pNext == NULL)
        return;
    deleteHead(undo);
    copyMatrix(undo.pHead->matrix, board, size);
    score = undo.pHead->score;
}
void playGame(List &undo, int **board, int size, int &score, char &choice)
{
    char x;
    bool canMove = false;

    while (true)
    {
        // cin >> x;
        x = getch();
        canMove = false;
        if (x == 'q')
        {
            choice = '2';
            system("cls");
            break;
        }
        if (x == 'w')
            moveUp(board, size, canMove, score);
        if (x == 's')
            moveDown(board, size, canMove, score);
        if (x == 'a')
            moveLeft(board, size, canMove, score);
        if (x == 'd')
            moveRight(board, size, canMove, score);
        if (x == 'z')
        {
            undoProcess(undo, board, size, score);
            system("cls");
            printUI(board, size, score);
            continue;
        }
        if (canMove == true)
        {
            placeRandomValueOnEmptyCell(board, size);
            Node *temp = createNode(board, size, score);
            addHead(undo, temp);
        }
        system("cls");
        printUI(board, size, score);
        cout << endl;
        if (isGameEnded(board, size) == true)
        {
            system("cls");
            cout << "GameOver" << endl;
            system("pause");
            choice = '2';
            break;
        }
    }
}
void startMenu(char &choice, int &size)
{
    system("cls");
    cout << "WELCOME TO 2048!!!" << endl;
    cout << "   1. Play a New Game" << endl;
    cout << "   2. Exit" << endl;
    cout << "Enter Choice (press number and enter): ";
    cin >> choice;
    while (choice != '1' && choice != '2')
    {
        system("cls");
        cout << "WELCOME TO 2048!!!" << endl;
        cout << "   1. Play a New Game" << endl;
        cout << "   2. Exit" << endl;
        cout << "Invalid, please enter choice again: ";
        cin >> choice;
    }
    if (choice == '2')
    {
        system("cls");
        cout << "Thank you and have a good day!!!\n";
        // system("pause");
        return;
    }
    system("cls");
    cout << "Enter gameboard size (press number and enter): ";
    cin >> size;
    while (size <= 0)
    {
        system("cls");
        cout << "Invalid, please enter gameboard size again: ";
        cin >> size;
    }
    system("cls");
}