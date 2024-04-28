
#include <QApplication>
#include <QPushButton>

#include "SudokuField/SudokuField.h"
#include "SudokuField/PlayersField.h"
#include <iostream>

#include <QDebug>
#include <cmath>

// поскольку интерфейс игры будет реализован в последнюю очередь,
// для доказательства работоспособности текущих созданных алгоритмов создана следующая программа в main:
// arr[][] - судоку, для которого быдет посчитана сложность. Подразумевает работу с судоку с единственно верным решением
// auto k = new PlayersField(1, 300, 2000); - поле игрока со сложностью 300 - 2000
// далее выведено поле, ответ на него, сделаны попытки вставить цифру в три клетки ручкой, затем аналогичное карандашом


//Функции взаимодействия
// для подсчета сложности - CalculateDifficulty(arr)
// PlayersField - класс, унаследованный от SudokuField. Будет реализовывать игру.
// На данный момент реализовывает нажатие цифрой на определенную клетку (зависит от того, пустая клетка или нет, активирован режим карандаша или нет
// Для генерации поля с определенным уровнем сложности - в конструктор PlayersField(1, мин_сложность, макс_сложность)
// Для генерации поля с доп подсказками - определенное положение ячеек относительно друг друга - PlayersField(0, *, *). Будет вызван другой алгоритм генерации
// получить поле и ответ - GetSudokuField(), GetSudokuFieldAnswer()
// для смены карандаша на ручку и наоборот - SetPencil()
// Для попытки добавить цифру в клетку - TryAdd(i, j, number). 0-индексация.
// вернет true, если:
//      установлена ручка и введенная цифра корректна
//      установлен карандаш и данная цифра уже есть в заметка - удаление из заметок
//      установлен карандаш и цифра не противоречит столбику, строке и клетке - добавление в заметки
//      узнать тип клетки и ее заметки - ShowCell(i, j). Будет выведен тип клетки и ее заметки (если клетка заполнена :тип - 1 в заметках цифра, которая записана)
// иначе вернет false, заметки изменены не будут

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int** arr = new int*[9];
    auto f = new SudokuField();
    arr[0] = new int [9] {9,0,0,0,0,2,0,0,5};
    arr[1] = new int [9] {0,5,1,0,0,7,4,0,0};
    arr[2] = new int [9] {0,4,7,6,0,0,0,8,1};
    arr[3] = new int [9] {0,0,0,0,0,6,0,0,0};
    arr[4] = new int [9] {0,0,6,0,2,0,8,0,0};
    arr[5] = new int [9] {7,0,0,0,8,0,0,1,3};
    arr[6] = new int [9] {4,0,0,7,0,9,5,0,8};
    arr[7] = new int [9] {1,0,0,0,0,5,0,0,0};
    arr[8] = new int [9] {6,0,0,0,0,0,1,9,2};
    std::cout << f->CalculateDifficulty(arr) << '\n';

    auto k = new PlayersField(1, 300, 2000);
    auto tt = k->GetSudokuField();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << tt[i][j];
        }
        std::cout << '\n';
    }
    tt = k->GetSudokuFieldAnswer();
    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            std::cout << tt[i][j];
        }
        std::cout << '\n';
    }

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 3; j++) {
            for (int value = 1; value <= 9; value++) {
                std::cout << i << " " << j << " " << value << '\n';
                bool t = k->TryAdd(i, j, value);
                std::cout << "try add to " << i + 1 << " " << j + 1 << " value " << value << " is " << t << '\n';
            }
            std::cout << "candidates for " << i + 1 << " " << j + 1 << " : ";
            k->ShowCell(i, j);
        }
    }

    k->SetPencil();

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 3; j++) {
            for (int value = 1; value <= 9; value++) {
                bool t = k->TryAdd(i, j, value);
                std::cout << "try add to " << i + 1 << " " << j + 1 << " value " << value << " is " << t << '\n';
            }
            std::cout << "candidates for " << i + 1 << " " << j + 1 << " : ";
            k->ShowCell(i, j);
        }
    }

    for (int i = 0; i < 9; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    exit(0);
    return QApplication::exec();
}
