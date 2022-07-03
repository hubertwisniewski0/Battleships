//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_LEGEND_HPP
#define BATTLESHIPS_LEGEND_HPP

#include <SDL.h>
#include "Text.hpp"

class Legend {
private:
    SDL_Surface *legend = NULL;
    SDL_Surface *legendColors = NULL;
    Text *text = NULL;
    SDL_Surface *texts[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    bool legendOk = true;

public:
    Legend(Text *T);

    ~Legend();

    bool ok();

    void draw(SDL_Surface *target, uint16_t x, uint16_t y);
};

#endif //BATTLESHIPS_LEGEND_HPP
