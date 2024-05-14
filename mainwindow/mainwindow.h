//
// Created by darina on 5/2/24.
//

#ifndef MAIN_VARIANT_MAINWINDOW_H
#define MAIN_VARIANT_MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QTimer>
#include "../SudokuField/PlayersField.h"

#include <stack>


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QWidget {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);

    ~mainwindow() override;

private:
    void ShowStartGrid();
    void SetColorButtons();
    void DisplayField();
    int current_difficulty = 0;
    bool author_field = false;
    PlayersField *playersfield;
    bool pencil = 0;
    int **notes;
    int **type_of_cell;
    int **answer;
    bool dark_theme = 0;
    QVector<QVector<QPushButton*>> field_buttons;
    QVector<QPushButton*> numbers_buttons;
    Ui::mainwindow *ui;
    QGridLayout *layout;
    QSignalMapper *fieldSignalMapper;
    QSignalMapper *numbersSignalMapper;
    int previous_cell = -1;
    int current_number = -1;
    int amount_of_mistakes;
    bool check_mistakes = false;
    int simple_hints_left = 3;
    int clever_hint_left = 1;
    bool fast_pencil = 1;
    bool request = 0;
    bool no_mistakes = true;
    std::vector<std::vector<std::pair<int, int> > > remember;
    QFont font32;
    QFont font11;
    QString GetBorder(int i, int j);
    void finish_game();
    QTimer *timer = new QTimer(this);
    int h, m, s;

public slots:
    void start_game_button_clicked();
    void change_difficulty_button_clicked(int type);
    void change_theme_button_clicked();
    void cell_button_clicked(int cell);
    void number_button_clicked(int number);
    void change_pencil_button_clicked();
    void back_button_clicked();
    void fast_pencil_button_clicked();
    void simple_hint_button_clicked();
    void to_main_window_clicked();
    void increase_time();
    void lose_game();
    void pause_button_clicked();
    void continue_button_clicked();
};


#endif //MAIN_VARIANT_MAINWINDOW_H
