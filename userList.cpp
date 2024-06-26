#include "headers/2048.h"

// dem so luong user trong file
int countNumberOfUser(std::fstream &input) 
{
    input.open(LIST_USER_FILE, ios::in);

    int begin = input.tellg();
    input.seekg(0, ios::end);
    int end = input.tellg();

    input.close();
    return (end - begin) / sizeof(user);
}

// load user tu file ve mang
void loadFileUserList(std::fstream &input, user *&listUser, int numberOfUser) 
{
    input.open(LIST_USER_FILE, ios::in | ios::binary);
    input.read((char *)listUser, sizeof(user) * numberOfUser);
    input.close();
}

// luu mang user len file
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

// ham kiem tra co ton tai user trong mang user chua
bool isExistUserName(user *listUser, int numberOfUser, const char *name) 
{
    for (int i = 0; i < numberOfUser; i++)
    {
        if (strcmp(name, listUser[i].userName) == 0)
            return true;
    }

    return false;
}

// chuan hoa lai ten nguoi dung nhap vao (nhap du dau cach o dau, cuoi, giua cac ki tu)
void normalize(char *name) 
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

    char *dest = name;
    for (char *src = name; *src; src++)
    {
        *dest = *src;
        if (*src != ' ' || (dest > name && *(dest - 1) != ' '))
            dest++;
    }
    *dest = '\0';
}

// kiem tra ten nhap vao co dung yeu cau chua
bool isValidName(const char *name) 
{
    int sizeName = strlen(name);

    if (sizeName < 6 || sizeName > 30) // do dai ten lon hon 6 va nho hon 30 ki tu
        return false;

    for (int i = 0; i < sizeName; i++)
        if (!(name[i] == '_' || isalpha(name[i]) || isdigit(name[i]) || name[i] == ' ')) // chi duoc chua dau "_", so va dau cach
            return false;

    return true;
}

// ham nhap ten
void enterUserName(user *listUser, int numberOfUser, char *name) 
{
    fstream loadResume;
    resume *resumeList = new resume[5];
    loadResumeFile(resumeList);

    std::cout << "Enter the name (Note: name from 6 to 30 characters including lowercase letters, uppercase letters, numbers, spaces and the character _ ): ";
    cout << BLUE;
    std::cin.getline(name, MAX_NAME_LENGTH);
    cout << RESET;
    normalize(name);

    // kiem tra tinh trung lap va ten da dung yeu cau hay chua (neu sai thi nhap lai)
    while (isExistUserName(listUser, numberOfUser, name) || !isValidName(name) || isExistResume(resumeList, name))
    {
        system("cls");
        std::cout << RED << "User name already exists or User name is not valid, please enter another user name!" << std::endl;
        std::cout << "Enter the name: " << RESET;
        cout << BLUE;
        std::cin.getline(name, MAX_NAME_LENGTH);
        cout << RESET;
        normalize(name);
    }
}

void printTop20Score(user *listUser, int numberOfUser)
{

    sortScore(listUser, numberOfUser);

    std::cout << YELLOW << "        TOP 20 USER WITH THE HIGHEST SCORE" << RESET << std::endl;
    std::cout << RED << std::setw(5) << std::left << "STT";
    std::cout << std::setw(30) << std::left << "Name";
    std::cout << std::setw(10) << std::left << "Score";
    std::cout << std::setw(10) << std::left << "Time" << RESET << std::endl;
    
    cout << BOLD;
    std::cout << std::setfill('-');
    std::cout << std::setw(54) << "-" << std::endl;
    std::cout << std::setfill(' ');
    cout << RESET;

    numberOfUser = (numberOfUser > 20) ? 20 : numberOfUser;

    for (int i = 0; i < numberOfUser; i++)
    {
        std::cout << std::setw(5) << i + 1;
        if (i < 3) // in mau khac doi voi top 3
            cout << "\033[0;34m";
        else 
            cout << "\033[0;36m";
        std::cout << std::setw(30) << std::left << listUser[i].userName << RESET;
        std::cout << std::setw(10) << std::left << listUser[i].score;
        std::cout << std::setw(10) << std::left << getTime(listUser[i].playingTime) << RESET << std::endl;
    }

    cout << std::right;
}

// dua thoi gian va dang hh::mm:ss
std::string getTime(int time) 
{
    std::string res;

    int hours = static_cast<int>(time / 3600);
    int minutes = static_cast<int>((time % 3600) / 60);
    int seconds = static_cast<int>(time % 60);

    res = (hours < 10 ? "0" + std::to_string(hours) : std::to_string(hours)) + ":" + (minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes)) + ":" + (seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds));

    return res;
}

// them moi player vao mang listUser
void saveUserList(user *&listUser, int &numberOfUser, user player) 
{
    std::fstream output;
    numberOfUser++;
    delete[] listUser;
    listUser = new user[numberOfUser];
    loadFileUserList(output, listUser, numberOfUser);
    listUser[numberOfUser - 1] = player;
    sortScore(listUser, numberOfUser);
}