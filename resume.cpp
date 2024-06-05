#include "2048.h"

void loadResumeFile(resume *&r)
{
    fstream input;
    string file = "RESUME_FILE";
    for (int i = 0; i < 5; i++)
    {
        input.open(file + to_string(i) + ".bin", ios::in | ios::binary);
        input.read((char *)&r[i], sizeof(resume));
        input.close();
    }
}

void saveResume(resume *r)
{
    fstream output;
    string file = "RESUME_FILE";
    for (int i = 0; i < 5; i++)
    {
        output.open(file + to_string(i) + ".bin", ios::out | ios::binary);
        output.write((char *)&r[i], sizeof(resume));
        output.close();
    }
}

int getResumeEmpty(resume *r, char *name)
{
    for (int i = 0; i < 5; i++)
        if (strcmp(r[i].player.userName, name) == 0)
            return i;

    for (int i = 0; i < 5; i++)
        if (r[i].size == 0)
            return i;
    return -1;
}

void changeResume(resume *&r, int index, int **board, int size, user player, Stack undo, Stack redo, bool isOpenUndo)
{
    r[index - 1].size = size;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            r[index - 1].board[i][j] = board[i][j];
    r[index - 1].player = player;
    r[index - 1].isOpenUndo = isOpenUndo;
    // r[index - 1].undo = undo;
    // r[index - 1].redo = redo;
}

void printResume(resume *r)
{
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". ";
        if (r[i].size == 0)
            cout << "Empty" << endl;
        else
        {
            formatName(r[i].player.userName);
            cout << r[i].player.userName << endl;
        }
    }
}