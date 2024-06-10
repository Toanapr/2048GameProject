#ifndef _2048_H_
#define _2048_H_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include "LinkedList.h"
#include "stack.h"
#include <fstream>
#include <string>
#include <cstring>
#include "userList.h"
#include "resume.h"

#define fileBestScore "best_score.bin"

using namespace std;

const string RED = "\033[1;31m";
const string BLUE = "\033[1;34m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string CYAN = "\033[1;36m";
const string RESET = "\033[0m";

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
void playGame(Stack &undo, Stack &redo, int **board, int size, user &player, int &bestScore, char &choice, bool isOpenUndo, resume *&resumeList);
void startMenu(char &choice, int &size, user &player, user *userList, int numberOfUser, bool &isOpenUndo, resume *&resumeList, int &index);
void saveBestScore(fstream &output, int score, int bestScore);
int getBestScore(fstream &input);
void settingGame(int &size, bool &isOpenUndo);

#endif