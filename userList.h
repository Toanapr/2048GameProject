#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "2048.h"

#define LIST_USER_FILE "user_list.txt"

struct user
{
    std::string userName;
    int score;
    int playingTime;

    user()
    {
        userName = "";
        score = 0;
        playingTime = 0;
    }
};

void loadFileUserList(std::fstream &input, user *&listUser, int numberOfUser);
void addUserInFile(std::fstream &output, user User);
std::string enterUserName(user *listUser, int numberOfUser);
void printTop20Score(user *listUser, int numberOfUser);
int countNumberOfUser(std::fstream &input);
std::string getPlayingTime(int time);

#endif