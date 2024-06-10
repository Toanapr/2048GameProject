#include "2048.h"

void loadResumeFile(resume *&resumeList)
{
    fstream input;
    string file = "RESUME_FILE";
    for (int i = 0; i < 5; i++)
    {
        input.open(file + to_string(i) + ".bin", ios::in | ios::binary);
        input.read((char *)&resumeList[i], sizeof(resume));
        input.close();
    }
}

void saveResume(resume *resumeList)
{
    fstream output;
    string file = "RESUME_FILE";
    for (int i = 0; i < 5; i++)
    {
        output.open(file + to_string(i) + ".bin", ios::out | ios::binary);
        output.write((char *)&resumeList[i], sizeof(resume));
        output.close();
    }
}

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
            // formatName(resumeList[i].player.userName);
            cout << resumeList[i].player.userName << endl;
        }
    }
    cout << "\n6. Exit\n";
}
bool isExistResume(resume *resumeList, char *name)
{
    for (int i = 0; i < 5; i++)
        if (strcmp(resumeList[i].player.userName, name) == 0)
            return true;
    return false;
}