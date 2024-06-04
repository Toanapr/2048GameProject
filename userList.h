#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "2048.h"

#define LIST_USER_FILE "user_list.bin"
#define MAX_NAME_LENGTH 31 // 30 characters + null terminator

struct user
{
    char userName[MAX_NAME_LENGTH];
    int score;
    int playingTime;

    user()
    {
        userName[0] = '\0';
        score = 0;
        playingTime = 0;
    }
};

void loadFileUserList(std::fstream &input, user *&listUser, int numberOfUser);
void addUserInFile(std::fstream &output, user *listUser, int numberOfUser);
void enterUserName(user *listUser, int numberOfUser, char* name);
void printTop20Score(user *listUser, int numberOfUser);
int countNumberOfUser(std::fstream &input);
char* getPlayingTime(int time);
void sortScore(user *&listUser, int numberOfUser);
void formatName(char* name);
void saveUserList(user *&listUser, int &numberOfUser, user player);

#endif
