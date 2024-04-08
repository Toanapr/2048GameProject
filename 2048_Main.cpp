#include "2048.h"
#include "undoButton.h"

void placeRandomValueOnEmptyCell(int **&board, int size)
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
int **allocateMatrix(int n)
{
    n = 4;
    int **board = new int *[n];
    for (int i = 0; i < n; i++)
        board[i] = new int[n];
    return board;
}
void creatNewGame(int **&board, int &n, int &score)
{
    board = allocateMatrix(n);
    score = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;
    placeRandomValueOnEmptyCell(board, n);
    placeRandomValueOnEmptyCell(board, n);
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void moveLeft(int **board, int n, bool &canMove, int &score)
{
    canMove = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp = j + 1;
            while (temp < n && board[i][temp] == 0)
            {
                temp++;
            }
            if (temp >= n)
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
void moveRight(int **board, int n, bool &canMove, int &score)
{
    canMove = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
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
void moveDown(int **board, int n, bool &canMove, int &score)
{
    canMove = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
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
void moveUp(int **board, int n, bool &canMove, int &score)
{
    canMove = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp = j + 1;
            while (temp < n && board[temp][i] == 0)
            {
                temp++;
            }
            if (temp >= n)
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
void printUI(int **board, int n, int score)
{
    if (board == NULL)
        return;
    cout << "Score: " << score << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != 0)
                cout << setw(4) << board[i][j] << " ";
            else
                cout << setw(4) << '.' << " ";
        }
        cout << endl;
    }
}
int countEmptyPosition(int **board, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == 0)
                count++;
    return count;
}
bool isGameEnded(int **board, int n)
{
    if (countEmptyPosition(board, n) > 0)
        return false;
    else
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n - 1; j++)
                if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i])
                    return false;
    }
    return true;
}

void gameStart(int **&board, int &n, List &undo)
{
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
    deleteHead(undo);
    board = undo.pHead->matrix;
    score = undo.pHead->score;
}
void playGame(List &undo, int **&board, int size, int &score)
{
    char x;
    bool canMove = false;

    while (true)
    {
        cin >> x;
        canMove = false;
        if (x == 'q')
            break;
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
            printUI(board, size, score);
            continue;
        }
        if (canMove == true)
        {
            placeRandomValueOnEmptyCell(board, size);
        }
        Node *temp = createNode(board, size, score);
        addHead(undo, temp);
        printUI(board, size, score);
        cout << endl;
        if (isGameEnded(board, size) == true)
        {
            cout << "GameOver" << endl;
            break;
        }
    }
}

int main()
{
    int **board;
    int n = 4;
    int score;
    srand(time(0));
    List undo;
    initializeGame(undo, board, n, score);

    playGame(undo, board, n, score);

    deleteMatrix(board, n);
    deleteList(undo, n);
    return 0;
}