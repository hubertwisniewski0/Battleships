//
// Created by hubert25632 on 01.07.22.
//

#include "Game.hpp"
#include <cstdlib>

Game::Game() {
    newGame();
}

void Game::clearBoards() {
    for (auto boardOwner: {BoardOwner::Player, BoardOwner::Enemy})
        for (auto &boardColumn: boards[boardOwner])
            for (auto &boardField: boardColumn)
                boardField = FieldType::Empty;
}

void Game::generateBoards() {
    // For each board
    for (auto &board: boards) {
        // For each possible ship length
        for (uint8_t l = 4; l > 0; l--) {
            // For each ship (count)
            for (uint8_t c = 0; c < 5 - l;) {
                // Ship start coordinates
                Position start;

                // Generate a random direction: 0 - horizontal, 1 - vertical
                uint8_t direction;
                direction = rand() % 2;

                if (direction == 0) {
                    start.x = rand() % (10 - (l - 1));
                    start.y = rand() % 10;
                } else {
                    start.x = rand() % 10;
                    start.y = rand() % (10 - (l - 1));
                }

                // Check if there is enough space to place a ship (ignore board boundaries)
                bool available = true;
                for (int8_t ckx = start.x - 1; ckx < start.x + (direction == 0 ? l + 1 : 2) && available; ckx++) {
                    for (int8_t cky = start.y - 1;
                         cky < start.y + (direction == 0 ? 2 : l + 1) && available; cky++) {
                        if (ckx < 0 || ckx > 9 || cky < 0 || cky > 9)
                            continue;
                        if (board.second[ckx][cky] != FieldType::Empty)
                            available = false;
                    }
                }

                // If the searched space is available, place the ship and increase the placed ship count
                if (available) {
                    if (direction == 0)
                        for (uint8_t field = start.x; field < start.x + l; field++)
                            board.second[field][start.y] = FieldType::Ship;
                    else
                        for (uint8_t field = start.y; field < start.y + l; field++)
                            board.second[start.x][field] = FieldType::Ship;
                    c++;
                }
            }
        }
    }
}

bool Game::sunk(BoardOwner boardOwner, Position position, Position prevPosition, bool mark) {
    // Check the 3x3 area around the given coordinates
    for (uint8_t j = position.x - (position.x > 0); j <= position.x + 1; j++) {
        for (uint8_t k = position.y - (position.y > 0); k <= position.y + 1; k++) {
            // If these are the given coordinates or the previous ones, skip checking.
            if ((j == position.x && k == position.y) || (j == prevPosition.x && k == prevPosition.y))
                continue;

            FieldType fieldType = field(boardOwner, {j, k});
            // If this is a 'ship' field, it means that the ship has not been sunk
            if (fieldType == FieldType::Ship)
                return false;
                // If this is a 'hit' field, keep checking
            else if (fieldType == FieldType::Hit)
                if (!sunk(boardOwner, {j, k}, position, mark))
                    return false;
        }
    }

    // Mark the fields as sunk if requested
    if (mark)
        boards[boardOwner][position.x][position.y] = FieldType::Sunk;

    return true;
}

bool Game::victory(BoardOwner boardOwner) {
    for (uint8_t j = 0; j < 10; j++)
        for (uint8_t k = 0; k < 10; k++)
            if (boards[boardOwner][j][k] == FieldType::Ship)
                return false;
    return true;
}

void Game::newGame() {
    clearBoards();
    generateBoards();
}

Game::ShootingResult Game::shot(BoardOwner boardOwner, Position position) {
    if (position.x > 9 || position.y > 9 || field(boardOwner, position) == FieldType::Miss ||
        field(boardOwner, position) == FieldType::Hit ||
        field(boardOwner, position) == FieldType::Sunk)
        return ShootingResult::Invalid;

    switch (field(boardOwner, position)) {
        case FieldType::Empty:
            boards[boardOwner][position.x][position.y] = FieldType::Miss;
            return ShootingResult::Miss;
        case FieldType::Ship: {
            boards[boardOwner][position.x][position.y] = FieldType::Hit;
            if (sunk(boardOwner, position, false)) {
                sunk(boardOwner, position, true);
                return ShootingResult::Sunk;
            } else
                return ShootingResult::Hit;
        }
    }

    return ShootingResult::Invalid;
}

Game::FieldType Game::field(BoardOwner boardOwner, Position position) {
    if (position.x > 9 || position.y > 9)
        return FieldType::Empty;
    return boards[boardOwner][position.x][position.y];
}
