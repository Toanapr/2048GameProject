#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>


using namespace std;

void random(int **a, int n);
int **allocateMatrix(int n);
void creatNewGame(int **&a, int &n);
void swap(int *a, int *b);
void moveLeft(int **a, int n, bool &canMove);
void moveRight(int **a, int n, bool &canMove);
void moveDown(int **a, int n, bool &canMove);
void moveUp(int **a, int n, bool &canMove);
void printUI(int **a, int n);
int countEmptyPosition(int **a, int n);
bool isGameEnded(int **a, int n);
void deletePoiter(int **&a, int n);
