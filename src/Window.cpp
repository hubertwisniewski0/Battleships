//
// Created by hubert25632 on 01.07.22.
//

#include "Window.hpp"
#include "General.hpp"
#include "MessageService.hpp"

Window::Window(MessageService *messageService) : messageService(messageService) {
    window = SDL_CreateWindow("Battleships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
    if (window == nullptr)
        messageService->showMessage(MessageService::MessageType::Error,
                                    "SDL_CreateWindow: " + std::string(SDL_GetError()));
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

void Window::initialize() {
    for (auto &board: boards)
        board.second = new Board(messageService);
    text = new Text(messageService);
    legend = new Legend(messageService, text);
    texts = new Texts(messageService, text);
}

void Window::draw(uint8_t victory) {
    SDL_FillRect(SDL_GetWindowSurface(window), nullptr, 0);
    for (auto &board: boards)
        board.second->draw(SDL_GetWindowSurface(window), graphicsXOffset + boardIterativeOffset * static_cast<unsigned>(board.first) + boardXOffset, graphicsYOffset);
    legend->draw(SDL_GetWindowSurface(window), legendBaseXOffset + boardXOffset, legendYOffset);
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
    messageService->showMessage(MessageService::MessageType::Victory,
                                (w == 1 ? "Player" : "Enemy") + std::string("'s victory"));
}

SDL_Window *Window::getWindow() {
    return window;
}
