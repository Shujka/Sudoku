#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

mainwindow::mainwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::mainwindow) {

    ui->setupUi(this);
    ui->mainMenuWidget->setStyleSheet(".QWidget {background-image: url(../Pictures/main_menu.png)}");
    ui->gameWidget->setStyleSheet(".QWidget {background-image: url(../Pictures/background.png)}");
    ui->gameWidget->hide();
    ui->endGameWidget->hide();
    ui->loseGameWidget->hide();
    ui->pauseGameWidget->hide();
    ui->themeButton->setIcon(QIcon("../Pictures/moon.png"));
    ui->themeButton->setStyleSheet("background-color:rgba(255, 255, 255, 0);  border: none;");
    ui->backMoveButton->setEnabled(0);

    font32.setPointSize(32);
    font11.setPointSize(11);

    field_buttons.resize(9);
    numbers_buttons.resize(9);

    fieldSignalMapper = new QSignalMapper(this);
    numbersSignalMapper = new QSignalMapper(this);

    timer->setInterval(1000);

    type_of_cell = new int *[9];
    for (int i = 0; i < 9; i++) {
        type_of_cell[i] = new int[9];
        field_buttons[i].resize(9);
        for (int j = 0; j < 9; j++) {
            type_of_cell[i][j] = 0;
            QPushButton *b = new QPushButton(this->ui->gameWidget);
            b->resize(70, 70);
            b->move(645 + 70 * j, 200 + 70 * i);
           // std::cout << i << " " << j << " " << 645 + 70 * i << " " << 300 + 70 * j << '\n';
            field_buttons[i][j] = b;
            QString style = "background-color:rgba(255, 255, 255, 0); border-style: solid; border-width: " + GetBorder(i, j) + " border-color: black;";
            qDebug() << i << " " << j << " " << style;
            //style = "background-color:rgba(255, 255, 255, 0); border-style: solid; border-width: 2px 2px 2px 2px; border-color: black;";
            field_buttons[i][j]->setStyleSheet(style);
            b->show();
            connect(field_buttons[i][j], SIGNAL(clicked()), fieldSignalMapper, SLOT(map()));
            fieldSignalMapper->setMapping(field_buttons[i][j], i * 10 + j);
        }
    }

    numbers_buttons.resize(9);
    for(int i = 0; i < 9; i++) {
        QPushButton *b = new QPushButton(this->ui->gameWidget);
        b->resize(50, 50);
        b->move(650 + 70 * i, 880);
        numbers_buttons[i] = b;
        numbers_buttons[i]->setText(QString::number(i + 1));
        numbers_buttons[i]->setFont(font32);
        numbers_buttons[i]->setStyleSheet("background-color:rgba(255, 255, 255, 50};");
        b->show();
        connect(numbers_buttons[i], SIGNAL(clicked()), numbersSignalMapper, SLOT(map()));
        numbersSignalMapper->setMapping(numbers_buttons[i], i);
    }


    connect(numbersSignalMapper, SIGNAL(mappedInt(int)), this, SLOT(number_button_clicked(int)));
    connect(fieldSignalMapper, SIGNAL(mapped(int)), this, SLOT(cell_button_clicked(int)));
    connect(ui->exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->newGameButton, SIGNAL(clicked(bool)), this, SLOT(start_game_button_clicked()));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(change_difficulty_button_clicked(int)));
    connect(ui->themeButton, SIGNAL(clicked(bool)), this, SLOT(change_theme_button_clicked()));
    connect(ui->changePencilButton, SIGNAL(clicked()), this, SLOT(change_pencil_button_clicked()));
    connect(ui->backMoveButton, SIGNAL(clicked()), this, SLOT(back_button_clicked()));
    connect(ui->fastPencilButton, SIGNAL(clicked()), this, SLOT(fast_pencil_button_clicked()));
    connect(ui->hintButton, SIGNAL(clicked()), this, SLOT(simple_hint_button_clicked()));
    connect(ui->newGameButton_2, SIGNAL(clicked()), this, SLOT(start_game_button_clicked()));
    connect(ui->newGameButton_1, SIGNAL(clicked()), this, SLOT(start_game_button_clicked()));
    connect(ui->exitButton_2, SIGNAL(clicked()), this, SLOT(close()));
    connect(timer, SIGNAL(timeout()), this, SLOT(increase_time()));
    connect(ui->exitButton_1, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->toMainMenuButton, SIGNAL(clicked()), this, SLOT(to_main_window_clicked()));
    connect(ui->toMainMenuButton_1, SIGNAL(clicked()), this, SLOT(to_main_window_clicked()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause_button_clicked()));
    connect(ui->continueButton, SIGNAL(clicked()), this, SLOT(continue_button_clicked()));
    connect(ui->newGameButton_6, SIGNAL(clicked()), this, SLOT(start_game_button_clicked()));
    connect(ui->toMainMenuButton_6, SIGNAL(clicked()), this, SLOT(to_main_window_clicked()));
    connect(ui->exitButton_6, SIGNAL(clicked()), this, SLOT(close()));

}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::start_game_button_clicked() {
    ui->timer_label->setText("00:00");
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            type_of_cell[i][j] = 0;
        }
    }
    if (author_field) {
        ui->newGameButton_1->setEnabled(false);
        ui->newGameButton_2->setEnabled(false);

    } else {
        ui->newGameButton_1->setEnabled(true);
        ui->newGameButton_2->setEnabled(true);
        ui->endGameWidget->hide();
        ui->loseGameWidget->hide();
        ui->pauseGameWidget->hide();
        ui->gameWidget->setEnabled(true);
        ui->fastPencilButton->setEnabled(true);
        clever_hint_left = 1;
        ui->cleverHintButton->setEnabled(true);
        remember.clear();
        ui->backMoveButton->setEnabled(false);
        ui->hintButton->setEnabled(true);
        simple_hints_left = 3;
        check_mistakes = ui->checkBox->isChecked();
        no_mistakes = true;
        /*for(int i = 0; i < 9; i ++)
        {
            for(int j = 0; j < 9; j ++)
            {
                field_buttons[i][j]->setText("");
            }
        }*/
        switch (current_difficulty) {
            case 0: {
                // simple generate
                playersfield = new PlayersField(0, 0, 0);
                break;
            }
            case 1: {
                // easy difficult
                playersfield = new PlayersField(1, 40, 150);
                break;
            }
            case 2: {
                // medium difficult
                playersfield = new PlayersField(1, 151, 650);
                break;
            }
            case 3: {
                // hard difficult
                playersfield = new PlayersField(1, 651, 1001);
                break;
            }
            case 4: {
                // very hard difficult
                playersfield = new PlayersField(1, 1001, 5000);
                break;
            }
        }
        notes = playersfield->GetNotes();
        answer = playersfield->GetSudokuFieldAnswer();
        ui->mainMenuWidget->hide();
        ShowStartGrid();
        ui->gameWidget->show();
    }
}

void mainwindow::change_difficulty_button_clicked(int type) {
    current_difficulty = type;
}

void mainwindow::change_theme_button_clicked() {
    dark_theme ^= 1;

    if (dark_theme) {
        ui->themeButton->setIcon(QIcon("../Pictures/sun.png"));
    } else {
        ui->themeButton->setIcon(QIcon("../Pictures/moon.png"));

    }
}


// 0 nothing special
// 1 blue clicked
// 2 red number
// 3 violet
void mainwindow::cell_button_clicked(int cell) {
    if (no_mistakes == 0) {
     //   std::cout << "no_mistakes = 0. I return\n";
        return;
    }
    if (previous_cell != -1) {
        int x = previous_cell / 10, y = previous_cell % 10;
        for (int i = 0; i < 9; i++) {
            if (type_of_cell[i][y] % 2 == 1) {
                type_of_cell[i][y] -= 1;
            }
            if (type_of_cell[x][i] % 2 == 1) {
                type_of_cell[x][i] -= 1;
            }
        }

        int start_cell_x = x / 3, start_cell_y = y / 3;
        for (int i = start_cell_x * 3; i < (start_cell_x + 1) * 3; i++) {
            for (int j = start_cell_y * 3; j < (start_cell_y + 1) * 3; j++) {
                if (type_of_cell[i][j] % 2 == 1) {
                    type_of_cell[i][j] -= 1;
                }
            }
        }
    }
    previous_cell = cell;
    int x = cell / 10, y = cell % 10;
    for (int i = 0; i < 9; i++) {
        if (type_of_cell[i][y] % 2 == 0) {
            type_of_cell[i][y]++;
        }
        if (type_of_cell[x][i] % 2 == 0) {
            type_of_cell[x][i]++;
        }
    }
    int start_cell_x = x / 3, start_cell_y = y / 3;
    for (int i = start_cell_x * 3; i < (start_cell_x + 1) * 3; i++) {
        for (int j = start_cell_y * 3; j < (start_cell_y + 1) * 3; j++) {
            if (type_of_cell[i][j] % 2 == 0) {
                type_of_cell[i][j]++;
            }
        }
    }

    if (current_number == -1) {
        if (notes[cell / 10][cell % 10] & 1) {
            current_number = answer[cell / 10][cell % 10];
            request = true;
            number_button_clicked(answer[cell / 10][cell % 10] - 1);
            request = false;
        }
    } else {
        std::vector <std::pair<int, int>> add_remember;
        for (int i = 0; i < 9; i ++) {
            for (int j = 0; j < 9; j ++) {
                add_remember.push_back({i * 10 + j, notes[i][j]});
            }
        }
        int t = playersfield->TryAdd(cell / 10, cell % 10, current_number);
        notes = playersfield->GetNotes();
        if (t == 0) {
            request = true;
            //ui->backMoveButton->setEnabled(true);
            number_button_clicked(answer[cell / 10][cell % 10] - 1);
            current_number = answer[cell / 10][cell % 10];
            std::cout << "left " << playersfield->GetEmptyCellsNumber() << '\n';
            if (playersfield->GetEmptyCellsNumber() == 0)
                finish_game();
            request = false;
        }
        if (t == 1) {
            request = true;
            bool is_changed = false;
            for (auto x: add_remember) {
                if (notes[x.first / 10][x.first % 10] != x.second)
                    is_changed = true;
            }
            if (is_changed) {
                remember.push_back(add_remember);
                ui->backMoveButton->setEnabled(true);
            }
            number_button_clicked(current_number - 1);
            std::cout << "left " << playersfield->GetEmptyCellsNumber() << std::endl;
            if (playersfield->GetEmptyCellsNumber() == 0)
                finish_game();
            request = false;
            // all is good
        }
        if (t == 2) {
            // same number in rcc
            // nothing happened
            request = false;
        }
        if (t == 3) {
            // work like mistake
            SetColorButtons();
            DisplayField();
            QString style = "text-align: center; background-color:rgba(255, 255, 0, 100); border-style: solid; border-width: " +
                            GetBorder(cell / 10, cell % 10) + " border-color: black; color: red;";
            field_buttons[cell / 10][cell % 10]->setStyleSheet(style);
            field_buttons[cell / 10][cell % 10]->setFont(font32);
            field_buttons[cell / 10][cell % 10]->setText(QString::number(current_number));
            no_mistakes = false;
            request = false;
            ui->backMoveButton->setEnabled(true);
            ui->hintButton->setEnabled(false);
            ui->cleverHintButton->setEnabled(false);
            ui->fastPencilButton->setEnabled(false);
            amount_of_mistakes ++;
            if(amount_of_mistakes == 3 && check_mistakes)
            {
                lose_game();
            }
            return;
        }
    }
    request = false;
    SetColorButtons();
    DisplayField();
}

void mainwindow::ShowStartGrid() {
    auto q = playersfield->GetSudokuField();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (q[i][j] == 0) {
                field_buttons[i][j]->setText("");
                continue;
            }
            field_buttons[i][j]->setText(QString::number(q[i][j]));
            field_buttons[i][j]->setFont(font32);
        }
    }
    h = 0, m = 0, s = 0;
    amount_of_mistakes = 0;
    SetColorButtons();
    DisplayField();
    timer->start();
}

void mainwindow::number_button_clicked(int number) {
    // to commit
    if (no_mistakes == 0)
        return;
    int value = number + 1;
    if (value == 0) {
        current_number = -1;
        previous_cell = -1;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                type_of_cell[i][j] = 0;
            }
        }
        SetColorButtons();
        DisplayField();
        return;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((notes[i][j] >> value) & 1) {
                if (type_of_cell[i][j] < 2) {
                    type_of_cell[i][j] += 2;
                }
            } else {
                if (type_of_cell[i][j] > 1) {
                    type_of_cell[i][j] -= 2;
                }
            }
        }
    }
    current_number = value;
    if (previous_cell != -1 && request == 0) {
        if ((notes[previous_cell / 10][previous_cell % 10] & 1) == 0) {
            cell_button_clicked(previous_cell);
        }
    }
    request = false;
    if (no_mistakes) {
        SetColorButtons();
        DisplayField();
    }
}

void mainwindow::SetColorButtons() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int k = type_of_cell[i][j];
            QString align;
            if (notes[i][j] & 1) {
                align = "text-align: center;";
            } else {
                align = "text-align: left;";
            }
            switch (k) {
                case 0: {
                    QString style = align + " background-color:rgba(255, 255, 255, 0); border-style: solid; border-width: " +
                                    GetBorder(i, j) + " border-color: black;";
                    field_buttons[i][j]->setStyleSheet(style);
                    break;
                }
                case 1: {
                    QString style = align + " background-color:rgba(0, 0, 255, 50); border-style: solid; border-width: " +
                                    GetBorder(i, j) + " border-color: black;";
                    field_buttons[i][j]->setStyleSheet(style);
                    break;
                }
                case 2: {
                    QString style = align + " background-color:rgba(255, 0, 0, 50); border-style: solid; border-width: " +
                                    GetBorder(i, j) + " border-color: black;";
                    field_buttons[i][j]->setStyleSheet(style);
                    break;
                }
                case 3: {
                    QString style = align + " background-color:rgba(255, 0, 255, 50); border-style: solid; border-width: " +
                                    GetBorder(i, j) + " border-color: black;";
                    field_buttons[i][j]->setStyleSheet(style);
                    break;
                }
                case 4:{
                    QString style = align + " background-color:rgba(250, 0, 250, 25); border-style: solid; border-width: " +
                                    GetBorder(i, j) + " border-color: black;";
                    field_buttons[i][j]->setStyleSheet(style);
                    break;
                }
            }
        }
    }
    if (previous_cell != -1) {
        QString align;
        if (notes[previous_cell / 10][previous_cell % 10] & 1) {
            align = "text-align: center;";
        } else {
            align = "text-align: left;";
        }
        QString style = align + " background-color:rgba(0, 0, 255, 100); border-style: solid; border-width: " +
                        GetBorder(previous_cell / 10, previous_cell % 10) + " border-color: black;";
        field_buttons[previous_cell / 10][previous_cell % 10]->setStyleSheet(style);

    }
 }

void mainwindow::DisplayField() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (notes[i][j] & 1) {
                // not empty
                {
                    field_buttons[i][j]->setFont(font32);
                    field_buttons[i][j]->setText(QString::number(answer[i][j]));
                }
            } else {
                if (notes[i][j] == 0) {
                    field_buttons[i][j]->setText("");
                } else {
                    field_buttons[i][j]->setFont(font11);
                    QString s = "\n ";
                    for (int value = 1; value <= 9; value++) {
                        if ((notes[i][j] >> value) & 1) {
                            s += QString::number(value);
                        } else {
                            s += "  ";
                        }
                        if (value % 3 == 0)
                            s += "\n" ;
                        else
                            s += " ";
                    }
                    field_buttons[i][j]->setText(s);
                }
            }
        }
    }
}

QString mainwindow::GetBorder(int i, int j) {
    QString s;
    if (i == 0) {
        s += "6";
    } else {
        if (i == 3 || i == 6)
            s += "3";
        else
            s += "2";
    }
    s += "px ";
    if (j == 8) {
        s += "6";
    } else {
        if (j == 2 || j == 5)
            s += "3";
        else
            s += "2";
    }
    s += "px ";
    if (i == 8) {
        s += "6";
    } else {
        if (i == 2 || i == 5)
            s += "3";
        else
            s += "2";
    }
    s += "px ";
    if (j == 0) {
        s += "6";
    } else {
        if (j == 3 || j == 6)
            s += "3";
        else
            s += "2";
    }
    s += "px;";
    return s;
}

void mainwindow::change_pencil_button_clicked() {
    playersfield->SetPencil();
    if(pencil == 0)
        ui->changePencilButton->setText("карандаш");
    else
        ui->changePencilButton->setText("ручка");
    pencil ^= 1;
}

void mainwindow::back_button_clicked() {
    if (no_mistakes) {
        // all correct
        if (remember.empty()){
            ui->backMoveButton->setEnabled(0);
            return;
        }
        auto previous = remember.back();
        for (auto x: previous) {
            notes[x.first / 10][x.first % 10] = x.second;
            playersfield->SetCell(x.first / 10, x.first % 10, notes[x.first / 10][x.first % 10]);
        }
        playersfield->show_field();
        for (auto x: previous) {
            notes[x.first / 10][x.first % 10] = x.second;
            playersfield->SetNotes(x.first / 10, x.first % 10);
        }
        remember.pop_back();
        number_button_clicked(-1);

    } else {
        // one mistake
        no_mistakes = true;
        if(fast_pencil)
            ui->fastPencilButton->setEnabled(true);
        if(simple_hints_left > 0)
            ui->hintButton->setEnabled(true);
        if(clever_hint_left > 0)
            ui->cleverHintButton->setEnabled(true);
        SetColorButtons();
        DisplayField();
    }
    if (remember.empty())
        ui->backMoveButton->setEnabled(false);
}

void mainwindow::fast_pencil_button_clicked() {

    std::vector<std::pair<int, int> > add_remember;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (notes[i][j] & 1)
                continue;
            add_remember.push_back({i * 10 + j, notes[i][j]});
        }
    }
    remember.push_back(add_remember);
    ui->backMoveButton->setEnabled(true);
    playersfield->GetFastNotes();
    number_button_clicked(-1);
    fast_pencil = false;
    ui->fastPencilButton->setEnabled(false);
}

void mainwindow::simple_hint_button_clicked() {
    int position = playersfield->GetSimpleHint();
    cell_button_clicked(position);
    SetColorButtons();
    DisplayField();
    simple_hints_left--;
    if (!simple_hints_left) {
        ui->hintButton->setEnabled(false);
    }
}


void mainwindow::increase_time() {
    s ++;
    if(s == 60)
        m ++, s = 0;
    if(m == 60)
        h ++, m = 0;
    QString time;
    if (h > 0) {
        if (h < 10)
            time += "0" + QString::number(h) + ":";
        else
            time += QString::number(h) + ":";;
    }
    if (m < 10)
        time += "0" + QString::number(m) + ":";
    else
        time += QString::number(m) + ":";
    if (s < 10)
        time += "0" + QString::number(s);
    else
        time += QString::number(s);
    ui->timer_label->setText(time);
}

void mainwindow::finish_game() {
    timer->stop();
    ui->endGameWidget->show();
    ui->gameWidget->setEnabled(0);
    current_number = -1;
    previous_cell = -1;
    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j ++) {
            type_of_cell[i][j] = 0;
        }
    }
    ui->mistakes_label->setText(QString::number(amount_of_mistakes)); // ENTER MISTAKES
    ui->time_label->setText(ui->timer_label->text()); // ENTER TIME
    delete playersfield;
}

void mainwindow::to_main_window_clicked() {
    ui->gameWidget->hide();
    ui->endGameWidget->hide();
    ui->loseGameWidget->hide();
    ui->pauseGameWidget->hide();
    ui->mainMenuWidget->show();
    current_number = -1;
    previous_cell = -1;
    amount_of_mistakes = 0;
    no_mistakes = true;
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            type_of_cell[i][j] = 0;
            field_buttons[i][j]->setText("");
        }
    }
    SetColorButtons();
    DisplayField();
}

void mainwindow::lose_game() {
    timer->stop();
    ui->loseGameWidget->show();
    ui->gameWidget->setEnabled(0);
    current_number = -1;
    previous_cell = -1;
    ui->mistakes_label_1->setText(QString::number(amount_of_mistakes)); // ENTER MISTAKES
    ui->time_label_1->setText(ui->timer_label->text()); // ENTER TIME

}

void mainwindow::pause_button_clicked() {
    timer->stop();
    ui->pauseGameWidget->show();
    ui->gameWidget->setEnabled(0);
    current_number = -1;
    previous_cell = -1;
    ui->mistakes_label_6->setText(QString::number(amount_of_mistakes)); // ENTER MISTAKES
    ui->time_label_6->setText(ui->timer_label->text()); // ENTER TIME
}

void mainwindow::continue_button_clicked() {
    ui->pauseGameWidget->hide();
    ui->gameWidget->setEnabled(1);
    timer->start();
}

// text-align: left;