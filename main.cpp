#include <QApplication>
#include <QPushButton>

#include "SudokuField/SudokuField.h"
#include <iostream>

#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto f = new SudokuField();
    int** arr = new int * [9];
    arr[0] = new int [9] {5,3,4,0,0,8,0,1,0};
    arr[1] = new int [9] {0,0,0,0,0,2,0,9,0};
    arr[2] = new int [9] {0,0,0,0,0,7,6,0,4};
    arr[3] = new int [9] {0,0,0,5,0,0,1,0,0};
    arr[4] = new int [9] {1,0,0,0,0,0,0,0,3};
    arr[5] = new int [9] {0,0,9,0,0,1,0,0,0};
    arr[6] = new int [9] {3,0,5,4,0,0,0,0,0};
    arr[7] = new int [9] {0,8,0,2,0,0,0,0,0};
    arr[8] = new int [9] {0,6,0,7,0,0,3,8,2};
    std::cout << f->CalculateDifficulty(arr);
    f->DifficultLevelGenerate(500, 800);
    auto t = f->GetSudokuField();
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            std::cout << t[i][j];
        }
        std::cout << '\n';
    }
    std::cout << f->CalculateDifficulty(t) << " \n";
    t = f->GetSudokuFieldAnswer();
    std::cout << '\n';
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            std::cout << t[i][j];
        }
        std::cout << '\n';
    }

    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            for(int number = 1; number <= 9; number ++)
                f->TryFill(i + 1, j + 1, number);
        }
    }

    std::cout << '\n';
    t = f->GetSudokuField();

    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            std::cout << t[i][j];
        }
        std::cout << '\n';
    }

    qDebug() << f->GetHint();
    exit(0);
    return QApplication::exec();
}