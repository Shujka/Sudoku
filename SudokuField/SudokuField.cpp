//
// Created by darina on 4/7/24.
//

#include <iostream>
#include "SudokuField.h"

SudokuField::SudokuField() {
    field = new int *[9];
    answer = new int *[9];
    check = new int *[9];
    chechers_answer = new int *[9];
    candidates = new int *[9];
    state_of_cell = new int *[9];
    for (int i = 0; i < 9; i++) {
        field[i] = new int[9];
        answer[i] = new int[9];
        check[i] = new int[9];
        chechers_answer[i] = new int[9];
        candidates[i] = new int[9];
        state_of_cell[i] = new int[9];
    }
}

// completely done
void SudokuField::SimpleBaseGenerate() {
    // srand(time(0));
    int *line = new int[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *start_positions = new int[9]{0, 3, 6, 1, 4, 7, 2, 5, 8};
    for (int i = 0; i < random_number; i++) {
        int x = rand() % 9;
        int y = rand() % 9;
        std::swap(line[x], line[y]);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = line[(start_positions[i] + j) % 9];
            answer[i][j] = field[i][j];
        }
    }
    delete[] line;
    delete[] start_positions;
}

// completely done
void SudokuField::RandomBaseGenerate() {
    //std::cout << "random base generate\n";
    //srand(time(nullptr));
    int *used_cells = new int[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *cell_2 = new int[9]{0, 0, 0, 0, 0, 0, 0, 0, 0};
    int *cell_3 = new int[9]{0, 0, 0, 0, 0, 0, 0, 0, 0};
    int *rows = new int[9]{0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 500; i++) {
        int x = rand() % 9;
        int y = rand() % 9;
        std::swap(used_cells[x], used_cells[y]);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            field[i][j] = used_cells[i * 3 + j];
            rows[used_cells[i * 3 + j] - 1] += i;
        }
    }

    int *left = new int[6];
    int *left_2 = new int[6];
    int *both = new int[6];
    int pos_1 = 0, pos_2 = 0, pos_3 = 0;

    for (int i = 0; i < 6; i++) {
        left[i] = used_cells[i + 3];
    }

    for (int i = 0; i < 200; i++) {
        int x = rand() % 6;
        int y = rand() % 6;
        std::swap(left[x], left[y]);
    }

    for (int i = 0; i < 3; i++) {
        cell_2[i] = left[i];
        cell_3[i] = left[i + 3];
    }
    for (int i = 1; i <= 9; i++) {
        if (cell_2[0] == i || cell_2[1] == i || cell_2[2] == i) {
            // can't place anywhere
            continue;
        }
        if (rows[i - 1] == 1) {
            // can't place in row 1
            left_2[pos_2] = i;
            pos_2++;
            continue;
        }
        if (rows[i - 1] == 2) {
            // can't place in row 2
            left[pos_1] = i;
            pos_1++;
            continue;
        }
        // can place in both rows
        both[pos_3] = i;
        pos_3++;
    }
    for (int i = 0; i < random_number / 5; i++) {
        int x, y;
        if (pos_3 != 0) {
            x = rand() % pos_3;
            y = rand() % pos_3;
            std::swap(both[x], both[y]);
        }
        if (pos_1 != 0) {
            x = rand() % pos_1;
            y = rand() % pos_1;
            std::swap(left[x], left[y]);
        }
        if (pos_2 != 0) {
            x = rand() % pos_2;
            y = rand() % pos_2;
            std::swap(left_2[x], left_2[y]);
        }
    }
    for (int i = 0; i < pos_3; i++) {
        if (pos_1 == 3) {
            left_2[pos_2] = both[i];
            pos_2++;
            continue;
        }
        if (pos_2 == 3) {
            left[pos_1] = both[i];
            pos_1++;
            continue;
        }
        if (rand() % 2) {
            left[pos_1] = both[i];
            pos_1++;
            continue;
        } else {
            left_2[pos_2] = both[i];
            pos_2++;
            continue;
        }
    }
    for (int i = 0; i < random_number / 5; i++) {
        int x;
        int y;
        x = rand() % pos_1;
        y = rand() % pos_1;
        std::swap(left[x], left[y]);
        x = rand() % pos_2;
        y = rand() % pos_2;
        std::swap(left_2[x], left_2[y]);
    }
    for (int i = 0; i < 3; i++) {
        cell_2[i + 3] = left[i];
        cell_2[i + 6] = left_2[i];
    }
    for (int i = 0; i < 9; i++) {
        rows[cell_2[i] - 1] += (i / 3);
    }
    pos_1 = 0, pos_2 = 0;
    for (int v = 1; v <= 9; v++) {
        if (3 - rows[v - 1] == 1) {
            left[pos_1] = v;
            pos_1++;
        }
        if (3 - rows[v - 1] == 2) {
            left_2[pos_2] = v;
            pos_2++;
        }
    }

    for (int i = 0; i < random_number / 5; i++) {
        int x;
        int y;
        x = rand() % pos_1;
        y = rand() % pos_1;
        std::swap(left[x], left[y]);
        x = rand() % pos_2;
        y = rand() % pos_2;
        std::swap(left_2[x], left_2[y]);
    }
    for (int i = 0; i < 3; i++) {
        cell_3[i + 3] = left[i];
        cell_3[i + 6] = left_2[i];
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 6; j++) {
            field[i][j] = cell_2[i * 3 + j % 3];
        }
        for (int j = 6; j < 9; j++) {
            field[i][j] = cell_3[i * 3 + j % 3];
        }
    }


    // Provide final grid
    // add vector of empty cells and not empty cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            not_empty_cell.push_back(i * 10 + j);
            state_of_cell[i][j] = 1;
        }
    }
    for (int i = 3; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            empty_cell.push_back(i * 10 + j);
            state_of_cell[i][j] = 0;
        }
    }
    checking_empty_cells = 81 - 27;
    FillAllCandidates();
    FillAnswerGrid();
    FillCheck();

    not_empty_cell.clear();
    empty_cell.clear();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            answer[i][j] = field[i][j];
            not_empty_cell.push_back(i * 10 + j);
            state_of_cell[i][j] = 1;
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

// completely done
int **SudokuField::GetSudokuField() {
    return field;
}

//completely done
int **SudokuField::GetSudokuFieldAnswer() {
    return answer;
}

// completely done
void SudokuField::SimpleLevelGenerate() {
    srand(time(nullptr));
    SimpleBaseGenerate();
    for (int t = 0; t < 500; t++) {
        int type = rand() % 4;
        int x = rand() % 3, y = rand() % 3;
        switch (type) {
            case 0: {
                // swap rows
                std::swap(field[x * 3], field[y * 3]);
                std::swap(field[x * 3 + 1], field[y * 3 + 1]);
                std::swap(field[x * 3 + 2], field[y * 3 + 2]);
                break;
            }
            case 1: {
                // swap rows in square
                int square = rand() % 3;
                std::swap(field[square * 3 + x], field[square * 3 + y]);
                break;
            }
            case 2: {
                // swap columns
                for (int i = 0; i < 9; i++) {
                    std::swap(field[i][x * 3], field[i][y * 3]);
                    std::swap(field[i][x * 3 + 1], field[i][y * 3 + 1]);
                    std::swap(field[i][x * 3 + 2], field[i][y * 3 + 2]);
                }
                break;
            }
            default: {
                // swap columns in square
                int square = rand() % 3;
                for (int i = 0; i < 9; i++) {
                    std::swap(field[i][square * 3 + x], field[i][square * 3 + y]);
                }
            }
        }
    }

    if (rand() % 2) {
        for (int i = 0; i < 9; i++) {
            for (int j = i + 1; j < 9; j++) {
                std::swap(field[i][j], field[j][i]);
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            answer[i][j] = field[i][j];
        }
    }

    for (int t = 0; t < 50; t++) {
        int i = rand() % 9, j = rand() % 9;
        int can = 0;
        if (field[i][j] != 0) {
            field[i][j] = 0;
            FillAllCandidates();
            int result = IsSolvable();
            can = std::max(can, result);
        }
        if (can > 1) {
            field[i][j] = answer[i][j];
        } else {
            empty_cells++;
            field[i][j] = 0;
        }
    }
}

// completely done
bool SudokuField::IsValid(int i, int j) {
    for (int x = i / 3 * 3; x < (i / 3 + 1) * 3; x++) {
        for (int y = j / 3 * 3; y < (j / 3 + 1) * 3; y++) {
            if (check[x][y] == check[i][j] && (x != i || y != j))
                return false;
        }
    }
    for (int x = 0; x < 9; x++) {
        if (check[x][j] == check[i][j] && x != i)
            return false;
    }
    for (int y = 0; y < 9; y++) {
        if (check[i][y] == check[i][j] && y != j)
            return false;
    }
    return true;
}

// completely done
int SudokuField::IsSolvable() {
    if (checking_empty_cells == 0) {
        return 1;
    }
    //std::cout << checking_empty_cells << "|";
    /*for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(check[i][j] == 0)
            {

                int t = 0;
                for(int value = 1; value <= 9; value ++)
                {
                    check[i][j] = value;
                    if(IsValid(i, j))
                    {
                        checking_empty_cells --;
                        t += IsSolvable();
                        checking_empty_cells ++;
                    }
                    check[i][j] = 0;
                    if(t > 1)
                        return t;
                }
                return t;
            }
        }
    }

    exit(0);*/

    int min_value = 10;
    std::pair<int, int> position;

    // search for cell with minimum possible candidates

//    std::cout<<"candidates:"<<' '<<checking_empty_cells<<std::endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (check[i][j] != 0)
                continue;
//            std::cout<<i<<' '<<j<<' '<<candidates[i][j]<<' '<<__builtin_popcount(candidates[i][j])<<std::endl;
            if (__builtin_popcount(candidates[i][j]) < min_value) {
                min_value = __builtin_popcount(candidates[i][j]);
                position = {i, j};
            }
        }
    }

    // search for value that occupy minimum cells in columns
    /*int number_in_column = 0, column = 0, amount_in_column = 10;
    for (int value = 1; value <= 9; value++) {
        for (int j = 0; j < 9; j++) {
            int current_amount = 0;
            for (int i = 0; i < 9; i++) {
                if (check[i][j] != 0)
                    continue;
                current_amount += ((candidates[i][j] >> value) & 1);
            }
            if (current_amount < amount_in_column && current_amount != 0) {
                number_in_column = value;
                column = j;
                amount_in_column = current_amount;
            }
        }
    }

    // search for value that occupy minimum cells in row
    int number_in_row = 0, row = 0, amount_in_row = 10;
    for (int value = 1; value <= 9; value++) {
        for (int i = 0; i < 9; i++) {
            int current_amount = 0;
            for (int j = 0; j < 9; j++) {
                if (check[i][j] != 0)
                    continue;
                current_amount += ((candidates[i][j] >> value) & 1);
            }
            if (current_amount < amount_in_row && current_amount != 0) {
                number_in_row = value;
                row = i;
                amount_in_row = current_amount;
            }
        }
    }

    //search for value that occupy minimum cells in square 3*3
    int number_in_square = 0, square = 0, amount_in_square = 10;
    for (int value = 1; value <= 9; value++) {
        for (int start_i = 0; start_i < 9; start_i += 3) {
            for (int start_j = 0; start_j < 9; start_j += 3) {
                int current_amount = 0;
                for (int i = start_i; i < start_i + 3; i++) {
                    for (int j = start_j; j < start_j + 3; j++) {
                        if (check[i][j] != 0)
                            continue;
                        current_amount += ((candidates[i][j] >> value) & 1);
                    }
                }
                if (current_amount < amount_in_square && current_amount != 0) {
                    number_in_square = value;
                    square = start_i * 10 + start_j;
                    amount_in_square = current_amount;
                }
            }
        }
    }
*/
    if (min_value == 0) {

     //   std::cout << ":)\n";
        return 0;
    }

   // if (min_value <= amount_in_column && min_value <= amount_in_row && min_value <= amount_in_square) {
        int t = 0;
        for (int i = 1; i <= 9; i++) {
            if (((candidates[position.first][position.second]) & (1 << i)) == 0)
                continue;
//            std::cout<<"good boy: "<<position.first<<' '<<position.second<<' '<<i<<std::endl;
            check[position.first][position.second] = i;
            checking_empty_cells--;
            FillCrossCandidates(position.first, position.second);
            t += IsSolvable();
            checking_empty_cells++;
            check[position.first][position.second] = 0;
            FillCrossCandidates(position.first, position.second);
            if (t > 1)
                return t;
        }
        return t;
/*    }

    if (amount_in_row <= amount_in_square && amount_in_row <= amount_in_column) {
        int t = 0;
        for (int j = 0; j < 9; j++) {
            if (((candidates[row][j] >> number_in_row) & 1) && check[row][j] == 0) {
                check[row][j] = number_in_row;
                checking_empty_cells--;
                FillCrossCandidates(row, j);
                t += IsSolvable();
                checking_empty_cells++;
                check[row][j] = 0;
                FillCrossCandidates(row, j);
                if (t > 1)
                    return t;
            }
        }
        return t;
    }

    if (amount_in_column <= amount_in_square) {
        int t = 0;
        for (int i = 0; i < 9; i++) {
            if (((candidates[i][column] >> number_in_column) & 1) && check[i][column] == 0) {
                check[i][column] = number_in_column;
                checking_empty_cells--;
                FillCrossCandidates(i, column);
                t += IsSolvable();
                checking_empty_cells++;
                check[i][column] = 0;
                FillCrossCandidates(i, column);
                if (t > 1)
                    return t;
            }
        }
 //       std::cout << t << std::endl;
        return t;
    }

    int t = 0;
    for (int i = square / 10; i < square / 10 + 3; i++) {
        for (int j = square % 10; j < square % 10 + 3; j++) {
            if (check[i][j] != 0)
                continue;
            if ((candidates[i][j] >> number_in_square) & 1) {
                check[i][j] = number_in_square;
                checking_empty_cells--;
                FillCrossCandidates(i, j);
                t += IsSolvable();
                checking_empty_cells++;
                check[i][j] = 0;
                FillCrossCandidates(i, j);
                if (t > 1)
                    return 2;
            }
        }
    }
    return t;*/
    std::cout << "loh" << std::endl;
}

// completely done
void SudokuField::DifficultLevelGenerate(int min_difficulty, int max_difficulty) {

    std::cout << "min " << min_difficulty << " " << max_difficulty << '\n';
    srand(time(nullptr));
    RandomBaseGenerate();

    empty_cells = 0;
    int remember_difficulty = 0;
    int **remember = new int *[9];
    for (int i = 0; i < 9; i++) {
        remember[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            remember[i][j] = field[i][j];
        }
    }

    for (int i = 0; i < 2000; i++) {
          //  std::cout << " i = " << i << " " << empty_cells << " " << empty_cell.size() + not_empty_cell.size() << " "
          //           << '\n';
        std::cout << "i = " << i << '\n';
        FillAllCandidates();
        int k;
        if (empty_cells > 81 - 17)
            k = 2;
        else
            k = IsSolvable();

        std::cout << "is solvable = " << k << '\n';

        if (k == 1) {
            FillAllCandidates();
            int c = CalculateDifficulty();
            std::cout << "generated with difficulty " << c << '\n';
            std::cout<<"field: "<<std::endl;
            for(int x = 0; x < 9; x++){
                for(int y = 0; y < 9; y++){
                    std::cout<<field[x][y]<<' ';
                }
                std::cout<<std::endl;
            }

            if (c > remember_difficulty || (c >= min_difficulty && c <= max_difficulty)) {
                remember_difficulty = c;
                for (int i2 = 0; i2 < 9; i2++) {
                    for (int j = 0; j < 9; j++) {
                        remember[i2][j] = field[i2][j];
                    }
                }
            } else {
                empty_cells = 0;
                empty_cell.clear();
                not_empty_cell.clear();
                for (int i2 = 0; i2 < 9; i2++) {
                    for (int j = 0; j < 9; j++) {
                        field[i2][j] = remember[i2][j];
                        if (field[i2][j] == 0) {
                            empty_cells++;
                            empty_cell.push_back(i2 * 10 + j);
                        } else {
                            not_empty_cell.push_back(i2 * 10 + j);
                        }
                    }
                }
            }
            if (remember_difficulty >= min_difficulty && remember_difficulty <= max_difficulty) {
                goto ttt;
            }
            //int random_number_delete = rand() % 15;
            //for (int j = 0; j < random_number_delete; j++) {
            if (TryDeleteCell())
                empty_cells++;
            //}
        } else {
            FillAllCandidates();
            int try_add_number = rand() % 3 + 1;
            for(int j = 0; j < try_add_number; j ++)
            {
                if (TryAddCell()) {
                    empty_cells--;
                    FillAllCandidates();
                }
            }
        }
    }
    ttt:;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = remember[i][j];
        }
    }
    std::cout << "finally " << remember_difficulty << '\n';
    for (int i = 0; i < 9; i++) {
        delete[] remember[i];
    }
    delete[] remember;
}

// completely done
// work with checkers_answer
void SudokuField::FillAnswer() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            answer[i][j] = chechers_answer[i][j];
        }
    }
}

// completely done
// work with playersfield
void SudokuField::FillCheck() {
    checking_empty_cells = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            check[i][j] = field[i][j];
            if(check[i][j] == 0)
                checking_empty_cells ++;
        }
    }
}

// completely done (i hope)
int SudokuField::GetDifficulty() {

    if (checking_empty_cells == 0) {
        for(int i = 0; i < 9; i ++)
        {
            for(int j = 0; j < 9; j ++)
            {
                answer[i][j] = check[i][j];
            }
        }
        return 0;

    }

    int min_value = 10;
    std::pair<int, int> position;

    // search for cell with minimum possible candidates
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (check[i][j] != 0)
                continue;
            if (__builtin_popcount(candidates[i][j]) < min_value) {
                min_value = __builtin_popcount(candidates[i][j]);
                position = {i, j};
            }
        }
    }

    // search for value that occupy minimum cells in columns
    int number_in_column = 0, column = 0, amount_in_column = 10;
    for (int value = 1; value <= 9; value++) {
        for (int j = 0; j < 9; j++) {
            int current_amount = 0;
            for (int i = 0; i < 9; i++) {
                if (check[i][j] != 0)
                    continue;
                current_amount += ((candidates[i][j] >> value) & 1);
            }
            if (current_amount < amount_in_column && current_amount != 0) {
                number_in_column = value;
                column = j;
                amount_in_column = current_amount;
            }
        }
    }

    // search for value that occupy minimum cells in row
    int number_in_row = 0, row = 0, amount_in_row = 10;
    for (int value = 1; value <= 9; value++) {
        for (int i = 0; i < 9; i++) {
            int current_amount = 0;
            for (int j = 0; j < 9; j++) {
                if (check[i][j] != 0)
                    continue;
                current_amount += ((candidates[i][j] >> value) & 1);
            }
            if (current_amount < amount_in_row && current_amount != 0) {
                number_in_row = value;
                row = i;
                amount_in_row = current_amount;
            }
        }
    }

    //search for value that occupy minimum cells in square 3*3
    int number_in_square = 0, square = 0, amount_in_square = 10;
    for (int value = 1; value <= 9; value++) {
        for (int start_i = 0; start_i < 9; start_i += 3) {
            for (int start_j = 0; start_j < 9; start_j += 3) {
                int current_amount = 0;
                for (int i = start_i; i < start_i + 3; i++) {
                    for (int j = start_j; j < start_j + 3; j++) {
                        if (check[i][j] != 0)
                            continue;
                        current_amount += ((candidates[i][j] >> value) & 1);
                    }
                }
                if (current_amount < amount_in_square && current_amount != 0) {
                    number_in_square = value;
                    square = start_i * 10 + start_j;
                    amount_in_square = current_amount;
                }
            }
        }
    }

    if (min_value == 0) {
        // unsolvable
        return 0;
    }

    if (min_value <= amount_in_column && min_value <= amount_in_row && min_value <= amount_in_square) {
        int t = -1;
        //   std::cout << "good position\n";
        all_sum += ((min_value - 1) * (min_value - 1));
        for (int i = 1; i <= 9; i++) {
            if (((candidates[position.first][position.second] >> i) & 1) == 0)
                continue;
            check[position.first][position.second] = i;
            checking_empty_cells--;
            FillCrossCandidates(position.first, position.second);
            t = std::max(GetDifficulty(), t);
            checking_empty_cells++;
            check[position.first][position.second] = 0;
            FillCrossCandidates(position.first, position.second);
        }
        return t;
    }
    if (amount_in_row <= amount_in_square && amount_in_row <= amount_in_column) {
        int t = -1;
        //   std::cout << "good row\n";
        all_sum += ((amount_in_row - 1) * (amount_in_row - 1));
        for (int j = 0; j < 9; j++) {
            if (((candidates[row][j] >> number_in_row) & 1) && check[row][j] == 0) {
                check[row][j] = number_in_row;
                checking_empty_cells--;
                FillCrossCandidates(row, j);
                t = std::max(GetDifficulty(), t);
                checking_empty_cells++;
                check[row][j] = 0;
                FillCrossCandidates(row, j);
            }
        }
        return t;
    }
    if (amount_in_column <= amount_in_square) {
        //   std::cout << "good column\n";
        int t = -1;
        all_sum += ((amount_in_column - 1) * (amount_in_column - 1));
        for (int i = 0; i < 9; i++) {
            if (((candidates[i][column] >> number_in_column) & 1) && check[i][column] == 0) {
                check[i][column] = number_in_column;
                checking_empty_cells--;
                FillCrossCandidates(i, column);
                t = std::max(GetDifficulty(), t);
                checking_empty_cells++;
                check[i][column] = 0;
                FillCrossCandidates(i, column);
            }
        }
        return t;
    }
    int t = -1;
    //std::cout << "good square\n";
    all_sum += ((amount_in_square - 1) * (amount_in_square - 1));
    for (int i = square / 10; i < square / 10 + 3; i++) {
        for (int j = square % 10; j < square % 10 + 3; j++) {
            if (check[i][j] != 0)
                continue;
            if ((candidates[i][j] >> number_in_square) & 1) {
                check[i][j] = number_in_square;
                checking_empty_cells--;
                FillCrossCandidates(i, j);
                t = std::max(t, GetDifficulty());
                checking_empty_cells++;
                check[i][j] = 0;
                FillCrossCandidates(i, j);
            }
        }
    }
    return t;
}

// completely done
bool SudokuField::TryAddCell() {
    if (empty_cell.empty())
        return false;
    int position = empty_cell[rand() % empty_cell.size()];
    int x = position / 10, y = position % 10;
    field[x][y] = answer[x][y];
    check[x][y] = answer[x][y];
    empty_cell.clear();
    not_empty_cell.clear();
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(field[i][j])
            {
                not_empty_cell.push_back(i * 10 + j);
            }
            else
            {
                empty_cell.push_back(i * 10 + j);
            }
        }
    }
    return true;
}

// completely done
bool SudokuField::TryDeleteCell() {
    if (not_empty_cell.empty())
        return false;
    int position = not_empty_cell[rand() % not_empty_cell.size()];
    int x = position / 10, y = position % 10;
    field[x][y] = 0;
    check[x][y] = 0;
    empty_cell.clear();
    not_empty_cell.clear();
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(field[i][j])
            {
                not_empty_cell.push_back(i * 10 + j);
            }
            else
            {
                empty_cell.push_back(i * 10 + j);
            }
        }
    }
    /*
    not_empty_cell.erase(std::find(not_empty_cell.begin(), not_empty_cell.end(), x * 10 + y));
    empty_cell.push_back(x * 10 + y);*/
    return true;
}

// completely done
int SudokuField::CalculateDifficulty() {
    checking_empty_cells = empty_cells;
    FillAllCandidates();
    all_sum = 0;
    GetDifficulty();
    return 100 * all_sum + empty_cells;
}

// for main
// completely done
int SudokuField::CalculateDifficulty(int **arr) {
    empty_cells = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            check[i][j] = arr[i][j];
            if (arr[i][j] == 0)
                empty_cells++;
        }
    }
    checking_empty_cells = empty_cells;
    //std::cout << "empty cells = " << empty_cells << '\n';
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            candidates[i][j] = 0;
            if (check[i][j] != 0) {
                candidates[i][j] = (1 << check[i][j]);
            } else {
                for (int value = 1; value <= 9; value++) {
                    check[i][j] = value;
                    if (IsValid(i, j))
                        candidates[i][j] += (1 << value);
                }
                check[i][j] = 0;
            }
        }
    }
    all_sum = 0;
    GetDifficulty();
    return 100 * all_sum + empty_cells;
}

//completely done
void SudokuField::FillAllCandidates() {
    FillCheck();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            candidates[i][j] = 0;
            if (check[i][j] != 0) {
                candidates[i][j] = (1 << check[i][j]);
            } else {
                for (int value = 1; value <= 9; value++) {
                    check[i][j] = value;
                    if (IsValid(i, j))
                        candidates[i][j] += (1 << value);
                }
                check[i][j] = 0;
            }
        }
    }
}

//completely done
void SudokuField::FillCrossCandidates(int i, int j) {
    //FillAllCandidates();

    candidates[i][j] = 0;
    if (check[i][j] != 0) {
        candidates[i][j] = (1 << check[i][j]);
    } else {
        for (int value = 1; value <= 9; value++) {
            check[i][j] = value;
            if (IsValid(i, j))
                candidates[i][j] += (1 << value);
            check[i][j] = 0;
        }
    }
    for (int x = 0; x < 9; x++) {
        if (x == i)
            continue;
        if (check[x][j] != 0) {
            continue;
        }
        candidates[x][j] = 0;
        for (int value = 1; value <= 9; value++) {
            check[x][j] = value;
            if (IsValid(x, j))
                candidates[x][j] += (1 << value);
        }
        check[x][j] = 0;
    }
    for (int y = 0; y < 9; y++) {
        if (y == j)
            continue;
        if (check[i][y] != 0) {
            continue;
        }
        candidates[i][y] = 0;
        for (int value = 1; value <= 9; value++) {
            check[i][y] = value;
            if (IsValid(i, y))
                candidates[i][y] += (1 << value);
        }
        check[i][y] = 0;
    }
    for (int x = i / 3 * 3; x < (i / 3 + 1) * 3; x++) {
        for (int y = j / 3 * 3; y < (j / 3 + 1) * 3; y++) {
            if (x == i && y == j)
                continue;
            if (check[x][y] != 0)
                continue;

            candidates[x][y] = 0;
            for (int value = 1; value <= 9; value++) {
                check[x][y] = value;
                if (IsValid(x, y))
                    candidates[x][y] += (1 << value);
            }
            check[x][y] = 0;
        }
    }
}

// completely done
bool SudokuField::FillAnswerGrid() {
    if (checking_empty_cells == 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                field[i][j] = check[i][j];
            }
        }
        return true;
    }
    int position = empty_cell[rand() % empty_cell.size()];
    QVector<int> candidate = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (auto x: empty_cell) {
        int i = x / 10, j = x % 10;
        QVector<int> new_candidate;
        for (int value = 1; value <= 9; value++) {
            check[i][j] = value;
            if (IsValid(i, j))
                new_candidate.push_back(value);
            check[i][j] = 0;
        }
        if (new_candidate.size() < candidate.size()) {
            position = x;
            std::swap(new_candidate, candidate);
            continue;
        }
        if ((new_candidate.size() == candidate.size()) && (rand() % 2)) {
            position = x;
            std::swap(new_candidate, candidate);
            continue;
        }
    }
    if (candidate.size() > 9 || candidate.empty())
        return false;
    int i = position / 10, j = position % 10;
    for (int t = 0; t < random_number; t++) {
        int x = rand() % candidate.size();
        int y = rand() % candidate.size();
        std::swap(x, y);
    }
    for (auto value: candidate) {
        check[i][j] = value;
        checking_empty_cells--;
        empty_cell.erase(std::find(empty_cell.begin(), empty_cell.end(), i * 10 + j));
        not_empty_cell.push_back(i * 10 + j);
        bool t = FillAnswerGrid();
        check[i][j] = 0;
        not_empty_cell.erase(std::find(not_empty_cell.begin(), not_empty_cell.end(), i * 10 + j));
        empty_cell.push_back(i * 10 + j);
        checking_empty_cells++;
        if (t)
            return true;
    }
    return false;
}
