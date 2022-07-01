//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_TEXT_HPP
#define BATTLESHIPS_TEXT_HPP

class Text {
private:
    TTF_Font *font = NULL;
    SDL_Color textColor;
    SDL_Color backgroundColor;
    bool textOk = true;

public:
    Text() {
        if (TTF_Init() != 0) {
            errorMessage(std::string("TTF_Init: ") + std::string(TTF_GetError()));
            textOk = false;
            return;
        }
        font = TTF_OpenFont(TTF_FONT_PATH, 16);
        if (font == NULL) {
            errorMessage(std::string("TTF_OpenFont: ") + std::string(TTF_GetError()));
            textOk = false;
            return;
        }
        textColor.r = 0xFF;
        textColor.g = 0xFF;
        textColor.b = 0xFF;
        textColor.a = 0xFF;
        backgroundColor.r = 0x00;
        backgroundColor.g = 0x00;
        backgroundColor.b = 0x00;
        backgroundColor.a = 0xFF;
    }

    ~Text() {
        if (font != NULL)
            TTF_CloseFont(font);
        if (TTF_WasInit() != 0)
            TTF_Quit();
    }

    bool ok() {
        return textOk;
    }

    SDL_Surface *renderText(const char *text) {
        return TTF_RenderUTF8_Shaded(font, text, textColor, backgroundColor);
    }

    void drawText(SDL_Surface *text, SDL_Surface *target, uint16_t x, uint16_t y) {
        SDL_Rect position;
        position.x = x;
        position.y = y;
        SDL_BlitSurface(text, NULL, target, &position);

    }

    int getMinOffset() {
        return TTF_FontLineSkip(font);
    }
};

#endif //BATTLESHIPS_TEXT_HPP
