//
// Created by hubert25632 on 01.07.22.
//

#include "Game.hpp"
#include <cstdlib>

Game::Game() {
    newGame();
}

void Game::clearBoards() {
    for (uint8_t i = 0; i < 2; i++)
        for (uint8_t j = 0; j < 10; j++)
            for (uint8_t k = 0; k < 10; k++)
                boards[i][j][k] = FieldType::Empty;
}

void Game::generateBoards() {
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
                        if (boards[i][ckx][cky] != FieldType::Empty)
                            available = false;
                    }
                }

                // If the searched space is available, place the ship and increase the placed ship count
                if (available) {
                    if (direction == 0)
                        for (uint8_t field = start[0]; field < start[0] + l; field++)
                            boards[i][field][start[1]] = FieldType::Ship;
                    else
                        for (uint8_t field = start[1]; field < start[1] + l; field++)
                            boards[i][start[0]][field] = FieldType::Ship;
                    c++;
                }
            }
        }
    }
}

bool Game::sunk(uint8_t i, uint8_t x, uint8_t y, uint8_t prevX, uint8_t prevY, bool mark) {
    // Check the 3x3 area around the given coordinates
    for (uint8_t j = x - (x > 0); j <= x + 1; j++) {
        for (uint8_t k = y - (y > 0); k <= y + 1; k++) {
            // If these are the given coordinates or the previous ones, skip checking.
            if ((j == x && k == y) || (j == prevX && k == prevY))
                continue;

            FieldType fieldType = field(i, j, k);
            // If this is a 'ship' field, it means that the ship has not been sunk
            if (fieldType == FieldType::Ship)
                return false;
                // If this is a 'hit' field, keep checking
            else if (fieldType == FieldType::Hit)
                if (!sunk(i, j, k, x, y, mark))
                    return false;
        }
    }

    // Mark the fields as sunk if requested
    if (mark)
        boards[i][x][y] = FieldType::Sunk;

    return true;
}

bool Game::victory(uint8_t i) {
    for (uint8_t j = 0; j < 10; j++)
        for (uint8_t k = 0; k < 10; k++)
            if (boards[i][j][k] == FieldType::Ship)
                return false;
    return true;
}

void Game::newGame() {
    clearBoards();
    generateBoards();
}

Game::ShootingResult Game::shot(uint8_t i, uint8_t x, uint8_t y) {
    if (x > 9 || y > 9 || boards[i][x][y] == FieldType::Miss || boards[i][x][y] == FieldType::Hit ||
        boards[i][x][y] == FieldType::Sunk)
        return ShootingResult::Invalid;

    switch (boards[i][x][y]) {
        case FieldType::Empty:
            boards[i][x][y] = FieldType::Miss;
            return ShootingResult::Miss;
        case FieldType::Ship: {
            boards[i][x][y] = FieldType::Hit;
            if (sunk(i, x, y, false)) {
                sunk(i, x, y, true);
                return ShootingResult::Sunk;
            } else
                return ShootingResult::Hit;
        }
    }

    return ShootingResult::Invalid;
}

Game::FieldType Game::field(uint8_t i, uint8_t x, uint8_t y) {
    if (x > 9 || y > 9)
        return FieldType::Empty;
    return boards[i][x][y];
}
