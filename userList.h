#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "2048.h"

#define LIST_USER_FILE "user_list.txt"

struct user
{
    std::string userName;
    int score;
    user()
    {
        userName = "";
        score = 0;
    }
};
void loadFileUserList(std::fstream &input, user *&listUser, int &numberOfUser);
void addUserInFile(std::fstream &output, user User);
std::string enterUserName(user *listUser, int numberOfUser);
void printTop10Score(user *listUser, int numberOfUser);
int countNumberOfUser(std::fstream &input);

#endif