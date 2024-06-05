#include "2048.h"

int countNumberOfUser(std::fstream &input)
{
    input.open(LIST_USER_FILE, ios::in);

    int begin = input.tellg();
    input.seekg(0, ios::end);
    int end = input.tellg();

    input.close();
    // cout << end << " " << begin << " " << sizeof(user);
    return (end - begin) / sizeof(user);
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
        {
            if (listUser[i].score < listUser[j].score)
                swap(listUser[i], listUser[j]);
            else if (listUser[i].score == listUser[j].score && listUser[i].playingTime > listUser[j].playingTime)
                swap(listUser[i], listUser[j]);
        }
}

void formatName(char* name)
{
    char* pos = strchr(name, '*');
    if (pos)
        *pos = '\0';
}

bool isExistUserName(user *listUser, int numberOfUser, const char* name)
{
    for (int i = 0; i < numberOfUser; i++)
    {
        formatName(listUser[i].userName);
        if (strcmp(name, listUser[i].userName) == 0)
            return true;
    }

    return false;
}

void normalize(char* name)
{
    int len = strlen(name);
    int start = 0, end = len - 1;

    while (start < len && name[start] == ' ')
        start++;
    while (end >= 0 && name[end] == ' ')
        end--;

    if (start > end)
    {
        name[0] = '\0';
        return;
    }

    memmove(name, name + start, end - start + 1);
    name[end - start + 1] = '\0';

    char* dest = name;
    for (char* src = name; *src; src++)
    {
        *dest = *src;
        if (*src != ' ' || (dest > name && *(dest - 1) != ' '))
            dest++;
    }
    *dest = '\0';
}

bool isValidName(const char* name)
{
    int sizeName = strlen(name);

    if (sizeName < 6 || sizeName > 30)
        return false;

    for (int i = 0; i < sizeName; i++)
        if (!(name[i] == '_' || isalpha(name[i]) || isdigit(name[i]) || name[i] == ' '))
            return false;

    return true;
}

void enterUserName(user *listUser, int numberOfUser, char* name)
{
    std::cout << "Enter the name (Note: name from 6 to 30 characters including lowercase letters, uppercase letters, numbers, spaces and the character _): ";
    std::cin.ignore();
    std::cin.getline(name, MAX_NAME_LENGTH);
    normalize(name);
    

    while (isExistUserName(listUser, numberOfUser, name) || !isValidName(name))
    {
        system("cls");
        std::cout << "User name already exists or User name is not valid, please enter another user name!" << std::endl;
        std::cout << "Enter the name: ";
        std::cin.getline(name, MAX_NAME_LENGTH);
        normalize(name);
    }

    while (strlen(name) < 30)
        strcat(name, "*");
}



void printTop20Score(user *listUser, int numberOfUser)
{
    
    // sortScore(listUser, numberOfUser);

    std::cout << "       TOP 20 USER WITH THE HIGHEST SCORE" << std::endl;
    std::cout << std::setw(5) << std::left << "STT";
    std::cout << std::setw(30) << std::left << "Name";
    std::cout << std::setw(10) << std::left << "Score";
    std::cout << std::setw(10) << std::left << "Time" << std::endl;

    std::cout << std::setfill('-');
    std::cout << std::setw(55) << "-" << std::endl;
    std::cout << std::setfill(' ');

    numberOfUser = (numberOfUser > 20) ? 20 : numberOfUser;
    
    for (int i = 0; i < numberOfUser; i++)
    {
        formatName(listUser[i].userName);
        std::cout << std::setw(5) << i + 1
                  << std::setw(30) << std::left << listUser[i].userName
                  << std::setw(10) << std::left << listUser[i].score
                  << std::setw(10) << std::left << getPlayingTime(listUser[i].playingTime) << std::endl;
    }

    cout << std::right;
}

char* getPlayingTime(int time)
{
    char* res;
    
    int hours = static_cast<int>(time / 3600);
    int minutes = static_cast<int>((time % 3600) / 60);
    int seconds = static_cast<int>(time % 60);

    sprintf(res, "%02d:%02d:%02d", hours, minutes, seconds);
    return res;
}

void saveUserList(user *&listUser, int &numberOfUser, user player)
{
    std::fstream output;
    numberOfUser++;
    delete[] listUser;
    listUser = new user[numberOfUser];
    loadFileUserList(output, listUser, numberOfUser);
    listUser[numberOfUser - 1] = player;
    sortScore(listUser, numberOfUser);
    // addUserInFile(output, listUser, (numberOfUser > 20) ? 20 : numberOfUser);
}