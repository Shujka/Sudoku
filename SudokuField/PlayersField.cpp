//
// Created by darina on 4/28/24.
//

#include <iostream>
#include "PlayersField.h"

PlayersField::PlayersField(int type, int min_difficulty, int max_difficulty) {
    if (type == 0) {
        SimpleLevelGenerate();
    } else {
        DifficultLevelGenerate(min_difficulty, max_difficulty);
    }
    notes = new int *[9];
    for (int i = 0; i < 9; i++) {
        notes[i] = new int[9];
    }
    FillBaseNotes();
}

void PlayersField::FillBaseNotes() {
    FillAllCandidates();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (field[i][j] == 0) {
                notes[i][j] = candidates[i][j];
            } else {
                notes[i][j] = candidates[i][j];
                notes[i][j]++;
            }
        }
    }
}

void PlayersField::SetPencil() {
    pencil ^= 1;
}

bool PlayersField::TryAdd(int i, int j, int number) {
    if (pencil) {
        // pencil
        // every move is correct
        // just ^ notes
        if(notes[i][j] & 1) {
            // not empty cell
            // do nothing
            // consider as mistake
            return false;
        }
        // empty cell
        // just work with notes
        // add only if it's good in rows, columns and squares
        // delete everytime
        bool type = (notes[i][j] >> number) & 1;
        if (type) {
            // delete
            notes[i][j] -= (1 << number) * type;
            type ^= 1;
            notes[i][j] += (1 << number) * type;
            return true;
        }
        FillCheck();
        check[i][j] = number;
        if (IsValid(i, j)) {
            // good work
            check[i][j] = 0;
            notes[i][j] -= (1 << number) * type;
            type ^= 1;
            notes[i][j] += (1 << number) * type;
            return true;
        } else {
            check[i][j] = 0;
            std::cout << "bad note. obvious mistake\n";
            return false;
        }
    } else {
        // pen
        if (notes[i][j] & 1) {
            // not empty cell
            // do nothing
            // consider as mistake
            return false;
        } else {
            // empty cell
            // try fill if correct
            if (answer[i][j] == number) {
                notes[i][j] = (1 << number);
                notes[i][j]++;
                return true;
            }
            return false;
        }
    }
}

void PlayersField::ShowCell(int row, int column) {
    std::cout << "empty or not (1 if no) " << (notes[row][column] & 1) << '\n';
    for (int i = 1; i <= 9; i++) {
        if ((notes[row][column] >> i) & 1) {
            // has number
            std::cout << i << " ";
        }
    }
    std::cout << '\n';
}
