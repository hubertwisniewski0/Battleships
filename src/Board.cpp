//
// Created by hubert25632 on 01.07.22.
//

#include "Board.hpp"

Board::Board(MessageService *messageService) {
    board = SDL_CreateRGBSurface(0, 302, 302, 24, 0, 0, 0, 0);
    if (board == nullptr)
        messageService->showMessage(MessageService::MessageType::Error,
                                    "SDL_CreateRGBSurface: " + std::string(SDL_GetError()));
    field.h = 28;
    field.w = 28;
    SDL_FillRect(board, nullptr, 0xFFFFFF);
}

Board::~Board() {
    if (board != nullptr)
        SDL_FreeSurface(board);
}

void Board::update(uint8_t x, uint8_t y, Game::FieldType fieldType) {
    if (x > 9 || y > 9)
        return;
    field.x = x * (field.w + 2) + 2;
    field.y = y * (field.h + 2) + 2;
    uint32_t color;
    switch (fieldType) {
        case Game::FieldType::Empty: {
            color = 0x0000FF;
            break;
        }
        case Game::FieldType::Ship: {
            color = 0x00FF00;
            break;
        }
        case Game::FieldType::Miss: {
            color = 0x7F7F7F;
            break;
        }
        case Game::FieldType::Hit: {
            color = 0xFFFF00;
            break;
        }
        case Game::FieldType::Sunk: {
            color = 0xFF0000;
            break;
        }
        default: {
            color = 0x000000;
            break;
        }
    }
    SDL_FillRect(board, &field, color);
}

void Board::draw(SDL_Surface *target, uint16_t x, uint16_t y) {
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(board, nullptr, target, &position);
}
