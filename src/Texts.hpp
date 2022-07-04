//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_TEXTS_HPP
#define BATTLESHIPS_TEXTS_HPP

#include <SDL.h>
#include "Text.hpp"
#include "Game.hpp"

class Texts {
private:
    SDL_Surface *texts[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    SDL_Surface *letters[10] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                                nullptr};
    SDL_Surface *numbers[10] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                                nullptr};
    SDL_Surface *readings[10][10] = {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}};
    SDL_Surface *playerReading = nullptr;
    SDL_Surface *enemyReading = nullptr;
    SDL_Surface *sPlayer = nullptr;
    SDL_Surface *sEnemy = nullptr;
    Text *const text;
    int minOffset;

public:
    Texts(MessageService *messageService, Text *text);

    ~Texts();

    void draw(SDL_Surface *target);

    void updateTexts(Game::BoardOwner boardOwner, Game::Position position, Game::ShootingResult shootingResult);

    void resetTexts();
};

#endif //BATTLESHIPS_TEXTS_HPP
