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
    int TryAdd(int row, int column, int number);
    void ShowCell(int row, int column);
    int** GetNotes();
    void GetFastNotes();
    void SetCell(int row, int column, int value);
    void SetNotes(int row, int column);
    int GetNote(int row, int column);
    int GetSimpleHint();
    int GetCleverHint();
    int GetEmptyCellsNumber();
    void show_field();

private:
    void FillBaseNotes();
    int** notes;
    int** players_notes;
    bool pencil = false;

};


#endif //MAIN_VARIANT_PLAYERSFIELD_H
