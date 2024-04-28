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
    void DifficultLevelGenerate(int min_difficulty, int max_difficulty);
    void SimpleLevelGenerate();
    int CalculateDifficulty(int** arr);
    bool TryFill(int row, int column, int number);
    QString GetHint();

private:
    int CalculateDifficulty();
    int GiveHint();
    int GetDifficulty();
    int IsSolvable();
    bool IsValid(int i, int j);
    void FillAnswer();
    void FillCheck();
    void FillAllCandidates();
    bool FillAnswerGrid();
    void FillCrossCandidates(int i, int j);
    void RandomBaseGenerate();
    void SimpleBaseGenerate();
    bool TryAddCell();
    bool TryDeleteCell();
    int** field;
    int** check;
    int** answer;
    int** chechers_answer;
    int** candidates;
    int** state_of_cell;
    int empty_cells = 0;
    int checking_empty_cells = 0;
    int field_difficulty = 0;
    bool already_unique = 0;
    int all_sum = 0;
    const int random_number = 100;
    std::vector<int> empty_cell, not_empty_cell;

};


#endif //MAIN_VARIANT_SUDOKUFIELD_H