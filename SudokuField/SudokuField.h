//
// Created by darina on 4/7/24.
//

#ifndef MAIN_VARIANT_SUDOKUFIELD_H
#define MAIN_VARIANT_SUDOKUFIELD_H


#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <QVector>
#include <vector>

class SudokuField {
public:
    SudokuField();

    int** GetSudokuField();
    int** GetSudokuFieldAnswer();
    int CalculateDifficulty(int** arr);

private:
    int CalculateDifficulty();
    int GetDifficulty();
    void FillAnswer();
    bool FillAnswerGrid();
    void FillCrossCandidates(int i, int j);
    void RandomBaseGenerate();
    void SimpleBaseGenerate();
    bool TryAddCell();
    bool TryDeleteCell();
    int** chechers_answer;
    int** state_of_cell;
    int empty_cells = 0;
    int checking_empty_cells = 0;
    int field_difficulty = 0;
    bool already_unique = 0;
    int all_sum = 0;
    const int random_number = 100;
    const int number_do_random = 3;
    const int number_left_min = 1;
    int bad_get = 0;
    std::vector<int> empty_cell, not_empty_cell;

protected:
    void DifficultLevelGenerate(int min_difficulty, int max_difficulty);
    void SimpleLevelGenerate();
    void FillAllCandidates();
    bool IsValid(int i, int j);
    void FillCheck();
    int IsSolvable();
    bool Solve();
    int** field;
    int** answer;
    int** candidates;
    int** check;

};


#endif //MAIN_VARIANT_SUDOKUFIELD_H