//
// Created by hubert25632 on 01.07.22.
//

#include "Window.hpp"
#include "Messages.hpp"
#include "General.hpp"

Window::Window() {
    window = SDL_CreateWindow("Battleships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if (window == NULL) {
        errorMessage(std::string("SDL_CreateWindow: ") + std::string(SDL_GetError()));
        windowOk = false;
        return;
    }
    for (uint8_t i = 0; i < 2; i++) {
        board[i] = new Board;
        if (!board[i]->ok()) {
            windowOk = false;
            return;
        }
    }
    text = new Text;
    if (!text->ok()) {
        windowOk = false;
        return;
    }
    legend = new Legend(text);
    if (!legend->ok()) {
        windowOk = false;
        return;
    }
    texts = new Texts(text);
    if (!texts->ok()) {
        windowOk = false;
        return;
    }
}

Window::~Window() {
    if (texts != NULL)
        delete texts;
    if (legend != NULL)
        delete legend;
    if (text != NULL)
        delete text;
    for (uint8_t i = 0; i < 2; i++)
        if (board[i] != NULL)
            delete board[i];
    if (window != NULL)
        SDL_DestroyWindow(window);
}

bool Window::ok() {
    return windowOk;
}

void Window::draw(uint8_t victory) {
    SDL_FillRect(SDL_GetWindowSurface(window), NULL, 0);
    for (uint8_t i = 0; i < 2; i++)
        board[i]->draw(SDL_GetWindowSurface(window), 29 + 360 * i + XOFFSET, 59);
    legend->draw(SDL_GetWindowSurface(window), 389 + XOFFSET, 374);
    texts->draw(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);
}

void Window::updateBoards(uint8_t i, uint8_t x, uint8_t y, Game::FieldType fieldType) {
    board[i]->update(x, y, fieldType);
}

void Window::resetTexts() {
    texts->updateTexts(0, 0, 0, Game::FieldType::Empty, true);
}

void Window::updateTexts(uint8_t i, uint8_t x, uint8_t y, Game::FieldType fieldType, bool reset) {
    texts->updateTexts(i, x, y, fieldType, reset);
}

void Window::victory(uint8_t w) {
    if (w == 1)
        victoryMessage(std::string("Player's victory"), window);
    else
        victoryMessage(std::string("Enemy's victory"), window);
}
