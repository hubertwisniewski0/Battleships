//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_BOARD_HPP
#define BATTLESHIPS_BOARD_HPP

#include <SDL.h>

class Board {
private:
    SDL_Surface *board = NULL;
    SDL_Rect field;
    bool boardOk = true;
public:
    Board();

    ~Board();

    bool ok();

    void update(uint8_t x, uint8_t y, uint8_t s);

    void draw(SDL_Surface *target, uint16_t x, uint16_t y);
};

#endif //BATTLESHIPS_BOARD_HPP
