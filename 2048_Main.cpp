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
void creatNewGame(int **&a, int &n)
{
    n = 4;
    a = new int *[n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    random(a, n);
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
void deletePoiter(int **&a, int n)
{
    for (int i = 0; i < n; i++)
        delete[] a[i];
}
int main()
{
    int **a;
    int n = 4;
    srand(time(0));
    creatNewGame(a, n);
    printUI(a, n);
    deletePoiter(a, n);
    return 0;
}