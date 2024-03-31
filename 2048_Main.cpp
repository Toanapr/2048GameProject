#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void random(int **a, int n)
{
    int pos1 = rand() % n;
    int pos2 = rand() % n;
    a[pos1][pos2] = 2;
    int pos3;
    int pos4;
    do
    {
        pos3 = rand() % n;
        pos4 = rand() % n;
        a[pos3][pos4] = 2;
    } while (pos1 == pos3 && pos2 == pos4);
}
int **allocateMatrix(int n)
{
    n = 4;
    int **a = new int *[n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];
    return a;
}
void creatNewGame(int **&a, int &n)
{
    a = allocateMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    random(a, n);
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void move(int **a, int n, int index, bool isRow)
{
    if (!isRow)
    {
        for (int i = 0; i < n; i++)
        {
            int temp = i + 1;
            while (a[i][index])
                ;
        }
    }
}
void moveLeft(int **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp = j + 1;
            while (temp < n && a[i][temp] == 0)
            {
                temp++;
            }
            if (temp >= n)
                break;
            if (a[i][j] == 0)
            {
                swap(&a[i][j], &a[i][temp]);
                j--;
            }
            if (a[i][j] == a[i][temp])
            {
                a[i][j] *= 2;
                a[i][temp] = 0;
            }
        }
    }
}
void moveRight(int **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            int temp = j - 1;
            while (temp >= 0 && a[i][temp] == 0)
            {
                temp--;
            }
            if (temp < 0)
                break;
            if (a[i][j] == 0)
            {
                swap(&a[i][j], &a[i][temp]);
                j++;
            }
            if (a[i][j] == a[i][temp])
            {
                a[i][j] *= 2;
                a[i][temp] = 0;
            }
        }
    }
}
void moveDown(int **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            int temp = j - 1;
            while (temp >= 0 && a[temp][i] == 0)
            {
                temp--;
            }
            if (temp < 0)
                break;
            if (a[j][i] == 0)
            {
                swap(&a[j][i], &a[temp][i]);
                j++;
            }
            else if (a[j][i] == a[temp][i])
            {
                a[j][i] *= 2;
                a[temp][i] = 0;
            }
        }
    }
}
void moveUp(int **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp = j + 1;
            while (temp < n && a[temp][i] == 0)
            {
                temp++;
            }
            if (temp >= n)
                break;
            if (a[j][i] == 0)
            {
                swap(&a[j][i], &a[temp][i]);
                j--;
            }
            else if (a[j][i] == a[temp][i])
            {
                a[j][i] *= 2;
                a[temp][i] = 0;
            }
        }
    }
}
void printUI(int **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
                cout << setw(4) << a[i][j] << " ";
            else
                cout << setw(4) << '.' << " ";
        }
        cout << endl;
    }
}
int countEmptyPosition(int **a, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j] == 0)
                count++;
    return count;
}
bool isGameEnded(int **a, int n)
{
    if (countEmptyPosition(a, n) > 0)
        return false;
    else
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n - 1; j++)
                if (a[i][j] == a[i][j + 1] || a[j][i] == a[j + 1][i])
                    return false;
    }
    return true;
}
void deletePoiter(int **&a, int n)
{
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete a;
}
int main()
{
    int **a;
    int n = 4;
    srand(time(0));
    creatNewGame(a, n);
    printUI(a, n);
    char x;
    while (true)
    {
        cin >> x;
        if (x == 'w')
            moveUp(a, n);
        if (x == 's')
            moveDown(a, n);
        if (x == 'a')
            moveLeft(a, n);
        if (x == 'd')
            moveRight(a, n);
        if (x == 'q')
            break;
        int pos3 = rand() % n;
        int pos4 = rand() % n;
        while (a[pos3][pos4] != 0 && countEmptyPosition(a, n) > 0)
        {
            pos3 = rand() % n;
            pos4 = rand() % n;
        }
        a[pos3][pos4] = 2;
        printUI(a, n);
        cout << endl;
        if (isGameEnded(a, n) == true)
        {
            cout << "GameOver" << endl;
            break;
        }
    }
    moveRight(a, n);
    printUI(a, n);
    deletePoiter(a, n);
    return 0;
}