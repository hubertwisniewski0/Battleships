//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GAME_HPP
#define BATTLESHIPS_GAME_HPP

#include <cstdint>

class Game {
public:
    enum class FieldType {
        Empty = 0,
        Ship = 1,
        Miss = 2,
        Hit = 3,
        Victory = 4, //TODO: to be removed
        NoVictory = 5, //TODO: to be removed
        Sunk = 6,
        UnableToMove = 7 //TODO: to be removed
    };
private:
    FieldType boards[2][10][10];

    void clearBoards();

    void generateBoards();

    bool sunk(uint8_t i, uint8_t x, uint8_t y, uint8_t p_x, uint8_t p_y, bool mark);

public:
    void newGame();

    Game();

    FieldType shot(uint8_t i, uint8_t x, uint8_t y);

    FieldType field(uint8_t i, uint8_t x, uint8_t y);
};

#endif //BATTLESHIPS_GAME_HPP
