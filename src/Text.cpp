//
// Created by hubert25632 on 01.07.22.
//

#include "Text.hpp"

Text::Text(MessageService *messageService) {
    if (TTF_Init() != 0)
        messageService->showMessage(MessageService::MessageType::Error, "TTF_Init: " + std::string(TTF_GetError()));
    font = TTF_OpenFont(TTF_FONT_PATH, 16);
    if (font == nullptr)
        messageService->showMessage(MessageService::MessageType::Error, "TTF_OpenFont: " + std::string(TTF_GetError()));
    textColor.r = 0xFF;
    textColor.g = 0xFF;
    textColor.b = 0xFF;
    textColor.a = 0xFF;
    backgroundColor.r = 0x00;
    backgroundColor.g = 0x00;
    backgroundColor.b = 0x00;
    backgroundColor.a = 0xFF;
}

Text::~Text() {
    if (font != nullptr)
        TTF_CloseFont(font);
    if (TTF_WasInit() != 0)
        TTF_Quit();
}

SDL_Surface *Text::renderText(const char *text) {
    return TTF_RenderUTF8_Shaded(font, text, textColor, backgroundColor);
}

void Text::drawText(SDL_Surface *text, SDL_Surface *target, uint16_t x, uint16_t y) {
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(text, nullptr, target, &position);

}

int Text::getMinOffset() {
    return TTF_FontLineSkip(font);
}
