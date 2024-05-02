#ifndef _USERLIST_H_
#define _USERLIST_H_

#include "2048.h"

#define listUserFile "user_list.txt"

struct user
{
    string userName;
    int score;
    user(string _userName, int _score)
    {
        userName = _userName;
        score = _score;
    }
    user()
    {
        userName = "";
        score = 0;
    }
};

#endif