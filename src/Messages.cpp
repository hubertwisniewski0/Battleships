//
// Created by hubert25632 on 01.07.22.
//

#include "Messages.hpp"
#include <iostream>

void errorMessage(std::string message) {
    if (SDL_WasInit(SDL_INIT_VIDEO))
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), NULL);
    else
        std::cerr << message << "\n";
}

void victoryMessage(std::string message, SDL_Window *window) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory", message.c_str(), window);
}
