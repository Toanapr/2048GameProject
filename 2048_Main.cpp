#include "2048.h"
#include "undoButton.h"

void random(int **board, int n)
{
    int pos1 = rand() % n;
    int pos2 = rand() % n;
    board[pos1][pos2] = 2;
    int pos3;
    int pos4;
    do
    {
        pos3 = rand() % n;
        pos4 = rand() % n;
        board[pos3][pos4] = 2;
    } while (pos1 == pos3 && pos2 == pos4);
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
    random(board, n);
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// void move(int **board, int n, int index, bool isRow)
// {
//     if (!isRow)
//     {
//         for (int i = 0; i < n; i++)
//         {
//             int temp = i + 1;
//             while (board[i][index])
//                 ;
//         }
//     }
// }
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
int main()
{
    int **board;
    int n = 4;
    int score;
    srand(time(0));
    List undo;
    initializeGame(undo, board, n, score);

    char x;
    bool canMove = false;

    while (true)
    {
        cin >> x;
        canMove = false;
        if (x == 'q')
            break;
        if (x == 'w')
            moveUp(board, n, canMove, score);
        if (x == 's')
            moveDown(board, n, canMove, score);
        if (x == 'a')
            moveLeft(board, n, canMove, score);
        if (x == 'd')
            moveRight(board, n, canMove, score);
        if (x == 'z')
        {
            deleteHead(undo);
            board = undo.pHead->matrix;
            score = undo.pHead->score;
            printUI(board, n, score);
            continue;
        }
        if (canMove == true)
        {
            int pos3 = rand() % n;
            int pos4 = rand() % n;
            while (board[pos3][pos4] != 0 && countEmptyPosition(board, n) > 0)
            {
                pos3 = rand() % n;
                pos4 = rand() % n;
            }
            board[pos3][pos4] = 2;
        }
        Node *temp = createNode(board, n, score);
        addHead(undo, temp);
        printUI(board, n, score);
        cout << endl;
        if (isGameEnded(board, n) == true)
        {
            cout << "GameOver" << endl;
            break;
        }
    }

    deleteMatrix(board, n);
    deleteList(undo, n);
    return 0;
}