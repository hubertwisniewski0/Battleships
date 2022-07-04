//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GUI_HPP
#define BATTLESHIPS_GUI_HPP

#include "Window.hpp"
#include "Timer.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include <SDL.h>

class GUI {
private:
    Game *const game;
    Enemy *const enemy;
    Window *const window;
    Timer *const timer;

    SDL_Event event;
    bool quit = false;
    bool guiOk = true;
    uint8_t victory = 0;
    uint8_t x, y;

    void drawBoards();

    void reset();

    void announceVictory(uint8_t w);

public:
    GUI(Game *game, Enemy *enemy);

    ~GUI();

    bool ok();

    void start();
};

#endif //BATTLESHIPS_GUI_HPP
