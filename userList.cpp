#include "2048.h"

int countNumberOfUser(std::fstream &input)
{
    input.open(LIST_USER_FILE, std::ios::in);
    int numberOfUser = 0;
    std::string name = "";
    int score = 0;
    while (!input.eof())
    {
        input >> name;
        input >> score;
        numberOfUser++;
    }
    input.close();
    return numberOfUser;
}
void loadFileUserList(std::fstream &input, user *&listUser, int numberOfUser)
{
    input.open(LIST_USER_FILE, std::ios::in);
    numberOfUser = 0;
    while (!input.eof())
    {
        input >> listUser[numberOfUser].userName;
        input >> listUser[numberOfUser].score;
        numberOfUser++;
    }
    input.close();
}
void addUserInFile(std::fstream &output, user User)
{
    output.open(LIST_USER_FILE, std::ios::app);
    output << User.userName << std::endl
           << User.score << std::endl;
    output.close();
}

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
bool isExistUserName(user *listUser, int numberOfUser, std::string name)
{
    for (int i = 0; i < numberOfUser; i++)
        if (name == listUser[i].userName)
            return true;
    return false;
}
std::string enterUserName(user *listUser, int numberOfUser)
{
    std::string name;
    std::cout << "Enter the name: ";
    cin.ignore();
    getline(std::cin, name);
    while (isExistUserName(listUser, numberOfUser, name))
    {
        system("cls");
        std::cout << "User name exists, please enter another user name!" << std::endl;
        std::cout << "Enter the name: ";
        getline(std::cin, name);
    }
    return name;
}
void printTop10Score(user *listUser, int numberOfUser)
{
    sortScore(listUser, numberOfUser);
    std::cout << "TOP 10 USER WITH THE HIGHEST SCORE" << std::endl;
    for (int i = 0; i < numberOfUser - 1; i++)
        std::cout << i + 1 << ". " << listUser[i].userName << std::setw(5) << listUser[i].score << std::endl;
}