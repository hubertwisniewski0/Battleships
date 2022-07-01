//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_LEGEND_HPP
#define BATTLESHIPS_LEGEND_HPP

class Legend {
private:
    SDL_Surface *legend = NULL;
    SDL_Surface *legendColors = NULL;
    Text *text = NULL;
    SDL_Surface *texts[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    bool legendOk = true;

public:
    Legend(Text *T) {
        legend = SDL_CreateRGBSurface(0, 300, 180, 24, 0, 0, 0, 0);
        if (legend == NULL) {
            errorMessage(std::string("SDL_CreateRGBSurface: ") + std::string(SDL_GetError()));
            legendOk = false;
            return;
        }
        legendColors = SDL_CreateRGBSurface(0, 32, 152, 24, 0, 0, 0, 0);
        if (legendColors == NULL) {
            errorMessage(std::string("SDL_CreateRGBSurface: ") + std::string(SDL_GetError()));
            legendOk = false;
            return;
        }
        text = T;
        SDL_Rect field;
        field.w = 28;
        field.h = 28;
        field.x = 2;
        uint32_t colors[5];
        colors[0] = 0x0000FF;
        colors[1] = 0x00FF00;
        colors[2] = 0x7F7F7F;
        colors[3] = 0xFFFF00;
        colors[4] = 0xFF0000;
        SDL_FillRect(legendColors, NULL, 0xFFFFFF);
        for (uint8_t i = 0; i < 5; i++) {
            field.y = i * (field.h + 2) + 2;
            SDL_FillRect(legendColors, &field, colors[i]);
        }
        texts[0] = text->renderText("Legend:");
        texts[1] = text->renderText("Empty/unknown field");
        texts[2] = text->renderText("Ship");
        texts[3] = text->renderText("Miss");
        texts[4] = text->renderText("Hit");
        texts[5] = text->renderText("Sunk");
        texts[6] = text->renderText("N = New game");
        texts[7] = text->renderText("ESC = Exit");
        for (uint8_t i = 0; i < 6; i++)
            text->drawText(texts[i], legend, 45, 13 - texts[i]->h / 2 + 30 * i);
        text->drawText(texts[6], legend, 300 - texts[6]->w, 180 - texts[7]->h - texts[6]->h);
        text->drawText(texts[7], legend, 300 - texts[7]->w, 180 - texts[7]->h);
        SDL_Rect legendColorsPosition;
        legendColorsPosition.x = 0;
        legendColorsPosition.y = 28;
        SDL_BlitSurface(legendColors, NULL, legend, &legendColorsPosition);
    }

    ~Legend() {
        if (legend != NULL)
            SDL_FreeSurface(legend);
        if (legendColors != NULL)
            SDL_FreeSurface(legendColors);
        for (uint8_t i = 0; i < 8; i++)
            if (texts[i] != NULL)
                SDL_FreeSurface(texts[i]);
    }

    bool ok() {
        return legendOk;
    }

    void draw(SDL_Surface *target, uint16_t x, uint16_t y) {
        SDL_Rect position;
        position.x = x;
        position.y = y;
        SDL_BlitSurface(legend, NULL, target, &position);
    }

};

#endif //BATTLESHIPS_LEGEND_HPP
