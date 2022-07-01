//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GAME_HPP
#define BATTLESHIPS_GAME_HPP

class Game {
private:
    uint8_t boards[2][10][10];

    void clearBoards() {
        for (uint8_t i = 0; i < 2; i++)
            for (uint8_t j = 0; j < 10; j++)
                for (uint8_t k = 0; k < 10; k++)
                    boards[i][j][k] = 0;
    }

    void generateBoards() {
        // For each board
        for (uint8_t i = 0; i < 2; i++) {
            // For each possible ship length
            for (uint8_t l = 4; l > 0; l--) {
                // For each ship
                for (uint8_t c = 0; c < 5 - l;) {
                    // Ship start coordinates
                    uint8_t start[2];

                    // Generate a random direction: 0 - horizontal, 1 - vertical
                    uint8_t direction;
                    direction = rand() % 2;

                    if (direction == 0) {
                        start[0] = rand() % (10 - (l - 1));
                        start[1] = rand() % 10;
                    } else {
                        start[0] = rand() % 10;
                        start[1] = rand() % (10 - (l - 1));
                    }

                    // Check if there is enough space to place a ship (ignore board boundaries)
                    bool available = true;
                    for (int8_t ckx = start[0] - 1; ckx < start[0] + (direction == 0 ? l + 1 : 2) && available; ckx++) {
                        for (int8_t cky = start[1] - 1;
                             cky < start[1] + (direction == 0 ? 2 : l + 1) && available; cky++) {
                            if (ckx < 0 || ckx > 9 || cky < 0 || cky > 9)
                                continue;
                            if (boards[i][ckx][cky] != 0)
                                available = false;
                        }
                    }

                    // If the searched space is available, place the ship and increase the placed ship count
                    if (available) {
                        if (direction == 0)
                            for (uint8_t field = start[0]; field < start[0] + l; field++)
                                boards[i][field][start[1]] = 1;
                        else
                            for (uint8_t field = start[1]; field < start[1] + l; field++)
                                boards[i][start[0]][field] = 1;
                        c++;
                    }
                }
            }
        }
    }

    bool sunk(uint8_t i, uint8_t x, uint8_t y, uint8_t p_x, uint8_t p_y, bool mark) {
        for (int8_t j = x - 1; j < x + 2; j++) {
            for (int8_t k = y - 1; k < y + 2; k++) {
                if (j < 0 || j > 9 || k < 0 || k > 9 || (j == x && k == y) || (j == p_x && k == p_y))
                    continue;
                if (boards[i][j][k] == 1)
                    return false;
                else if (boards[i][j][k] == 3)
                    if (!sunk(i, j, k, x, y, mark))
                        return false;
            }
        }
        if (mark)
            boards[i][x][y] = 6;
        return true;
    }

public:
    void newGame() {
        clearBoards();
        generateBoards();
    }

    Game() {
        newGame();
    }

    uint8_t shot(uint8_t i, uint8_t x, uint8_t y) {
        if (x > 9 || y > 9)
            return 2;
        uint8_t prev = boards[i][x][y];
        if (prev == 0)
            boards[i][x][y] = 2;
        else if (prev == 1)
            boards[i][x][y] = 3;
        bool victory = true;
        for (uint8_t j = 0; j < 10 && victory; j++)
            for (uint8_t k = 0; k < 10 && victory; k++)
                if (boards[i][j][k] == 1)
                    victory = false;
        if (prev != 1)
            return prev;
        else if (sunk(i, x, y, x, y, false) || victory) {
            sunk(i, x, y, x, y, true);
            if (victory)
                return 4;
            else
                return 5;
        } else
            return 1;
    }

    uint8_t field(uint8_t i, uint8_t x, uint8_t y) {
        if (x > 9 || y > 9)
            return 2;
        uint8_t p = boards[i][x][y];
        return p;
    }
};

#endif //BATTLESHIPS_GAME_HPP
