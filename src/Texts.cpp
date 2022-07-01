//
// Created by hubert25632 on 01.07.22.
//

#include "Texts.hpp"
#include "Messages.hpp"
#include "General.hpp"

Texts::Texts(Text *T) {
    text = T;
    minOffset = text->getMinOffset();
    texts[0] = text->renderText("Player's sea");
    texts[1] = text->renderText("Enemy's sea");
    texts[2] = text->renderText("Player");
    texts[3] = text->renderText("Enemy");
    texts[4] = text->renderText("Victory");
    texts[5] = text->renderText("Miss");
    texts[6] = text->renderText("Hit");
    texts[7] = text->renderText("Sunk");
    for (uint8_t i = 0; i < 8; i++) {
        if (texts[i] == NULL) {
            errorMessage(std::string("Rendering text n") + std::to_string((int) i) + std::string(": ") +
                         std::string(TTF_GetError()));
            textsOk = false;
            return;
        }
    }
    char t[2];
    char c[3];
    char w[4];
    for (uint8_t i = 0; i < 10; i++) {
        t[0] = 0x41 + i;
        t[1] = 0;
        letters[i] = text->renderText(t);
        for (uint8_t j = 0; j < 10; j++) {
            if (j < 9) {
                c[0] = 0x31 + j;
                c[1] = 0;
            } else {
                c[0] = '1';
                c[1] = '0';
                c[2] = 0;
            }
            if (i == 0) {
                numbers[j] = text->renderText(c);
                if (numbers[j] == NULL) {
                    errorMessage(std::string("Rendering text c") + std::to_string((int) j) + std::string(": ") +
                                 std::string(TTF_GetError()));
                    textsOk = false;
                    return;
                }
            }
            w[0] = 0;
            strcat(w, t);
            strcat(w, c);
            readings[i][j] = text->renderText(w);
            if (readings[i][j] == NULL) {
                errorMessage(
                        std::string("Rendering text w") + std::to_string((int) i) + std::to_string((int) j) +
                        std::string(": ") + std::string(TTF_GetError()));
                textsOk = false;
                return;
            }
        }
        if (letters[i] == NULL) {
            errorMessage(std::string("Rendering text t") + std::to_string((int) i) + std::string(": ") +
                         std::string(TTF_GetError()));
            textsOk = false;
            return;
        }
    }
}

Texts::~Texts() {
    for (uint8_t i = 0; i < 10; i++) {
        if (letters[i] != NULL)
            SDL_FreeSurface(letters[i]);
        if (numbers[i] != NULL)
            SDL_FreeSurface(numbers[i]);
        for (uint8_t j = 0; j < 10; j++)
            if (readings[i][j] != NULL)
                SDL_FreeSurface(readings[i][j]);
    }
    for (uint8_t i = 0; i < 8; i++)
        if (texts[i] != NULL)
            SDL_FreeSurface(texts[i]);
}

bool Texts::ok() {
    return textsOk;
}

void Texts::draw(SDL_Surface *target) {
    text->drawText(texts[0], target, 180 - texts[0]->w / 2 + XOFFSET, 15 - texts[0]->h / 2);
    text->drawText(texts[1], target, 540 - texts[1]->w / 2 + XOFFSET, 15 - texts[1]->h / 2);
    text->drawText(texts[2], target, 30 + XOFFSET, 375 - texts[2]->h / 2);
    text->drawText(texts[3], target, 30 + XOFFSET, 375 - texts[3]->h / 2 + minOffset);
    if (playerReading != NULL)
        text->drawText(playerReading, target, 90 + XOFFSET, 375 - playerReading->h / 2);
    if (enemyReading != NULL)
        text->drawText(enemyReading, target, 90 + XOFFSET, 375 - enemyReading->h / 2 + minOffset);
    if (sPlayer != NULL)
        text->drawText(sPlayer, target, 150 + XOFFSET, 375 - sPlayer->h / 2);
    if (sEnemy != NULL)
        text->drawText(sEnemy, target, 150 + XOFFSET, 375 - sEnemy->h / 2 + minOffset);
    for (uint8_t i = 0; i < 10; i++) {
        text->drawText(letters[i], target, 45 + (30 * i) - letters[i]->w / 2 + XOFFSET, 45 - letters[i]->h / 2);
        text->drawText(letters[i], target, 405 + (30 * i) - letters[i]->w / 2 + XOFFSET, 45 - letters[i]->h / 2);
        text->drawText(numbers[i], target, 15 - numbers[i]->w / 2 + XOFFSET, 75 + (30 * i) - numbers[i]->h / 2);
        text->drawText(numbers[i], target, 375 - numbers[i]->w / 2 + XOFFSET, 75 + (30 * i) - numbers[i]->h / 2);
    }
}

void Texts::updateTexts(uint8_t i, uint8_t x, uint8_t y, uint8_t s, bool reset) {
    if (reset) {
        playerReading = NULL;
        enemyReading = NULL;
        sPlayer = NULL;
        sEnemy = NULL;
        return;
    }
    if (i == 0) {
        playerReading = readings[x][y];
        switch (s) {
            case (0): {
                sPlayer = texts[5];
                break;
            }
            case (1): {
                sPlayer = texts[6];
                break;
            }
            case (4): {
                sPlayer = texts[4];
                break;
            }
            case (5): {
                sPlayer = texts[7];
                break;
            }
        }
    } else {
        enemyReading = readings[x][y];
        switch (s) {
            case (0): {
                sEnemy = texts[5];
                break;
            }
            case (1): {
                sEnemy = texts[6];
                break;
            }
            case (4): {
                sEnemy = texts[4];
                break;
            }
            case (5): {
                sEnemy = texts[7];
                break;
            }
        }
    }
}
