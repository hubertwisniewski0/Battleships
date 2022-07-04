//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_GUI_HPP
#define BATTLESHIPS_GUI_HPP

#include "Window.hpp"
#include "Timer.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include "MessageService.hpp"
#include <SDL.h>

class GUI : public MessageService {
private:
    Game *const game;
    Enemy *const enemy;
    Window *window;
    Timer *timer;

    SDL_Event event;
    bool quit = false;
    uint8_t victory = 0;
    uint8_t x, y;

    void drawBoards();

    void reset();

    void announceVictory(uint8_t w);

public:
    GUI(Game *game, Enemy *enemy);

    ~GUI();

    void initialize();

    void start();

    void showMessage(MessageType messageType, const std::string &message) override;
};

#endif //BATTLESHIPS_GUI_HPP
