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
    explicit Window(MessageService *messageService);

    ~Window();

    void initialize();

    void draw();

    void updateBoards(Game::BoardOwner boardOwner, Game::Position position, Game::FieldType fieldType);

    void resetTexts();

    void updateTexts(Game::BoardOwner boardOwner, Game::Position position, Game::ShootingResult shootingResult);

    void victory(uint8_t w);

    SDL_Window *getWindow();
};

#endif //BATTLESHIPS_WINDOW_HPP
