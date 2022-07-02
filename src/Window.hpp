//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_WINDOW_HPP
#define BATTLESHIPS_WINDOW_HPP

#include "Board.hpp"
#include "Texts.hpp"
#include "Legend.hpp"
#include "Game.hpp"

class Window {
private:
    SDL_Window *window = NULL;
    Board *board[2] = {NULL, NULL};
    Text *text = NULL;
    Legend *legend = NULL;
    Texts *texts = NULL;
    bool windowOk = true;

public:
    Window();

    ~Window();

    bool ok();

    void draw(uint8_t victory);

    void updateBoards(uint8_t i, uint8_t x, uint8_t y, Game::FieldType fieldType);

    void resetTexts();

    void updateTexts(uint8_t i, uint8_t x, uint8_t y, Game::ShootingResult shootingResult, bool reset);

    void victory(uint8_t w);
};

#endif //BATTLESHIPS_WINDOW_HPP
