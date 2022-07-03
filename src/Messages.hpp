//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_MESSAGES_HPP
#define BATTLESHIPS_MESSAGES_HPP

#include <string>
#include <SDL.h>

void errorMessage(std::string message);

void victoryMessage(std::string message, SDL_Window *window);

#endif //BATTLESHIPS_MESSAGES_HPP
