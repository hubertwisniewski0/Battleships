//
// Created by hubert25632 on 01.07.22.
//

#include "Legend.hpp"
#include "General.hpp"

constexpr uint32_t colors[] = {0x0000ff, 0x00ff00, 0x7f7f7f, 0xffff00, 0xff0000};


Legend::Legend(MessageService *messageService, Text *text) {
    legend = SDL_CreateRGBSurface(0, legendWidth, legendHeight, 24, 0, 0, 0, 0);
    if (legend == nullptr)
        messageService->showMessage(MessageService::MessageType::Error,
                                    "SDL_CreateRGBSurface: " + std::string(SDL_GetError()));
    legendColors = SDL_CreateRGBSurface(0, legendColorsWidth, legendColorsHeight, 24, 0, 0, 0, 0);
    if (legendColors == nullptr)
        messageService->showMessage(MessageService::MessageType::Error,
                                    "SDL_CreateRGBSurface: " + std::string(SDL_GetError()));
    SDL_Rect field {2,0,boardFieldWidth,boardFieldHeight};
    SDL_FillRect(legendColors, nullptr, 0xFFFFFF);
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
    SDL_BlitSurface(legendColors, nullptr, legend, &legendColorsPosition);
}

Legend::~Legend() {
    if (legend != nullptr)
        SDL_FreeSurface(legend);
    if (legendColors != nullptr)
        SDL_FreeSurface(legendColors);
    for (uint8_t i = 0; i < 8; i++)
        if (texts[i] != nullptr)
            SDL_FreeSurface(texts[i]);
}

void Legend::draw(SDL_Surface *target, uint16_t x, uint16_t y) {
    SDL_Rect position {x,y};
    SDL_BlitSurface(legend, nullptr, target, &position);
}
