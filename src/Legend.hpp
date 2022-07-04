//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_LEGEND_HPP
#define BATTLESHIPS_LEGEND_HPP

#include <SDL.h>
#include "Text.hpp"

class Legend {
private:
    SDL_Surface *legend = nullptr;
    SDL_Surface *legendColors = nullptr;

    SDL_Surface *texts[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

public:
    Legend(MessageService *messageService, Text *text);

    ~Legend();

    void draw(SDL_Surface *target, uint16_t x, uint16_t y);
};

#endif //BATTLESHIPS_LEGEND_HPP
