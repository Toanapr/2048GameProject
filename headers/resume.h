#ifndef _RESUME_H_
#define _RESUME_H_

#include "2048.h"

struct resume
{
    int board[10][10];
    int size;
    user player;

    resume()
    {
        this->board[10][10];
        this->size = 0;
        this->player.userName[0] = '\0';
        this->player.score = 0;
        this->player.playingTime = 0;
    }
};

void loadResumeFile(resume *&resumeList);
void saveResume(resume *resumeList);
int getResumeEmpty(resume *resumeList, char *name);
void changeResume(resume *&resumeList, int index, int **board, int size, user player);
void printResume(resume *resumeList);
bool isExistResume(resume *resumeList, char *name);

#endif