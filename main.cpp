
#include <QApplication>
#include <QPushButton>

#include "mainwindow/mainwindow.h"

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

    mainwindow w;
    w.setWindowState(Qt::WindowFullScreen);
    w.show();

    return QApplication::exec();
}
