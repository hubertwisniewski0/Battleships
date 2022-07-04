//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_WINDOW_HPP
#define BATTLESHIPS_WINDOW_HPP

#include "Board.hpp"
#include "Texts.hpp"
#include "Legend.hpp"
#include "Game.hpp"
#include "MessageService.hpp"

class Window {
private:
    SDL_Window *window = nullptr;
    std::unordered_map<Game::BoardOwner, Board *> boards = {{Game::BoardOwner::Player, NULL},
                                                            {Game::BoardOwner::Enemy,  NULL}};

    MessageService *const messageService;
    Text *text;
    Legend *legend;
    Texts *texts;

public:
    Window(MessageService *messageService);

    ~Window();

    void initialize();

    void draw(uint8_t victory);

    void updateBoards(Game::BoardOwner boardOwner, uint8_t x, uint8_t y, Game::FieldType fieldType);

    void resetTexts();

    void updateTexts(uint8_t i, uint8_t x, uint8_t y, Game::ShootingResult shootingResult, bool reset);

    void victory(uint8_t w);

    SDL_Window *getWindow();
};

#endif //BATTLESHIPS_WINDOW_HPP
