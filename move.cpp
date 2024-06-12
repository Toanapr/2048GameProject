#include "headers/2048.h"

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

            while (temp < size && board[i][temp] == 0) // tim vi tri cac o con trong de don
            {
                temp++;
            }

            if (temp >= size)
                break;

            if (board[i][j] == 0) // neu o trong thi don qua
            {
                swap(&board[i][j], &board[i][temp]);
                j--;
                canMove = true;
            }
            else if (board[i][j] == board[i][temp]) // neu giong nhau thi hop nhat 
            {
                board[i][j] *= 2; // hop nhat
                board[i][temp] = 0; // cap nhat lai o khi da hop nhat
                canMove = true;
                score += board[i][j]; // cap nhat lai diem
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
