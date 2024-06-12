#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "2048.h"


#define LIST_USER_FILE ".\\binary_files\\user_list.bin"
#define MAX_NAME_LENGTH 31 // 30 characters + null terminator

struct user
{
    char userName[MAX_NAME_LENGTH];
    int score;
    int playingTime;

    user()
    {
        this->userName[0] = '\0';
        this->score = 0;
        this->playingTime = 0;
    }
};

void loadFileUserList(std::fstream &input, user *&listUser, int numberOfUser);
void addUserInFile(std::fstream &output, user *listUser, int numberOfUser);
bool isExistUserName(user *listUser, int numberOfUser, const char* name);
void enterUserName(user *listUser, int numberOfUser, char* name);
void printTop20Score(user *listUser, int numberOfUser);
int countNumberOfUser(std::fstream &input);
std::string getTime(int time);
void sortScore(user *&listUser, int numberOfUser);
void formatName(char* name);
void saveUserList(user *&listUser, int &numberOfUser, user player);
void formatName(char* name);

#endif
