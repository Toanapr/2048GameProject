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

#define fileBestScore ".\\binary_files\\best_score.bin"

using namespace std;

const string RED = "\033[1;31m";
const string BLUE = "\033[1;34m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string CYAN = "\033[1;36m";
const string MAGENTA = "\033[1;35m";
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";

void undoProcess(Stack &undo, Stack &redo, int **&board, int size, int &score);
void redoProcess(Stack &undo, Stack &redo, int **&board, int size, int &score);

void swap(int *a, int *b);
void moveLeft(int **board, int size, bool &canMove, int &score);
void moveRight(int **board, int size, bool &canMove, int &score);
void moveDown(int **board, int size, bool &canMove, int &score);
void moveUp(int **board, int size, bool &canMove, int &score);

bool isWinGame(int **board, int size);
bool isGameEnded(int **board, int size);
void playGame(Stack &undo, Stack &redo, int **board, int size, user &player, int &bestScore, char &choice, bool isOpenUndo, resume *&resumeList);

void printUI(int **board, int size, user player, int &bestScore, bool isOpenUndo);
int countEmptyPosition(int **board, int size);
void placeRandomValueOnEmptyCell(int **board, int size);
void initializeGame(Stack &undo, int **&board, int &size, user &player, int bestScore, bool isOpenUndo);
void startMenu(char &choice, int &size, user &player, user *userList, int numberOfUser, bool &isOpenUndo, resume *&resumeList, int &index);
void saveBestScore(fstream &output, int score, int bestScore);
int getBestScore(fstream &input);
void settingGame(int &size, bool &isOpenUndo);

void handleResumedGame(int **board, resume *resumeList, user *userList, int numberOfUser, int index, user &player, int &bestScore, char &choice, Stack undo, Stack redo, fstream &loadUser);
void handleNewGame(int size, user &player, int &bestScore, char &choice, bool isOpenUndo, resume *resumeList, Stack &undo, Stack &redo, fstream &output);

#endif