//
// Created by hubert25632 on 01.07.22.
//

#include "GUI.hpp"
#include "Messages.hpp"
#include "General.hpp"

GUI::GUI(Game *G, Enemy *K) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        errorMessage(std::string("SDL_Init: ") + std::string(SDL_GetError()));
        guiOk = false;
        return;
    }
    window = new Window;
    if (!window->ok()) {
        guiOk = false;
        return;
    }
    timer = new Timer;
    if (!timer->ok()) {
        guiOk = false;
        return;
    }
    game = G;
    enemy = K;
}

GUI::~GUI() {
    if (timer != NULL)
        delete timer;
    if (window != NULL)
        delete window;
    if (SDL_WasInit(0) != 0)
        SDL_Quit();
}

void GUI::drawBoards() {
    Game::FieldType f;
    // For each board
    for (uint8_t i = 0; i < 2; i++) {
        // For each column
        for (uint8_t j = 0; j < 10; j++) {
            // For each row
            for (uint8_t k = 0; k < 10; k++) {
                f = game->field(i, j, k);
                window->updateBoards(i, j, k,
                                     (f == Game::FieldType::Ship && i == 1 && victory == 0 ? Game::FieldType::Empty
                                                                                           : f));
            }
        }
    }
    window->draw(victory);
}

void GUI::reset() {
    game->newGame();
    enemy->reset();
    window->resetTexts();
    victory = 0;
}

void GUI::announceVictory(uint8_t w) {
    victory = w;
    drawBoards();
    window->victory(victory);
}

bool GUI::ok() {
    return guiOk;
}

void GUI::start() {
    Game::FieldType f;
    drawBoards();
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = true;
            if (event.type == SDL_MOUSEMOTION)
                window->draw(victory);
            if (event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.x - XOFFSET >= 390 && event.button.x - XOFFSET < 690 &&
                event.button.y >= 60 && event.button.y < 360 &&
                !victory) {
                x = (event.button.x - XOFFSET) / 30 - 13;
                y = event.button.y / 30 - 2;
                f = game->shot(1, x, y);
                if (f != Game::FieldType::Empty && f != Game::FieldType::Ship && f != Game::FieldType::Victory &&
                    f != Game::FieldType::NoVictory)
                    continue;
                window->updateTexts(0, x, y, f, false);
                if (f == Game::FieldType::Victory)
                    announceVictory(1);
                else {
                    f = enemy->move(&x, &y);
                    if (f == Game::FieldType::UnableToMove)
                        continue;
                    window->updateTexts(1, x, y, f, false);
                    if (f == Game::FieldType::Victory)
                        announceVictory(2);
                }
                drawBoards();
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.scancode) {
                    case (SDL_SCANCODE_N): {
                        reset();
                        drawBoards();
                        break;
                    }
                    case (SDL_SCANCODE_ESCAPE): {
                        quit = true;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }
        timer->synchronize();
    }
}
