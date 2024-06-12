#include "headers/2048.h"

// luu mang resumeList vao 5 fine bin
void loadResumeFile(resume *&resumeList)
{
    fstream input;
    string file = ".\\binary_files\\RESUME_FILE";
    for (int i = 0; i < 5; i++)
    {
        input.open(file + to_string(i) + ".bin", ios::in | ios::binary);
        input.read((char *)&resumeList[i], sizeof(resume));
        input.close();
    }
}

// lay du lieu xuong tu file
void saveResume(resume *resumeList)
{
    fstream output;
    string file = ".\\binary_files\\RESUME_FILE";
    for (int i = 0; i < 5; i++)
    {
        output.open(file + to_string(i) + ".bin", ios::out | ios::binary);
        output.write((char *)&resumeList[i], sizeof(resume));
        output.close();
    }
}

// ham nay tra ve vi tri nguoi choi co ten "name" hoac tra ve vi tri con trong trong resume
int getResumeEmpty(resume *resumeList, char *name)
{
    for (int i = 0; i < 5; i++)
        if (strcmp(resumeList[i].player.userName, name) == 0)
            return i;

    for (int i = 0; i < 5; i++)
        if (resumeList[i].size == 0)
            return i;
    return -1;
}

// ham cap nhat lai thong tin player trong resumeList
void changeResume(resume *&resumeList, int index, int **board, int size, user player)
{
    resumeList[index - 1].size = size;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            resumeList[index - 1].board[i][j] = board[i][j];
    resumeList[index - 1].player = player;
}

void printResume(resume *resumeList)
{
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". ";
        if (resumeList[i].size == 0)
            cout << "Empty" << endl;
        else
        {
            cout << resumeList[i].player.userName << endl;
        }
    }
    cout << "\n6. Exit\n";
}

// kiem tra player da xuat hien trong resumeList chua
bool isExistResume(resume *resumeList, char *name)
{
    for (int i = 0; i < 5; i++)
        if (strcmp(resumeList[i].player.userName, name) == 0)
            return true;
    return false;
}