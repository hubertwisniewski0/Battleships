//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GAME_HPP
#define BATTLESHIPS_GAME_HPP

#include <cstdint>

class Game {
private:
    uint8_t boards[2][10][10];

    void clearBoards();

    void generateBoards();

    bool sunk(uint8_t i, uint8_t x, uint8_t y, uint8_t p_x, uint8_t p_y, bool mark);

public:
    void newGame();

    Game();

    uint8_t shot(uint8_t i, uint8_t x, uint8_t y);

    uint8_t field(uint8_t i, uint8_t x, uint8_t y);
};

#endif //BATTLESHIPS_GAME_HPP
