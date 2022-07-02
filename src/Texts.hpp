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
    SDL_Surface *texts[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    SDL_Surface *letters[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    SDL_Surface *numbers[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    SDL_Surface *readings[10][10] = {
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
            {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};
    SDL_Surface *playerReading = NULL;
    SDL_Surface *enemyReading = NULL;
    SDL_Surface *sPlayer = NULL;
    SDL_Surface *sEnemy = NULL;
    Text *text = NULL;
    int minOffset;
    bool textsOk = true;

public:
    Texts(Text *T);

    ~Texts();

    bool ok();

    void draw(SDL_Surface *target);

    void updateTexts(uint8_t i, uint8_t x, uint8_t y, Game::FieldType fieldType, bool reset);
};

#endif //BATTLESHIPS_TEXTS_HPP
