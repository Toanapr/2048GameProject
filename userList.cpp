#include "userList.h"

void swap(user &a, user &b)
{
    user temp = a;
    a = b;
    b = temp;
}
void sortScore(user *&listUser, int numberOfUser)
{
    for (int i = 0; i < numberOfUser; i++)
        for (int j = i + 1; j < numberOfUser; j++)
            if (listUser[i].score < listUser[j].score)
                swap(listUser[i], listUser[j]);
}
bool isExistUserName(user *listUser, int numberOfUser, string name)
{
    for (int i = 0; i < numberOfUser; i++)
        if (name == listUser[i].userName)
            return true;
    return false;
}
string enterUserName(user *listUser, int numberOfUser)
{
    string name;
    cout << "enter the name: ";
    getline(cin, name);
    while (isExistUserName(listUser, numberOfUser, name))
    {
        cout << "User name exists, please enter another user name!" << endl;
        getline(cin, name);
    }
    return name;
}
void printTop10Score(user *listUser, int numberOfUser)
{
    cout << "TOP 10 USER WITH THE HIGHEST SCORE" << endl;
    for (int i = 0; i < numberOfUser; i++)
        cout << i + 1 << ". " << listUser[i].userName << setw(5) << listUser[i].score << endl;
}