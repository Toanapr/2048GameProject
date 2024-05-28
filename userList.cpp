#include "2048.h"

int countNumberOfUser(std::fstream &input)
{
    int count = 0;
    user User;
    input.open(LIST_USER_FILE, ios::in | ios::binary);

    while (input.read(reinterpret_cast<char*>(&User), sizeof(user))) {
        count++;
    }

    input.close();
    return count;
}

void loadFileUserList(std::fstream &input, user *&listUser, int numberOfUser)
{
    input.open(LIST_USER_FILE, ios::in | ios::binary);
    input.read((char *)listUser, sizeof(user) * numberOfUser);
    input.close();
}

void addUserInFile(std::fstream &output, user *listUser, int numberOfUser)
{
    output.open(LIST_USER_FILE, ios::out | ios::binary);
    output.write((char *)listUser, sizeof(user) * numberOfUser);
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
    int sizeName = name.size();

    if (sizeName < 6)
        return false;

    if (sizeName > 30)
        return false;

    for (int i = 0; i < name.size(); i++)
        if (!(name[i] == '_' || isalpha(name[i]) != 0 || isdigit(name[i]) != 0 || name[i] == ' '))
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

    while (name.size() < 30)
        name = name + '*';

    return name;
}

string formatName(string name)
{
    int index = name.find('*');

    return name.substr(0, index);
}

void printTop20Score(user *listUser, int numberOfUser)
{
    sortScore(listUser, numberOfUser);

    std::cout << "       TOP 20 USER WITH THE HIGHEST SCORE" << std::endl;
    std::cout << std::setw(5) << std::left << "STT";
    std::cout << std::setw(30) << std::left << "Name";
    std::cout << std::setw(10) << std::left << "Score";
    std::cout << std::setw(10) << std::left << "Time" << std::endl;

    std::cout << std::setfill('-');
    std::cout << std::setw(50) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (int i = 0; i < 20; i++)
        std::cout << std::setw(5) << i + 1
                  << std::setw(30) << std::left << formatName(listUser[i].userName)
                  << std::setw(10) << std::left << listUser[i].score
                  << std::setw(10) << std::left << getPlayingTime(listUser[i].playingTime) << std::endl;
}

std::string getPlayingTime(int time)
{
    std::string res = "";

    int hours = static_cast<int>(time / 3600);
    int minutes = static_cast<int>((time % 3600) / 60);
    int seconds = static_cast<int>(time % 60);

    return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
}