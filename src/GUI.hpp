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
    Window *window = NULL;
    Timer *timer = NULL;
    SDL_Event event;
    bool quit = false;
    uint8_t victory = 0;
    Game *game;
    Enemy *enemy;
    uint8_t x, y;
    bool guiOk = true;

    void drawBoards();

    void reset();

    void announceVictory(uint8_t w);

public:
    GUI(Game *G, Enemy *K);

    ~GUI();

    bool ok();

    void start();
};

#endif //BATTLESHIPS_GUI_HPP
