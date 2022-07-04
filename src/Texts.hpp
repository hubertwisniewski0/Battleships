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
    bool textsOk = true;

public:
    Texts(Text *text);

    ~Texts();

    bool ok();

    void draw(SDL_Surface *target);

    void updateTexts(uint8_t i, uint8_t x, uint8_t y, Game::ShootingResult shootingResult, bool reset);
};

#endif //BATTLESHIPS_TEXTS_HPP
