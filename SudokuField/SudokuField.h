//
// Created by darina on 4/7/24.
//

#ifndef MAIN_VARIANT_SUDOKUFIELD_H
#define MAIN_VARIANT_SUDOKUFIELD_H


#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <QVector>

class SudokuField {
public:
    SudokuField();
    int** GetSudokuField();
    int** GetSudokuFieldAnswer();
    void SimpleLevelGenerate();
    void DifficultLevelGenerate(int min_difficulty, int max_difficulty);
    int CalculateDifficulty(int** arr);
    bool TryFill(int row, int column, int number);
    QString GetHint();

private:
    int GiveHint();
    int GetDifficulty();
    bool IsValid(int i, int j);
    int IsSolvable();
    int CalculateDifficulty();
    void OptimisedIsSolvable();
    void SimpleBaseGenerate();
    void RandomBaseGenerate();
    void FillAnswer();
    void FillCheck();
    void TryAddCell();
    void TryDeleteCell();
    void FillAllCandidates();
    void FillCrossCandidates(int i, int j);
    int** field;
    int** check;
    int** answer;
    int** chechers_answer;
    int empty_cells = 0;
    int checking_empty_cells = 0;
    bool already_unique = 0;
    int all_sum = 0;
    QVector<int> candidates[9][9];

};


#endif //MAIN_VARIANT_SUDOKUFIELD_H
