//
// Created by darina on 4/28/24.
//

#ifndef MAIN_VARIANT_PLAYERSFIELD_H
#define MAIN_VARIANT_PLAYERSFIELD_H

#include "SudokuField.h"

class PlayersField : public SudokuField {
public:
    PlayersField (int type, int min_difficulty, int max_difficulty);
    void SetPencil();
    bool TryAdd(int row, int column, int number);
    void ShowCell(int row, int column);

private:
    void FillBaseNotes();
    int** notes;
    bool pencil = false;
};


#endif //MAIN_VARIANT_PLAYERSFIELD_H
