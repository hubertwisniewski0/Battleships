//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_TEXT_HPP
#define BATTLESHIPS_TEXT_HPP

#include <SDL_ttf.h>
#include "MessageService.hpp"

class Text {
private:
    TTF_Font *font = nullptr;

public:
    explicit Text(MessageService *messageService);

    ~Text();

    SDL_Surface *renderText(const char *text);

    static void drawText(SDL_Surface *text, SDL_Surface *target, uint16_t x, uint16_t y);

    int getMinOffset();
};

#endif //BATTLESHIPS_TEXT_HPP
