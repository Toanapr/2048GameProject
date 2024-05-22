#ifndef _2048_H_
#define _2048_H_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include "LinkedList.h"
#include "stack.h"
#include <fstream>
#include <string>
#include "userList.h"

#define fileBestScore "best_score.bin"

using namespace std;

int **allocateMatrix(int size);
void swap(int *a, int *b);
void moveLeft(int **board, int size, bool &canMove, int &score);
void moveRight(int **board, int size, bool &canMove, int &score);
void moveDown(int **board, int size, bool &canMove, int &score);
void moveUp(int **board, int size, bool &canMove, int &score);
void printUI(int **board, int size, user player, int &bestScore, bool isOpenUndo);
int countEmptyPosition(int **board, int size);
bool isGameEnded(int **board, int size);
void placeRandomValueOnEmptyCell(int **board, int size);
void initializeGame(Stack &undo, int **&board, int &size, user &player, int bestScore, bool isOpenUndo);
void playGame(Stack &undo, Stack &redo, int **board, int size, user &player, int &bestScore, char &choice, bool isOpenUndo);
void startMenu(char &choice, int &size, user &player, user *userList, int numberOfUser,bool &isOpenUndo);
void saveBestScore(fstream &output, int score, int bestScore);
int getBestScore(fstream &input);
void settingGame(int &size, bool &isOpenUndo);

#endif