//
// Created by hubert25632 on 01.07.22.
//

#include "GUI.hpp"
#include "Messages.hpp"
#include "General.hpp"

GUI::GUI(Game *game, Enemy *enemy) : game(game), enemy(enemy), window(new Window), timer(new Timer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        errorMessage(std::string("SDL_Init: ") + std::string(SDL_GetError()));
        guiOk = false;
        return;
    }
    if (!window->ok()) {
        guiOk = false;
        return;
    }
    if (!timer->ok()) {
        guiOk = false;
        return;
    }
}

GUI::~GUI() {
    delete timer;
    delete window;
    if (SDL_WasInit(0) != 0)
        SDL_Quit();
}

void GUI::drawBoards() {
    Game::FieldType f;
    // For each board
    for (auto boardOwner: {Game::BoardOwner::Player, Game::BoardOwner::Enemy}) {
        // For each column
        for (uint8_t j = 0; j < 10; j++) {
            // For each row
            for (uint8_t k = 0; k < 10; k++) {
                f = game->getField(boardOwner, {j, k});
                window->updateBoards(boardOwner, j, k,
                                     (f == Game::FieldType::Ship && boardOwner == Game::BoardOwner::Enemy &&
                                      victory == 0 ? Game::FieldType::Empty
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
    Game::ShootingResult shootingResult;
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
                shootingResult = game->shot(Game::BoardOwner::Enemy, {x, y});

                if (shootingResult == Game::ShootingResult::Invalid)
                    continue;

                window->updateTexts(0, x, y, shootingResult, false);

                if (game->victory(Game::BoardOwner::Enemy))
                    announceVictory(1);
                else {
                    auto [enemyPosition, enemyShootingResult] = enemy->move();
                    window->updateTexts(1, enemyPosition.x, enemyPosition.y, enemyShootingResult, false);
                    if (game->victory(Game::BoardOwner::Player))
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
