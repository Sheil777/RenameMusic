//#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio> // for rename
#include <time.h>
#include <cstdlib> // exit(0)

int* randZnach(int countEl)
{
    // bool table[10] = { false };
    bool* table = new bool[countEl];
    int* a = new int[countEl];
    srand(time(0));

    // ��������� ������ ���������� false
    for (int i = 0; i < countEl; i++)
        table[i] = false;

    for (int i = 0;i < countEl;++i)
    {
        int n;
        while (table[n = rand() % countEl]);
        table[n] = true;
        a[i] = n;
    }

    return a;
}

int main() {
    setlocale(LC_ALL, "rus");

    WIN32_FIND_DATA FindFileData;
    HANDLE hf;

    std::string files[200];

    int countFiles = 0;
    //char path[] = "c:\\test\\";
    std::string pathS;

    std::cout << "\t\t******* Developed by Sheil777 *******\n\n";

    std::cout << "������ ��������� ��������� � ������ ����� ���� ������ � �������� ���������, ��� ���� ����� ��������������.\n\n";

    std::cout << "������� ���� � �������� � �������(������ ��������)\n";
    std::cout << "����: ";
    std::cin >> pathS;

    pathS.insert(pathS.size(), "\\");

    bool flag = false;
    // �������� \ ����� :
    for (int i = 0; i < pathS.length(); i++) {
        if (pathS[i] == ':') {
            if (pathS[i + 1] == '\\' || pathS[i + 1] == '/') {
                flag = true;
                break;
            }
            pathS.insert(i+1, "\\");

            flag = true;
            break;
        }
        
    }

    // ������� ��������� : ����� ����� �����
    if(!flag) pathS.insert(1, ":");

    const char* path = pathS.c_str();

    char pathAll[sizeof(path) * 2 + 10];
    strcpy_s(pathAll, path);
    strcat_s(pathAll, "\\*");

    // �������� ����� ������ � ������
    hf = FindFirstFile(pathAll, &FindFileData);
    if (hf != INVALID_HANDLE_VALUE) {
        do {
            // std::cout << FindFileData.cFileName << "\n";
            
            if (strcmp(FindFileData.cFileName, ".") == 0) continue;
            if (strcmp(FindFileData.cFileName, "..") == 0) continue;

            files[countFiles] = FindFileData.cFileName;
            countFiles++;
        } while (FindNextFile(hf, &FindFileData) != 0);
        FindClose(hf);
    }
    else
    {
        std::cout << "������ �������������� ���� � ��������!\n";
        system("pause");
        exit(0);
    }

    system("cls");
    std::cout << "������� ��������� �����:\n";

    // ����� ���� ������
    for (int i = 0; i < countFiles; i++)
        std::cout << files[i] << std::endl;

    char answer;

    std::cout << "\n�� ������������� ������ ������������� �� � ��������� �������? (y/n) ";
    std::cin >> answer;

    if (answer != 'y')
        exit(0);

    /* ������������� */
    std::string str;
    char* fileName;
    char oldName[200];
    char newName[200];
    std::string tmp;

    int* arrRand = randZnach(countFiles);
    int sucRename = 0; // �������� ��������������
    int failRename = 0;// ���������� ��������������


    // ������������
    for (int i = 0; i < countFiles; i++) {
        // �������� �������� �����
        // �������� ������ ������� �����
        strcpy_s(oldName, path);
        str = files[i];
        fileName = &str[0];
        strcat_s(oldName, fileName);

        // �������� ������ ������ �����
        strcpy_s(newName, path);
        str = files[i];
        tmp = ". ";
        tmp.insert(0, std::to_string(arrRand[i] + 1));

        str.insert(0, tmp);

        fileName = &str[0];
        strcat_s(newName, fileName);

        //std::cout << "newName " << newName << "\n";
        //system("pause");

        if (rename(oldName, newName) == 0)
            sucRename++;
        else
            failRename++;
    }
    
    system("cls");
    std::cout << "������� ��������������� ������: " << sucRename << "\n";
    std::cout << "������: " << failRename << "\n\n";

    //std::cout << "����� ������� ���������, ������� ����� ������...\n";
    system("pause");

}