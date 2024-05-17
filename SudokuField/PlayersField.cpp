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
                players_notes[i][j]++;
                notes[i][j]++;
            }
        }
    }
}

void PlayersField::SetPencil(bool type) {
    pencil = type;
}

// 0 - pencil, try to write at filled, change number
// 1 - pencil, delete note, all is done

int PlayersField::TryAdd(int i, int j, int number) {
    // 0 - do nothing
    // 1 - done what expected
    // 2 - not changed pencil mistake
    // 3 - mistake in filling with pen

    if (pencil) {
        // pencil
        // every move is correct
        // just ^ notes
        if (notes[i][j] & 1) {
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
                    if (x == i)
                        continue;
                    if ((notes[x][j] >> number) & 1) {
                        notes[x][j] -= (1 << number);
                    }
                    if ((players_notes[x][j] >> number) & 1) {
                        players_notes[x][j] -= (1 << number);
                    }
                }
                for (int y = 0; y < 9; y++) {
                    if (y == j)
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
                        if (x == i && y == j)
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
    if (value & 1) {
        // not empty cell
        for (int i = 1; i < 9; i++) {
            if ((value >> i) & 1) {
                field[row][column] = i;
                break;
            }
        }
    } else {
        field[row][column] = 0;
    }
    players_notes[row][column] = value;

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
        if (y == j)
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
            if (x == i && y == j)
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
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!field[i][j])
                ans++;
        }
    }
    return ans;
}

void PlayersField::show_field() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << field[i][j];
        }
        std::cout << '\n';
    }
}

// -1 wrong players_notes
// 1 last free cell
// 2 last remaining cell
// 3 last possible cell
// 4 obvious single
// 5 obvious pair
// 6 obvious triples

int PlayersField::GetCleverHint() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (((players_notes[i][j] >> answer[i][j]) & 1) == 0)
                return -1;
        }
    }

    // last free cell search
    for (int i = 0; i < 9; i++) {
        int candidate = 0;
        for (int j = 0; j < 9; j++) {
            if (field[i][j] == 0)
                candidate++;
            if (candidate > 1)
                break;
        }
        if (candidate == 1){
            return 1;
        }
    }
    for (int j = 0; j < 9; j++) {
        int candidate = 0;
        for (int i = 0; i < 9; i++) {
            if (field[i][j] == 0)
                candidate++;
            if (candidate > 1) {
                break;
            }
        }
        if (candidate == 1) {
            return 1;
        }
    }
    for (int x = 0; x < 9; x += 3) {
        for (int y = 0; y < 9; y += 3) {
            int candidate = 0;
            for (int i = x; i < x + 3 && candidate < 2; i++) {
                for (int j = y; j < y + 3; j++) {
                    if (field[i][j] == 0)
                        candidate++;
                    if (candidate > 1)
                        break;
                }
            }
            if (candidate == 1) {
                return 1;
            }
        }
    }

    // search for last remaining cell
    for (int x = 0; x < 9; x += 3) {
        for (int y = 0; y < 9; y += 3) {
            std::vector<int> a(10);
            for (int i = x; i < x + 3; i++) {
                for (int j = y; j < y + 3; j++) {
                    if (field[i][j] == 0) {
                        for (int value = 1; value <= 9; value++) {
                            if ((notes[i][j] >> value) & 1) {
                                a[value]++;
                            }
                        }
                    }
                }
            }
            for (int value = 1; value <= 9; value++) {
                if (a[value] == 1) {
                    return 2;
                }
            }
        }
    }

    // search for last possible cell
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (__builtin_popcount(notes[i][j]) == 1) {
                return 3;
            }
        }
    }

    // search for obvious singles
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (__builtin_popcount(players_notes[i][j]) == 1) {
                return 4;
            }
        }
    }

    // search for obvious pairs
    for (int x = 0; x < 9; x += 3) {
        for (int y = 0; y < 9; y += 3) {
            std::vector<int> pairs;
            std::vector<int> all_variants(10);
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (field[i][j] == 0 && __builtin_popcount(players_notes[i][j]) == 2) {
                        pairs.push_back(players_notes[i][j]);
                    }
                    if (field[i][j] == 0) {
                        for (int value = 1; value <= 9; value++) {
                            if ((players_notes[i][j] >> value) & 1)
                                all_variants[value]++;
                        }
                    }
                }
            }
            sort(pairs.begin(), pairs.end());
            for (int i = 1; i < pairs.size(); i++) {
                if (pairs[i] == pairs[i - 1]) {
                    for (int value = 1; value <= 9; value++) {
                        if (((pairs[i] >> value) & 1) && all_variants[value] > 2) {

                            return 5;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        std::vector<int> pairs;
        std::vector<int> all_variants(10);
        for (int j = 0; j < 9; j++) {
            if (field[i][j] == 0 && __builtin_popcount(players_notes[i][j]) == 2) {
                pairs.push_back(players_notes[i][j]);
            }
            if (field[i][j] == 0) {
                for (int value = 1; value <= 9; value++) {
                    if ((players_notes[i][j] >> value) & 1)
                        all_variants[value]++;
                }
            }
        }
        sort(pairs.begin(), pairs.end());
        for (int j = 1; j < pairs.size(); j++) {
            if (pairs[j] == pairs[j - 1]) {
                for (int value = 1; value <= 9; value++) {
                    if (((pairs[j] >> value) & 1) && all_variants[value] > 2) {

                        return 5;
                    }
                }
            }
        }
    }
    for (int j = 0; j < 9; j++) {
        std::vector<int> pairs;
        std::vector<int> all_variants(10);
        for (int i = 0; i < 9; i++) {
            if (field[i][j] == 0 && __builtin_popcount(players_notes[i][j]) == 2) {
                pairs.push_back(players_notes[i][j]);
            }
            if (field[i][j] == 0) {
                for (int value = 1; value <= 9; value++) {
                    if ((players_notes[i][j] >> value) & 1)
                        all_variants[value]++;
                }
            }
        }
        sort(pairs.begin(), pairs.end());
        for (int i = 1; i < pairs.size(); i++) {
            if (pairs[i] == pairs[i - 1]) {
                for (int value = 1; value <= 9; value++) {
                    if (((pairs[i] >> value) & 1) && all_variants[value] > 2) {

                        return 5;
                    }
                }
            }
        }
    }

    return 0;
    // search for obvious triples

}

void PlayersField::clear() {
    for(int i = 0; i < 9; i ++)
    {
        for(int j = 0; j < 9; j ++)
        {
            field[i][j] = 0;
            players_notes[i][j] = 0;
        }
    }
    players_game = true;
}

int PlayersField::SetAuthorCell(int row, int column, int value) {
    if(field[row][column] == value)
    {
        field[row][column] = 0;
        players_notes[row][column] = 0;
    }
    else
    {
        field[row][column] = value;
        players_notes[row][column] = (1 << value) + 1;
    }
    FillCheck();
    if(IsValid(row, column)) {
        FillCheck();
        FillAllCandidates();
        int t = IsSolvable();
        return t;
    }
    else
    {
        field[row][column] = 0;
        players_notes[row][column] = 0;
        return -1;
    }
}

void PlayersField::PrepareGame() {
    FillCheck();
    Solve();
    notes = new int *[9];
    players_notes = new int *[9];
    for (int i = 0; i < 9; i++) {
        notes[i] = new int[9];
        players_notes[i] = new int[9];
    }
    FillBaseNotes();
}
