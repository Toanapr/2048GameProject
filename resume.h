#ifndef _RESUME_H_
#define _RESUME_H_

#include "2048.h"

#define RESUME_FILE1 "resume1.bin"
#define RESUME_FILE2 "resume2.bin"
#define RESUME_FILE3 "resume3.bin"
#define RESUME_FILE4 "resume4.bin"
#define RESUME_FILE5 "resume5.bin"

struct resume
{
    int board[10][10];
    int size;
    user player;

    resume()
    {
        board[10][10];
        size = 0;
        player.userName[0] = '\0';
        player.score = 0;
        player.playingTime = 0;
    }
};

void loadResumeFile(resume *&resumeList);
void saveResume(resume *resumeList);
int getResumeEmpty(resume *resumeList, char *name);
void changeResume(resume *&resumeList, int index, int **board, int size, user player, bool isOpenUndo);
void printResume(resume *resumeList);
bool isExistResume(resume *resumeList, char *name);

#endif