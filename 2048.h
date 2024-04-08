#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


void random(int **a, int n);
int **allocateMatrix(int n);
void creatNewGame(int **&a, int &n, int &score);
void swap(int *a, int *b);
void moveLeft(int **a, int n, bool &canMove, int &score);
void moveRight(int **a, int n, bool &canMove, int &score);
void moveDown(int **a, int n, bool &canMove, int &score);
void moveUp(int **a, int n, bool &canMove, int &score);
void printUI(int **a, int n, int score);
int countEmptyPosition(int **a, int n);
bool isGameEnded(int **a, int n);