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
#include <QFile>
#include <QTextStream>
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
    bool author_field = false;
    bool check_mistakes = false;
    bool fast_pencil = 1;
    bool request = 0;
    bool no_mistakes = true;
    bool pencil = 0;

    int current_difficulty = 0;
    int previous_cell = -1;
    int current_number = -1;
    int amount_of_mistakes;
    int simple_hints_left = 3;
    int clever_hint_left = 1;
    int h, m, s;
    int current_page = 0;

    QVector<QVector<QPushButton*>> field_buttons;
    QVector<QPushButton*> numbers_buttons;
    std::vector <std::vector<std::pair < int, int>> > remember;

    static QString GetBorder(int i, int j);

    void finish_game();

    void ShowStartGrid();

    void SetColorButtons();

    void DisplayField();

    void DisplayRules();

    void ChangeBulbBackground();

    PlayersField *playersfield;
    int **notes;
    int **type_of_cell;
    int **answer;
    Ui::mainwindow *ui;
    QGridLayout *layout;
    QSignalMapper *fieldSignalMapper;
    QSignalMapper *numbersSignalMapper;
    QFont font32;
    QFont font11;
    QTimer *timer = new QTimer(this);

private slots:
    void start_game_button_clicked();

    void change_difficulty_button_clicked(int type);

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

    void show_rules_clicked();

    void increase_page_number();

    void decrease_page_number();

    void close_rules_button_clicked();

    void clever_hint_button_clicked();

    void close_hint_button_clicked();

    void start_create_button_clicked();
};


#endif //MAIN_VARIANT_MAINWINDOW_H
