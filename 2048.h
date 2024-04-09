#ifndef _2048_H_
#define _2048_H_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include "undoButton.h"

using namespace std;

int **allocateMatrix(int size);
void creatNewGame(int **&board, int &size, int &score);
void swap(int *a, int *b);
void moveLeft(int **board, int size, bool &canMove, int &score);
void moveRight(int **board, int size, bool &canMove, int &score);
void moveDown(int **board, int size, bool &canMove, int &score);
void moveUp(int **board, int size, bool &canMove, int &score);
void printUI(int **board, int size, int score);
int countEmptyPosition(int **board, int size);
bool isGameEnded(int **board, int size);
void placeRandomValueOnEmptyCell(int **board, int size);
void printUI(int **board, int size, int score);
void initializeGame(List &undo, int **&board, int &size, int &score);
void playGame(List &undo, int **board, int size, int &score, char &choice);
void startMenu(char &choice, int &size);

#endif