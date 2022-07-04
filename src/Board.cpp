//
// Created by hubert25632 on 01.07.22.
//

#include "Board.hpp"

const std::unordered_map<Game::FieldType, uint32_t> fieldColors = {{Game::FieldType::Empty, 0x0000ff},
                                                                   {Game::FieldType::Ship,  0x00ff00},
                                                                   {Game::FieldType::Miss,  0x7f7f7f},
                                                                   {Game::FieldType::Hit,   0xffff00},
                                                                   {Game::FieldType::Sunk,  0xff0000}};

Board::Board(MessageService *messageService) {
    board = SDL_CreateRGBSurface(0, boardWidth, boardHeight, 24, 0, 0, 0, 0);
    if (board == nullptr)
        messageService->showMessage(MessageService::MessageType::Error,
                                    "SDL_CreateRGBSurface: " + std::string(SDL_GetError()));
    SDL_FillRect(board, nullptr, 0xFFFFFF);
}

Board::~Board() {
    if (board != nullptr)
        SDL_FreeSurface(board);
}

void Board::update(Game::Position position, Game::FieldType fieldType) {
    if (!Game::positionWithinLimits(position))
        return;
    SDL_Rect field = {position.x * (boardFieldWidth + 2) + 2, position.y * (boardFieldHeight + 2) + 2, boardFieldWidth,
                      boardFieldHeight};
    SDL_FillRect(board, &field, fieldColors.at(fieldType));
}

void Board::draw(SDL_Surface *target, uint16_t x, uint16_t y) {
    SDL_Rect position{x, y};
    SDL_BlitSurface(board, nullptr, target, &position);
}
