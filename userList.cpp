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

void normalize(std::string &name)
{
    while (name[0] == ' ')
        name.erase(0, 1);

    while (name[name.size() - 1] == ' ')
        name.erase(name.size() - 1, 1);

    for (int i = 0; i < name.size(); i++)
        if (name[i] == ' ')
        {
            while (name[i + 1] == ' ')
            {
                name.erase(i + 1, 1);
                i--;
            }
        }
}

bool isValidName(std::string name)
{
    for (int i = 0; i < name.size(); i++)
        if (!(name[i] == '_' || isalpha(name[i]) != 0 || isdigit(name[i]) != 0))
            return false;

    return true;
}

std::string enterUserName(user *listUser, int numberOfUser)
{
    std::string name;
    std::cout << "Enter the name (Note: name from 6 to 30 characters including lowercase letters, uppercase letters, numbers, spaces and the character "
                 "_"
                 "): ";
    std::cin.ignore();

    getline(std::cin, name);
    normalize(name);

    while (isExistUserName(listUser, numberOfUser, name) || !isValidName(name))
    {
        system("cls");
        std::cout << "User name already exists or User name is not valid , please enter another user name!" << std::endl;
        std::cout << "Enter the name: ";
        getline(std::cin, name);
        normalize(name);
    }

    return name;
}
void printTop20Score(user *listUser, int numberOfUser)
{
    sortScore(listUser, numberOfUser);

    std::cout << "TOP 20 USER WITH THE HIGHEST SCORE" << std::endl;
    std::cout << setw(5) << left << "STT";
    std::cout << setw(30) << left << "Name";
    std::cout << setw(10) << left << "Score" << endl;
    std::cout << setw(10) << left << "Time" << endl;

    std::cout << setfill('-');
    std::cout << setw(55) << "-" << endl;
    std::cout << setfill(' ');

    for (int i = 0; i < numberOfUser - 1; i++)
        std::cout << std::setw(5) << i + 1
                  << std::setw(30) << left << listUser[i].userName
                  << std::setw(10) << left << listUser[i].score
                  << std::setw(10) << left << getPlayingTime(listUser[i].playingTime) << std::endl;
}

std::string getPlayingTime(int time)
{
    std::string res = "";

    int hours = static_cast<int>(time / 3600);
    int minutes = static_cast<int>((time % 3600) / 60);
    int seconds = static_cast<int>(time % 60);

    return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
}