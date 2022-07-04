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
    Text *const text;
    SDL_Surface *texts[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    bool legendOk = true;

public:
    Legend(Text *text);

    ~Legend();

    bool ok();

    void draw(SDL_Surface *target, uint16_t x, uint16_t y);
};

#endif //BATTLESHIPS_LEGEND_HPP
