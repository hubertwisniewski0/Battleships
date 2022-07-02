//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GAME_HPP
#define BATTLESHIPS_GAME_HPP

#include <cstdint>

class Game {
public:
    enum class FieldType {
        Empty,
        Ship,
        Miss,
        Hit,
        Sunk
    };

    enum class ShootingResult {
        Invalid,
        Miss,
        Hit,
        Sunk
    };

private:
    FieldType boards[2][10][10];

    void clearBoards();

    void generateBoards();

    bool sunk(uint8_t i, uint8_t x, uint8_t y, uint8_t prevX, uint8_t prevY, bool mark);

    inline bool sunk(uint8_t i, uint8_t x, uint8_t y, bool mark) {
        return sunk(i, x, y, x, y, mark);
    }

public:
    void newGame();

    Game();

    ShootingResult shot(uint8_t i, uint8_t x, uint8_t y);

    FieldType field(uint8_t i, uint8_t x, uint8_t y);

    bool victory(uint8_t i);
};

#endif //BATTLESHIPS_GAME_HPP
