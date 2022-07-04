//
// Created by hubert25632 on 01.07.22.
//

#include "Window.hpp"
#include "Messages.hpp"
#include "General.hpp"

Window::Window() : text(new Text), legend(new Legend(text)), texts(new Texts(text)) {
    window = SDL_CreateWindow("Battleships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if (window == nullptr) {
        errorMessage(std::string("SDL_CreateWindow: ") + std::string(SDL_GetError()));
        windowOk = false;
        return;
    }
    for (auto &board: boards) {
        board.second = new Board;
        if (!board.second->ok()) {
            windowOk = false;
            return;
        }
    }
    if (!text->ok()) {
        windowOk = false;
        return;
    }
    if (!legend->ok()) {
        windowOk = false;
        return;
    }
    if (!texts->ok()) {
        windowOk = false;
        return;
    }
}

Window::~Window() {
    delete texts;
    delete legend;
    delete text;
    for (auto &board: boards)
        delete board.second;
    if (window != nullptr)
        SDL_DestroyWindow(window);
}

bool Window::ok() {
    return windowOk;
}

void Window::draw(uint8_t victory) {
    SDL_FillRect(SDL_GetWindowSurface(window), nullptr, 0);
    for (auto &board: boards)
        board.second->draw(SDL_GetWindowSurface(window), 29 + 360 * static_cast<unsigned>(board.first) + XOFFSET, 59);
    legend->draw(SDL_GetWindowSurface(window), 389 + XOFFSET, 374);
    texts->draw(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);
}

void Window::updateBoards(Game::BoardOwner boardOwner, uint8_t x, uint8_t y, Game::FieldType fieldType) {
    boards[boardOwner]->update(x, y, fieldType);
}

void Window::resetTexts() {
    texts->updateTexts(0, 0, 0, Game::ShootingResult::Invalid, true);
}

void Window::updateTexts(uint8_t i, uint8_t x, uint8_t y, Game::ShootingResult shootingResult, bool reset) {
    texts->updateTexts(i, x, y, shootingResult, reset);
}

void Window::victory(uint8_t w) {
    if (w == 1)
        victoryMessage(std::string("Player's victory"), window);
    else
        victoryMessage(std::string("Enemy's victory"), window);
}
