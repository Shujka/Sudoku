//
// Created by darina on 4/7/24.
//

#include <iostream>
#include "SudokuField.h"

SudokuField::SudokuField() {
    field = new int*[9];
    answer = new int*[9];
    check = new int*[9];
    chechers_answer = new int*[9];
    for(int i = 0; i < 9; i ++)
    {
        field[i] = new int [9];
        answer[i] = new int [9];
        check[i] = new int [9];
        chechers_answer[i] = new int[9];
    }
}

void SudokuField::SimpleBaseGenerate() {
   // srand(time(0));
    int* line = new int[9] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int* start_positions = new int [9] {0, 3, 6, 1, 4, 7, 2, 5, 8};
    for(int i = 0; i < random_number; i ++)
    {
        int x = rand() % 9;
        int y = rand() % 9;
        std::swap(line[x], line[y]);
    }
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            field[i][j] = line[(start_positions[i] + j) % 9];
            answer[i][j] = field[i][j];
        }
    }
    delete[] line;
    delete[] start_positions;
}

void SudokuField::RandomBaseGenerate() {
    //std::cout << "random base generate\n";
    srand(time(0));
    int* used_cells = new int [9] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int* cell_2 = new int [9] {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int* cell_3 = new int [9] {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int* rows = new int [9] {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < 500; i ++)
    {
        int x = rand() % 9;
        int y = rand() % 9;
        std::swap(used_cells[x], used_cells[y]);
    }
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            field[i][j] = 0;
        }
    }
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            field[i][j] = used_cells[i * 3 + j];
            rows[used_cells[i * 3 + j] - 1] += i;
        }
    }

    int* left = new int[6];
    int* left_2 = new int[6];
    int* both = new int[6];
    int pos_1 = 0, pos_2 = 0, pos_3 = 0;

    for(int i = 0; i < 6; i ++)
    {
        left[i] = used_cells[i + 3];
    }

    for(int i = 0; i < 200; i ++)
    {
        int x = rand() % 6;
        int y = rand() % 6;
        std::swap(left[x], left[y]);
    }

    for(int i = 0; i < 3; i ++)
    {
        cell_2[i] = left[i];
        cell_3[i] = left[i + 3];
    }
    for(int i = 1; i <= 9; i ++)
    {
        if(cell_2[0] == i || cell_2[1] == i || cell_2[2] == i)
        {
            // can't place anywhere
            continue;
        }
        if(rows[i - 1] == 1)
        {
            // can't place in row 1
            left_2[pos_2] = i;
            pos_2 ++;
            continue;
        }
        if(rows[i - 1] == 2)
        {
            // can't place in row 2
            left[pos_1] = i;
            pos_1 ++;
            continue;
        }
        // can place in both rows
        both[pos_3] = i;
        pos_3 ++;
    }
    for(int i = 0; i < random_number / 5; i ++)
    {
        int x, y;
        if(pos_3 != 0) {
            x = rand() % pos_3;
            y = rand() % pos_3;
            std::swap(both[x], both[y]);
        }
        if(pos_1 != 0) {
            x = rand() % pos_1;
            y = rand() % pos_1;
            std::swap(left[x], left[y]);
        }
        if(pos_2 != 0) {
            x = rand() % pos_2;
            y = rand() % pos_2;
            std::swap(left_2[x], left_2[y]);
        }
    }
    for(int i = 0; i < pos_3; i ++)
    {
        if(pos_1 == 3)
        {
            left_2[pos_2] = both[i];
            pos_2 ++;
            continue;
        }
        if(pos_2 == 3)
        {
            left[pos_1] = both[i];
            pos_1 ++;
            continue;
        }
        if(rand() % 2)
        {
            left[pos_1] = both[i];
            pos_1 ++;
            continue;
        }
        else
        {
            left_2[pos_2] = both[i];
            pos_2 ++;
            continue;
        }
    }
    for(int i = 0; i < random_number / 5; i ++)
    {
        int x;
        int y;
        x = rand() % pos_1;
        y = rand() % pos_1;
        std::swap(left[x], left[y]);
        x = rand() % pos_2;
        y = rand() % pos_2;
        std::swap(left_2[x], left_2[y]);
    }
    for(int i = 0; i < 3; i ++)
    {
        cell_2[i + 3] = left[i];
        cell_2[i + 6] = left_2[i];
    }
    for(int i = 0; i < 9; i ++)
    {
        rows[cell_2[i] - 1] += (i / 3);
    }
    pos_1 = 0, pos_2 = 0;
    for(int v = 1; v <= 9; v ++)
    {
        if(3 - rows[v - 1] == 1)
        {
            left[pos_1] = v;
            pos_1 ++;
        }
        if(3 - rows[v - 1] == 2)
        {
            left_2[pos_2] = v;
            pos_2 ++;
        }
    }

    for(int i = 0; i < random_number / 5; i ++)
    {
        int x;
        int y;
        x = rand() % pos_1;
        y = rand() % pos_1;
        std::swap(left[x], left[y]);
        x = rand() % pos_2;
        y = rand() % pos_2;
        std::swap(left_2[x], left_2[y]);
    }
    for(int i = 0; i < 3; i ++)
    {
        cell_3[i + 3] = left[i];
        cell_3[i + 6] = left_2[i];
    }
    for(int i = 0; i < 3; i ++)
    {
        for(int j = 3; j < 6; j ++)
        {
            field[i][j] = cell_2[i * 3 + j % 3];
        }
        for(int j = 6; j < 9; j ++)
        {
            field[i][j] = cell_3[i * 3 + j % 3];
        }
    }
    delete[] used_cells;
    delete[] cell_2;
    delete[] cell_3;
    delete[] left;
    delete[] left_2;
    delete[] rows;
    delete[] both;
}

int **SudokuField::GetSudokuField() {
    return field;
}

int **SudokuField::GetSudokuFieldAnswer() {
    return answer;
}

void SudokuField::SimpleLevelGenerate() {
    SimpleBaseGenerate();
    for(int t = 0; t < 500; t ++)
    {
        int type = rand() % 4;
        int x = rand() % 3, y = rand() % 3;
        switch (type){
            case 0:
            {
                // swap rows
                std::swap(field[x * 3], field[y * 3]);
                std::swap(field[x * 3 + 1], field[y * 3 + 1]);
                std::swap(field[x * 3 + 2], field[y * 3 + 2]);
                break;
            }
            case 1:
            {
                // swap rows in square
                int square = rand() % 3;
                std::swap(field[square * 3 + x], field[square * 3 + y]);
                break;
            }
            case 2:
            {
                // swap columns
                for(int i = 0; i < 9; i ++)
                {
                    std::swap(field[i][x * 3], field[i][y * 3]);
                    std::swap(field[i][x * 3 + 1], field[i][y * 3 + 1]);
                    std::swap(field[i][x * 3 + 2], field[i][y * 3 + 2]);
                }
                break;
            }
            case 3:
            {
                // swap columns in square
                int square = rand() % 3;
                for(int i = 0; i < 9; i ++)
                {
                    std::swap(field[i][square * 3 + x], field[i][square * 3 + y]);
                }
            }
        }
    }

    if(rand() % 2)
    {
        for(int i = 0; i < 9; i ++)
        {
            for(int j = i + 1; j < 9; j ++)
            {
                std::swap(field[i][j], field[j][i]);
            }
        }
    }

    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            answer[i][j] = field[i][j];
        }
    }

    for(int t = 0; t < 30; t ++)
    {
        int i = rand() % 9, j = rand() % 9;
        bool can = 0;
        if(field[i][j] != 0)
        {
            field[i][j] = 0;
            for(int new_value = 1; new_value <= 9 && can == 0; new_value ++)
            {
                if(new_value != answer[i][j])
                {
                    FillCheck();
                    field[i][j] = new_value;
                    check[i][j] = new_value;
                    if(IsValid(i, j))
                    {
                        checking_empty_cells = empty_cells;
                        bool result = IsSolvable();
                        can = std::max(result, can);
                    }
                }
            }
        }
        if(can)
        {
            field[i][j] = answer[i][j];
        }
        else
        {
            empty_cells ++;
            field[i][j] = 0;
        }
    }
}

bool SudokuField::IsValid(int i, int j) {
    for(int x = i / 3 * 3; x < (i / 3 + 1) * 3; x ++)
    {
        for(int y = j / 3 * 3; y < (j / 3 + 1) * 3; y ++)
        {
            if(check[x][y] == check[i][j] && (x != i || y != j))
                return false;
        }
    }
    for(int x = 0; x < 9; x ++)
    {
        if(check[x][j] == check[i][j] && x != i)
            return false;
    }
    for(int y = 0; y < 9; y ++)
    {
        if(check[i][y] == check[i][j] && y != j)
            return false;
    }
    return true;
}

int SudokuField::IsSolvable() {
    if(checking_empty_cells == 0)
    {
        for(int i = 0; i < 9; i ++)
        {
            for(int j = 0; j < 9; j ++)
            {
                chechers_answer[i][j] = check[i][j];
            }
        }
        return 1;
    }
    int all_solutions = 0;
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(check[i][j] == 0)
            {
                for(int new_value = 1; new_value <= 9; new_value ++)
                {
                    check[i][j] = new_value;
                    if(IsValid(i, j))
                    {
                        checking_empty_cells --;
                        all_solutions += IsSolvable();
                        if(all_solutions > 1)
                            return 2;
                        checking_empty_cells ++;
                    }
                }
                check[i][j] = 0;
                return all_solutions;
            }
        }
    }
    return all_solutions;
}

void SudokuField::DifficultLevelGenerate(int min_difficulty, int max_difficulty) {

    //freopen("output.txt", "w", stdout);
    RandomBaseGenerate();
    empty_cells = 81-27;
    int current_difficulty = 5000;
    //for(int i = 0; i < 500; i ++)
    while(current_difficulty < min_difficulty || current_difficulty > max_difficulty)
    {
       // std::cout << "ok generate in " << i << " time\n";
        checking_empty_cells = empty_cells;
        if(rand() % 4)
        {
            if(current_difficulty < min_difficulty)
            {
                // let's delete some cells
                already_unique = 0;
                std::cout << "delete\n";
                TryDeleteCell();
            }
            else
            {
                // let's add some cells
                std::cout << "add\n";
                TryAddCell();
            }
        }
        else
        {
            if(current_difficulty < min_difficulty)
            {
                // random move let's add some cells
                std::cout << "add\n";
                TryAddCell();
            }
            else
            {
                // random move let's delete some cells
                already_unique = 0;
                std::cout << "delete\n";
                TryDeleteCell();
            }
        }
        std::cout << "generated. now calculate difficulty\n";
        FillAllCandidates();
        FillCheck();
        //current_difficulty = rand() % 500 + 1;
        current_difficulty = CalculateDifficulty();
        std::cout << "generated with difficulty " << current_difficulty << "\n";
    }
}

void SudokuField::FillAnswer() {
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            answer[i][j] = chechers_answer[i][j];
        }
    }
}

void SudokuField::FillCheck() {
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            check[i][j] = field[i][j];
        }
    }
}

// add function
int SudokuField::GetDifficulty() {

    if(checking_empty_cells == 0)
    {
        return 0;
    }
    int min_value = 10;
    std::pair<int, int> position;
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(check[i][j] != 0)
                continue;
            if(candidates[i][j].size() < min_value)
            {
                min_value = candidates[i][j].size();
                position = {i, j};
            }
        }
    }
    if(min_value == 0)
    {
        // unsolvable
        return -1;
    }
    int t = -1;
    all_sum += ((min_value - 1) * (min_value - 1));
    for(auto value: candidates[position.first][position.second])
    {
        check[position.first][position.second] = value;
        checking_empty_cells --;
        FillCrossCandidates(position.first, position.second);
        t = std::max(GetDifficulty(), t);
        checking_empty_cells ++;
    }

    check[position.first][position.second] = 0;
    FillCrossCandidates(position.first, position.second);
    return t;
}

void SudokuField::TryAddCell() {
    while (empty_cells > 0)
    {
        checking_empty_cells = empty_cells;
        int x = rand() % 9, y = rand() % 9;
        if(field[x][y] == 0)
        {
            int value = rand() % 9 + 1;
            FillCheck();
            check[x][y] = value;
            if(IsValid(x, y))
            {
                checking_empty_cells --;
                int answers = IsSolvable();
                if(answers == 1)
                {
                    already_unique = 1;
                    FillAnswer();
                    // unique answer found
                    field[x][y] = value;
                    empty_cells --;
                    return;
                }
                if(answers > 1)
                {
                    empty_cells --;
                    field[x][y] = value;
                    // multiply answers
                    // should add some more
                    continue;
                }
                checking_empty_cells ++; // ?
                // no answer found - impossible
            }
            check[x][y] = 0;
        }
    }
}

void SudokuField::TryDeleteCell() {
    for(int i = 0; i < 10; i ++)
    {
        checking_empty_cells = empty_cells;
        int x = rand() % 9, y = rand() % 9;
        if(field[x][y] != 0)
        {
            FillCheck();
            check[x][y] = 0;
            checking_empty_cells = empty_cells + 1;
            int answers = IsSolvable();
            if(answers == 1)
            {
                // unique answer found
                already_unique = 1;
                FillAnswer();
                field[x][y] = 0;
                empty_cells ++;
                break;
            }
            if(answers > 1)
            {
                // multiply answers
                already_unique = 0;
                empty_cells ++;
                field[x][y] = 0;
                continue;
            }
            // no answer found - impossible
        }
    }
    if(already_unique == 0)
    {
        TryAddCell();
    }
}

int SudokuField::CalculateDifficulty() {
    empty_cells = 0;
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(check[i][j] == 0)
                empty_cells ++;
        }
    }
    checking_empty_cells = empty_cells;
    FillAllCandidates();
    all_sum = 0;
    GetDifficulty();
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            std::cout << check[i][j];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << all_sum << " all sum " << empty_cells << "\n";
    return 100 * all_sum + empty_cells;
}

int SudokuField::CalculateDifficulty(int **arr) {
    empty_cells = 0;
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            check[i][j] = arr[i][j];
            if(arr[i][j] == 0)
                empty_cells ++;
            std::cout << check[i][j];
        }
        std::cout << '\n';
    }
    checking_empty_cells = empty_cells;
    //std::cout << "empty cells = " << empty_cells << '\n';
    FillAllCandidates();
    all_sum = 0;
    GetDifficulty();
    std::cout << all_sum << " all sum \n";
    return 100 * all_sum + empty_cells;
}

void SudokuField::OptimisedIsSolvable() {

}

void SudokuField::FillAllCandidates() {
    //FillCheck();
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            candidates[i][j].clear();
            if(check[i][j] != 0)
                candidates[i][j].push_back(check[i][j]);
            else
            {
                for(int value = 1; value <= 9; value ++)
                {
                    check[i][j] = value;
                    if(IsValid(i, j))
                        candidates[i][j].push_back(value);
                }
                check[i][j] = 0;
            }
        }
    }
}

void SudokuField::FillCrossCandidates(int i, int j) {
    candidates[i][j].clear();
    candidates[i][j].push_back(check[i][j]);
    for(int x = 0; x < 9; x ++)
    {
        if(x == i)
            continue;
        if(check[x][j] != 0)
        {
            continue;
        }
        candidates[x][j].clear();
        for(int value = 1; value <= 9; value ++)
        {
            check[x][j] = value;
            if(IsValid(x, j))
                candidates[x][j].push_back(value);
        }
        check[x][j] = 0;
    }
    for(int y = 0; y < 9; y ++)
    {
        if(y == j)
            continue;
        if(check[i][y] != 0)
        {
            continue;
        }
        candidates[i][y].clear();
        for(int value = 1; value <= 9; value ++)
        {
            check[i][y] = value;
            if(IsValid(i, y))
                candidates[i][y].push_back(value);
        }
        check[i][y] = 0;
    }
    for(int x = i / 3 * 3; x < (i / 3 + 1) * 3; x ++)
    {
        for(int y = j / 3 * 3; y < (j / 3 + 1) * 3; y ++)
        {
            if(x == i && y == j)
                continue;
            if(check[x][y] != 0)
                continue;

            for(int value = 1; value <= 9; value ++)
            {
                check[x][y] = value;
                if(IsValid(x, y))
                    candidates[x][y].push_back(value);
            }
            check[x][y] = 0;
        }
    }
}

bool SudokuField::TryFill(int row, int column, int number) {
    if(answer[row - 1][column - 1] == number) {
        field[row - 1][column - 1] = number;
        return true;
    }
    return false;
}

int SudokuField::GiveHint() {
    FillAllCandidates();
    // obvious single
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(candidates[i][j].size() == 1 && field[i][j] == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

QString SudokuField::GetHint() {
    int type = GiveHint();
    switch (type) {
        case 1:
            return "Single one";
    }
    return "brute";
}



