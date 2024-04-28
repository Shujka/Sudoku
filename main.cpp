
#include <QApplication>
#include <QPushButton>

#include "SudokuField/SudokuField.h"
#include <iostream>

#include <QDebug>
#include <cmath>

// f->DifficultLevelGenerate(min, max) // to generate field
// f->GetSudokuFieldAnswer() // get answer
// f->GetSudokuField() // get field
// f->CalculateDifficulty(arr) // calculate difficulty of valid field arr

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto f = new SudokuField();
    int** arr = new int*[9];

    arr[0] = new int [9] {9,0,0,0,0,2,0,0,5};
    arr[1] = new int [9] {0,5,1,0,0,7,4,0,0};
    arr[2] = new int [9] {0,4,7,6,0,0,0,8,1};
    arr[3] = new int [9] {0,0,0,0,0,6,0,0,0};
    arr[4] = new int [9] {0,0,6,0,2,0,8,0,0};
    arr[5] = new int [9] {7,0,0,0,8,0,0,1,3};
    arr[6] = new int [9] {4,0,0,7,0,9,5,0,8};
    arr[7] = new int [9] {1,0,0,0,0,5,0,0,0};
    arr[8] = new int [9] {6,0,0,0,0,0,1,9,2};
    //std::cout << f->CalculateDifficulty(arr) << '\n';

    f->DifficultLevelGenerate(350, 2000);
    auto t = f->GetSudokuFieldAnswer();
    std::cout << "answer\n";
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            std::cout << t[i][j];
        }
        std::cout << '\n';
    }

    t = f->GetSudokuField();
    std::cout << f->CalculateDifficulty(t) << " \n";

    for(int i = 0; i < 9; i ++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    exit(0);
    return QApplication::exec();
}
