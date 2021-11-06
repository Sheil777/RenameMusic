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

    // Заполняем массив значениями false
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

    std::cout << "Данная программа добавляет в начале имени всех файлов в каталоге нумерацию, при этом файлы перемешиваются.\n\n";

    std::cout << "Укажите путь к каталогу с музыкой(только латиница)\n";
    std::cout << "Путь: ";
    std::cin >> pathS;

    pathS.insert(pathS.size(), "\\");

    bool flag = false;
    // Добавить \ после :
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

    // Попытка поставить : после буквы диска
    if(!flag) pathS.insert(1, ":");

    const char* path = pathS.c_str();

    char pathAll[sizeof(path) * 2 + 10];
    strcpy_s(pathAll, path);
    strcat_s(pathAll, "\\*");

    // Собираем имена файлов в массив
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
        std::cout << "Указан несуществующий путь к каталогу!\n";
        system("pause");
        exit(0);
    }

    system("cls");
    std::cout << "Найдены следующие файлы:\n";

    // Вывод имен файлов
    for (int i = 0; i < countFiles; i++)
        std::cout << files[i] << std::endl;

    char answer;

    std::cout << "\nВы действительно хотите пронумеровать их в случайном порядке? (y/n) ";
    std::cin >> answer;

    if (answer != 'y')
        exit(0);

    /* Переименовать */
    std::string str;
    char* fileName;
    char oldName[200];
    char newName[200];
    std::string tmp;

    int* arrRand = randZnach(countFiles);
    int sucRename = 0; // Успешные переименования
    int failRename = 0;// Неуспешные переименования


    // Переименовка
    for (int i = 0; i < countFiles; i++) {
        // Попробуй написать проще
        // Создание строки старого имени
        strcpy_s(oldName, path);
        str = files[i];
        fileName = &str[0];
        strcat_s(oldName, fileName);

        // Создание строки нового имени
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
    std::cout << "Успешно переименованных файлов: " << sucRename << "\n";
    std::cout << "Ошибок: " << failRename << "\n\n";

    //std::cout << "Чтобы закрыть программу, нажмите любую кнопку...\n";
    system("pause");

}