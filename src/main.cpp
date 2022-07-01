#include<iostream>
#include<ctime>
#include<pthread.h>
#include<SDL.h>
#include<SDL_ttf.h>
#define XOFFSET 40
void errorMessage(std::string message)
{
    if(SDL_WasInit(SDL_INIT_VIDEO))
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), NULL);
    else
        std::cerr << message << "\n";
}
void victoryMessage(std::string message, SDL_Window* window)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory", message.c_str(), window);
}
#include"statki.hpp"
#include"tekst.hpp"
#include"legenda.hpp"
#include"napisy.hpp"
#include"plansza.hpp"
#include"zegar.hpp"
#include"okno.hpp"
#include"interfejs.hpp"
int main(int argc, char* argv[])
{
    srand(time(NULL));
    Game game;
    Enemy enemy(&game);
    GUI gui(&game, &enemy);
    if(!gui.ok())
        return 1;
    gui.start();
    return 0;
}
