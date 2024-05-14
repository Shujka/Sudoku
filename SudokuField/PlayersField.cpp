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
    players_notes = new int *[9];
    for (int i = 0; i < 9; i++) {
        notes[i] = new int[9];
        players_notes[i] = new int[9];
    }
    FillBaseNotes();
}

void PlayersField::FillBaseNotes() {
    FillAllCandidates();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            players_notes[i][j] = 0;
            if (field[i][j] == 0) {
                notes[i][j] = candidates[i][j];
            } else {
                notes[i][j] = candidates[i][j];
                players_notes[i][j] = (1 << field[i][j]);
                players_notes[i][j] ++;
                notes[i][j]++;
            }
        }
    }
}

void PlayersField::SetPencil() {
    pencil ^= 1;
}

// 0 - pencil, try to write at filled, change number
// 1 - pencil, delete note, all is done

int PlayersField::TryAdd(int i, int j, int number) {
    // 0 - do nothing
    // 1 - done what expected
    // 2 - not changed pencil mistake
    // 3 - mistake in filling with pen
    std::cout << "tryadd\n";
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            std::cout << field[i][j] << " ";
        }
    }
    std::cout << '\n';
    std::cout << " i " << i << " " << j << " " << field[i][j] << " number " << number << " answer " << answer[i][j] << '\n';
    if (pencil) {
        // pencil
        // every move is correct
        // just ^ notes
        if(notes[i][j] & 1) {
            // not empty cell
            // do nothing
            return 0;
        }
        // empty cell
        // just work with notes
        // add only if it's good in rows, columns and squares
        // delete everytime
        bool type = (players_notes[i][j] >> number) & 1;
        if (type) {
            // delete
            players_notes[i][j] -= (1 << number) * type;
            type ^= 1;
            players_notes[i][j] += (1 << number) * type;
            return 1;
        }
        FillCheck();
        check[i][j] = number;
        if (IsValid(i, j)) {
            // good work
            check[i][j] = 0;
            players_notes[i][j] -= (1 << number) * type;
            type ^= 1;
            players_notes[i][j] += (1 << number) * type;
            return 1;
        } else {
            check[i][j] = 0;
            std::cout << "bad note. obvious mistake\n";
            return 2;
        }
    } else {
        // pen
        if (notes[i][j] & 1) {
            // not empty cell
            // do nothing
            return 0;
        } else {
            // empty cell
            // try fill if correct
            if (answer[i][j] == number) {
                notes[i][j] = (1 << number);
                notes[i][j]++;
                field[i][j] = number;
                players_notes[i][j] = notes[i][j];
                for (int x = 0; x < 9; x++) {
                    if(x == i)
                        continue;
                    if ((notes[x][j] >> number) & 1) {
                        notes[x][j] -= (1 << number);
                    }
                    if ((players_notes[x][j] >> number) & 1) {
                        players_notes[x][j] -= (1 << number);
                    }
                }
                for (int y = 0; y < 9; y++) {
                    if(y == j)
                        continue;
                    if ((notes[i][y] >> number) & 1) {
                        notes[i][y] -= (1 << number);
                    }
                    if ((players_notes[i][y] >> number) & 1) {
                        players_notes[i][y] -= (1 << number);
                    }
                }
                for (int x = (i / 3) * 3; x < (i / 3 + 1) * 3; x++) {
                    for (int y = (j / 3) * 3; y < (j / 3 + 1) * 3; y++) {
                        if(x == i && y == j)
                            continue;
                        if ((notes[x][y] >> number) & 1) {
                            notes[x][y] -= (1 << number);
                        }
                        if ((players_notes[x][y] >> number) & 1) {
                            players_notes[x][y] -= (1 << number);
                        }
                    }
                }
                return 1;
            }
            return 3;
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

int **PlayersField::GetNotes() {
    return players_notes;
}

int PlayersField::GetNote(int row, int column) {
    return players_notes[row][column];
}

void PlayersField::GetFastNotes() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            players_notes[i][j] = notes[i][j];
        }
    }
}

void PlayersField::SetCell(int row, int column, int value) {
    std::cout << "ok set cell " << row << " " << column << " value " << value << '\n';
    if (value & 1) {
        // not empty cell
        for (int i = 1; i < 9; i ++) {
            if ((value >> i) & 1) {
                field[row][column] = i;
                break;
            }
        }
    } else {
        field[row][column] = 0;
    }
    players_notes[row][column] = value;
    for (int i = 0; i < 9; i ++)
    {
        for (int j = 0; j < 9; j ++)
        {
            std::cout << field[i][j];
        }
        std::cout << '\n';
    }
//    exit(0);
}

void PlayersField::SetNotes(int row, int column) {
    if (field[row][column]) {
        notes[row][column] = (1 << field[row][column]) + 1;
        return;
    }
    notes[row][column] = 0;
    FillCheck();
    for (int value = 1; value <= 9; value++) {
        check[row][column] = value;
        if (IsValid(row, column)) {
            notes[row][column] += (1 << value);
        }
        check[row][column] = 0;
    }
}

int PlayersField::GetSimpleHint() {
    int best_difficulty = -1;
    int best_cell = -1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (field[i][j] == 0) {
                field[i][j] = answer[i][j];
                int current_difficulty = CalculateDifficulty(field);
                if (current_difficulty > best_difficulty) {
                    best_difficulty = current_difficulty;
                    best_cell = i * 10 + j;
                }
                field[i][j] = 0;
            }
        }
    }
    if (best_difficulty == -1)
        return -1;
    int i = best_cell / 10, j = best_cell % 10;
    notes[i][j] = (1 << answer[i][j]);
    notes[i][j]++;
    field[i][j] = answer[i][j];
    players_notes[i][j] = notes[i][j];
    for (int x = 0; x < 9; x++) {
        if (x == i)
            continue;
        if ((notes[x][j] >> answer[i][j]) & 1) {
            notes[x][j] -= (1 << answer[i][j]);
        }
        if ((players_notes[x][j] >> answer[i][j]) & 1) {
            players_notes[x][j] -= (1 << answer[i][j]);
        }
    }
    for (int y = 0; y < 9; y++) {
        if(y == j)
            continue;
        if ((notes[i][y] >> answer[i][j]) & 1) {
            notes[i][y] -= (1 << answer[i][j]);
        }
        if ((players_notes[i][y] >> answer[i][j]) & 1) {
            players_notes[i][y] -= (1 << answer[i][j]);
        }
    }
    for (int x = (i / 3) * 3; x < (i / 3 + 1) * 3; x++) {
        for (int y = (j / 3) * 3; y < (j / 3 + 1) * 3; y++) {
            if(x == i && y == j)
                continue;
            if ((notes[x][y] >> answer[i][j]) & 1) {
                notes[x][y] -= (1 << answer[i][j]);
            }
            if ((players_notes[x][y] >> answer[i][j]) & 1) {
                players_notes[x][y] -= (1 << answer[i][j]);
            }
        }
    }
    return best_cell;
}

int PlayersField::GetEmptyCellsNumber() {
    int ans = 0;
    std::cout << '\n';
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            if(!field[i][j])
                ans ++;
        }
    }
    return ans;
}

void PlayersField::show_field() {
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            std::cout << field[i][j];
        }
        std::cout << '\n';
    }
}
